import ROOT
import argparse
import subprocess

def main():
    
    # Argument Parser Setup
    parser = argparse.ArgumentParser()
    
    parser.add_argument("--e-min", type=float, default=4, help="minimal initial energy (in MeV)")
    parser.add_argument("--e-max", type=float, default=5, help="maximum initial energy (in MeV)")
    parser.add_argument("--n-e",   type=int,   default=1, help="number of inital energies")
    parser.add_argument("--d-min", type=float, default=1, help="minimal initial distance (in cm)")
    parser.add_argument("--d-max", type=float, default=2, help="maximum initial distance (in cm)")
    parser.add_argument("--n-d",   type=int,   default=1, help="number of inital distances")
    parser.add_argument("--z-min", type=float, default=1, help="minimal foil thickness (in um)")
    parser.add_argument("--z-max", type=float, default=2, help="maximum foil thickness (in um)")
    parser.add_argument("--n-z",   type=int,   default=1, help="number of foil thicknesses")
    parser.add_argument("-n", "--n-events", type=int, default=100, help="number of events per run")
    
    args = parser.parse_args()

    # ROOT Setup
    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")

    #
    FILE_PATH = "output.root"
    #

    # Initial Data Setup
    energies_in = [ args.e_min + n*(args.e_max - args.e_min)/args.n_e for n in range(0, args.n_e) ]
    distances   = [ args.d_min + n*(args.d_max - args.d_min)/args.n_d for n in range(0, args.n_d) ]
    thicknesses = [ args.z_min + n*(args.z_max - args.z_min)/args.n_z for n in range(0, args.n_z) ]
    
    # Final Data Setup
    energies_out = [ ]
    sigmas       = [ ]
    chi2ndfs     = [ ]

    for energy_in in energies_in:
        for distance in distances:
            for thickness in thicknesses:
                
                subprocess.run([
                    "./build/rutherford-scattering",
                    "-e", str(energy_in),
                    "-n", str(args.n_events)
                ], stdout=subprocess.DEVNULL)

                file = ROOT.TFile.Open(FILE_PATH, "READ")

                hist = file.Get("histoEnergy")
                if not hist: raise RuntimeError("Histogram not found in file!")

                fit = hist.Fit("gaus", "QS")

                mean      = fit.Parameter(1)
                mean_err  = fit.ParError(1)
                sigma     = fit.Parameter(2)
                sigma_err = fit.ParError(2)
                chi2      = fit.Chi2()
                ndf       = fit.Ndf()
                chi2ndf   = chi2/ndf if ndf != 0 else float("inf")
                
                energies_out.append(mean)
                sigmas.append(sigma)
                chi2ndfs.append(chi2ndf)
    
    print(energies_in)
    print(energies_out)
    print(sigmas)
    print(chi2ndfs)

if __name__ == "__main__":
    main()
