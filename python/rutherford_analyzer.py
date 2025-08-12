import os
import argparse

import ROOT

import math

from particle import Particle

from alive_progress import alive_bar

def trunc_gauss(x, par):

    x = x[0]
    norm, mean, sigma = par[0], par[1], par[2]

    gaus = math.exp(-0.5*((x - mean)/sigma)**2)
    cdf0 = 0.5 * (1 + math.erf((0 - mean) / (sigma * math.sqrt(2))))
    return norm * gaus / (1 - cdf0) / sigma / math.sqrt(2*math.pi)

def main():
    
    # Argument Parser Setup
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", type=str, default="./.data", help="directory of simulation output")
    parser.add_argument("-f", "--final", type=str, default="./.data/analysis.root", help="path to analysis output file")
    args = parser.parse_args()

    # ROOT Setup
    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
    
    electron = Particle.from_pdgid(11)
    alpha    = Particle.from_pdgid(1000020040)

    # Data Setup
    energies_in  = [ ]
    energies_out = [ ]
    deltas       = [ ]
    sigmas       = [ ]
    chi2ndfs     = [ ]
    
    # Simulation Files / Runs
    file_names = os.listdir(args.dir)
    file_paths = [ os.path.join(args.dir, file_name) for file_name in file_names ]
    if args.final in file_paths: file_paths.remove(args.final)
    n_runs = len(file_paths)

    # Analysis Output
    in_out_graph  = ROOT.TGraphErrors(n_runs)
    in_fwhm_graph = ROOT.TGraphErrors(n_runs)
    
    n = 0
    with alive_bar(n_runs) as bar:
        for file_path in file_paths:
        
            file = ROOT.TFile.Open(file_path, "UPDATE")
        
            energy_param = file.Get("Energy")
            if not energy_param: continue
            energy = energy_param.GetVal()
            
            hist = file.Get("histoEnergy")
            if not hist: continue 
            
            # Vavilov Parameter Calculation
            mean = hist.GetMean()
            t_max = 4*electron.mass/alpha.mass * energy
            VAVILOV_THRESHOLD = 10
            vavilov = (energy - mean)/t_max
            if vavilov < VAVILOV_THRESHOLD: raise(f"Calculated vavilov param {vavilov:.1f} < {VAVILOV_THRESHOLD}.")

            # Truncated Gaussian (needs fixing)
            # trunc_gauss_func = ROOT.TF1("truncGaussFunc", trunc_gauss, 0, 2, 3)
            # trunc_gauss_func.SetParNames("norm", "mean", "sigma")
            # trunc_gauss_func.SetParameters(1, 0, 1)
            
            # Fit Specra
            fit = hist.Fit("gaus", "QS")

            # Fit Parameters
            mean      = fit.Parameter(1)
            mean_err  = fit.ParError(1)
            sigma     = fit.Parameter(2)
            sigma_err = fit.ParError(2)
            
            # Statistics
            chi2      = fit.Chi2()
            ndf       = fit.Ndf()
            chi2ndf   = chi2/ndf if ndf != 0 else float("inf")
            p_value   = fit.Prob()
            #
            # SIGNIFICANCE_THRESHOLD = 0.05
            # if p_value > SIGNIFICANCE_THRESHOLD: print(f"BAD FIT FOR Ein={energy}MeV")

            delta = energy - mean
            
            # Fill Graphs
            in_out_graph.SetPoint(n, energy, mean)
            in_out_graph.SetPointError(n, 0.0, mean_err)
            #
            in_fwhm_graph.SetPoint(n, energy, sigma)
            in_fwhm_graph.SetPointError(n, 0.0, sigma_err)
            
            # Histogram Style
            hist.SetLineColor(ROOT.kBlue)
            hist.SetLineWidth(2)
            hist.SetMarkerStyle(0)
            hist.SetFillStyle(0)
            #
            hist.GetXaxis().SetTitle("E_in  [MeV]")
            hist.GetYaxis().SetTitle("dσ/dE [counts per bin]")
            #
            fit_func = hist.GetFunction("gaus")
            if fit_func:
                fit_func.SetLineColor(ROOT.kRed)
                fit_func.SetLineWidth(3)
                fit_func.SetLineStyle(2)
            
            # Save And Close
            hist.Write("", ROOT.TObject.kOverwrite)
            file.Close()
            
            # Fill Lists
            energies_in.append(energy)
            energies_out.append(mean)
            deltas.append(delta)
            sigmas.append(sigma)
            chi2ndfs.append(chi2ndf)
            
            n += 1
            bar()

    in_out_graph.GetXaxis().SetTitle("E_in  [MeV]")
    in_out_graph.GetYaxis().SetTitle("E_out [MeV]")
    in_out_graph.SetLineStyle(0)
    
    in_fwhm_graph.GetXaxis().SetTitle("E_in  [MeV]")
    in_fwhm_graph.GetYaxis().SetTitle("sigma [MeV]")
    in_fwhm_graph.SetLineStyle(0)

    in_out_func = ROOT.TF1("funcEinEout", "pol1", min(energies_in), max(energies_in))
    in_out_graph.Fit(in_out_func, "Q")

    a     = in_out_func.GetParameter(1)
    a_err = in_out_func.GetParError(1)
    b     = in_out_func.GetParameter(0)
    b_err = in_out_func.GetParError(0)

    print(f"E_out = ({a:.2f} +- {a_err:.2f}) * E_in + ({b:.2f} +- {b_err:.2f}) MeV")

    file = ROOT.TFile.Open(args.final, "RECREATE")
    in_out_graph.Write("graphEinEout")
    in_fwhm_graph.Write("graphEinFWHM")
    file.Close()

if __name__ == "__main__":
    main()
