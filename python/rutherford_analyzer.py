import os
import argparse

import ROOT

def main():
    
    # Argument Parser Setup
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", type=str, default="./.data", help="directory of spectra data")
    args = parser.parse_args()

    # ROOT Setup
    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")

    #
    FILE_PATH = "output.root"
    #

    # Final Data Setup
    energies_in  = [ ]
    energies_out = [ ]
    deltas       = [ ]
    sigmas       = [ ]
    chi2ndfs     = [ ]
    
    for file_name in os.listdir(args.dir):

        file_path = os.path.join(args.dir, file_name)
        
        file = ROOT.TFile.Open(file_path, "READ")
        
        energy_param = file.Get("InitialEnergy")
        if not energy_param: continue
        energy = energy_param.GetVal()

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
        
        energies_in.append(energy)
        energies_out.append(mean)
        deltas.append(energy - mean)
        sigmas.append(sigma)
        chi2ndfs.append(chi2ndf)
    
    print(energies_in)
    print(energies_out)
    print(deltas)
    print(sigmas)
    print(chi2ndfs)

if __name__ == "__main__":
    main()
