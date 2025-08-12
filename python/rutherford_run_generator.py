import os
import subprocess
import argparse

from alive_progress import alive_bar

from system_of_units import *

def main():
    
    # Argument Parser

    parser = argparse.ArgumentParser()
    parser.add_argument("dir", type=str, default="./.data", help="directory of simulation output")
    parser.add_argument("-s", "--simulation",  type=str,   default="./build/rutherford-scattering", help="path to simulation")
    parser.add_argument("-n", "--n-events",    type=int,   default=1, help="number of events per run")
    parser.add_argument("-i", "--energy-min",  type=float, default=4, help="minimum INITIAL energy (in MeV)")
    parser.add_argument("-u", "--energy-max",  type=float, default=5, help="maximum INITIAL energy (in MeV)")
    parser.add_argument("-e", "--energies",    type=int,   default=1, help="number of INITIAL energies")
    parser.add_argument("-b", "--energy-bins", type=int,   default=1, help="number of FINAL energy bins")
    args = parser.parse_args()

    energy_min  = args.energy_min * MeV
    energy_max  = args.energy_max * MeV
    n_energies  = args.energies
    energy_bins = args.energy_bins
    n_events    = args.n_events

    n_runs = n_energies # * n_distances * n_thicknesses
    
    energies = [ energy_min + n*(energy_max - energy_min)/n_energies for n in range(n_energies) ]

    E_BACK_WINDOW = energy_min/2

    new_energy_min = max(energy_min - E_BACK_WINDOW, 0.0)
    new_energy_max = max(energy_max - E_BACK_WINDOW, 0.0)

    with alive_bar(n_runs) as bar:
        for energy in energies:
            subprocess.run([
                args.simulation,
                "--energy" , str(energy / MeV),
                "--energy-min", str(new_energy_min / MeV),
                "--energy-max", str(new_energy_max / MeV),
                "--energy-bins", str(energy_bins),
                "--output" , f"{args.dir}/output-{(energy/MeV):.2f}MeV.root",
                "--n-events", str(n_events)
            ], stdout=subprocess.DEVNULL)
            bar()

if __name__ == "__main__":
    main()
