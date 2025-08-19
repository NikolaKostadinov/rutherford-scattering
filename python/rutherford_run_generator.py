import os
import subprocess
import argparse

from concurrent.futures import ProcessPoolExecutor, as_completed

from alive_progress import alive_bar

from system_of_units import *

def run_simulation(output_dir, simulation, thickness, energy, energy_min, energy_max, energy_bins, n_events):

    subprocess.run(
        [
            simulation,
            "--thickness",   str(thickness / um),
            "--energy" ,     str(energy / MeV),
            "--energy-min",  str(energy_min / MeV),
            "--energy-max",  str(energy_max / MeV),
            "--energy-bins", str(energy_bins),
            "--output" ,     f"{output_dir}/output-{(thickness/um):.1f}um-{(energy/MeV):.3f}MeV-1.0cm.root",
            "--n-events",    str(n_events)
        ],
        stdout=subprocess.DEVNULL
    )

def main():
    
    # Argument Parser

    parser = argparse.ArgumentParser()
    parser.add_argument("output_dir",            type=str,   default="./.data",                       help="directory of simulation output")
    parser.add_argument("-s", "--simulation",    type=str,   default="./build/rutherford-scattering", help="path to simulation")
    parser.add_argument("-j", "--jobs",          type=int,   default=1,                               help="number of concurent jobs")
    parser.add_argument("-n", "--n-events",      type=int,   default=1,                               help="number of events per run")
    parser.add_argument("-t", "--thickness-min", type=float, default=1.0,                             help="minimum foil thickness (in um)")
    parser.add_argument("-T", "--thickness-max", type=float, default=2.0,                             help="maximum foil thickness (in um)")
    parser.add_argument("-z", "--thicknesses",   type=int,   default=1,                               help="number of foil thicknesses")
    parser.add_argument("-i", "--energy-min",    type=float, default=4.0,                             help="minimum INITIAL energy (in MeV)")
    parser.add_argument("-u", "--energy-max",    type=float, default=5.0,                             help="maximum INITIAL energy (in MeV)")
    parser.add_argument("-e", "--energies",      type=int,   default=1,                               help="number of INITIAL energies")
    parser.add_argument("-b", "--energy-bins",   type=int,   default=1,                               help="number of FINAL energy bins")
    args = parser.parse_args()

    thickness_min  = args.thickness_min * um
    thickness_max  = args.thickness_max * um
    n_thicknesses  = args.thicknesses

    energy_min  = args.energy_min * MeV
    energy_max  = args.energy_max * MeV
    n_energies  = args.energies

    energy_bins = args.energy_bins
    
    n_events    = args.n_events

    n_runs = n_thicknesses * n_energies
    
    thicknesses = [ thickness_min + n*(thickness_max - thickness_min)/n_thicknesses for n in range(n_thicknesses) ]
    energies    = [ energy_min    + n*(energy_max    - energy_min   )/n_energies    for n in range(n_energies)    ]

    E_BACK_WINDOW  = energy_min/2
    new_energy_min = max(energy_min - E_BACK_WINDOW, 0.0)
    new_energy_max = max(energy_max - E_BACK_WINDOW, 0.0)
    
    with ProcessPoolExecutor(max_workers = args.jobs) as executor:
        try:
            futures = [
                executor.submit(
                    run_simulation,
                    args.output_dir,
                    args.simulation,
                    thickness,
                    energy,
                    new_energy_min,
                    new_energy_max,
                    energy_bins,
                    n_events
                )
                for thickness in thicknesses
                for energy    in energies
            ]
            with alive_bar(n_runs, title="simulating", bar="smooth", spinner="arrows_in", unit="runs") as bar:
                for future in as_completed(futures):
                    bar()
        
        except KeyboardInterrupt:
            executor.shutdown(wait=False, cancel_futures=True)

if __name__ == "__main__":
    main()
