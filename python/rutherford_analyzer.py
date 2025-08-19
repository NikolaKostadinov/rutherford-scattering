import os
import sys
import argparse

import ROOT

from rutherford_config    import RutherfordConfig
from rutherford_critical  import rutherford_critical_energy
from rutherford_constants import *
from rutherford_physics   import *

from alive_progress import alive_bar

def main():
    
    # Argument Parser Setup
    parser = argparse.ArgumentParser()
    parser.add_argument("input_dir",             type=str, default="./.data",               help="directory of simulation output and analysis input")
    parser.add_argument("output_file",           type=str, default="./.data/analysis.root", help="path to analysis output file")
    parser.add_argument("-p", "--sign-level",    type=float, default=0.05,                  help="significance value (probability value threshold)")
    parser.add_argument("-V", "--vavilov-level", type=float, default=10.0,                  help="vavilov number threshold")
    parser.add_argument("-v", "--verbose",       action="store_true")
    args = parser.parse_args()

    # ROOT Setup
    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
    ROOT.gErrorIgnoreLevel = ROOT.kFatal
    
    # Data Setup
    configs = []
    
    # Simulation Files / Runs
    file_names = os.listdir(args.input_dir)
    file_paths = [ os.path.join(args.input_dir, file_name) for file_name in file_names ]
    if args.output_file in file_paths: file_paths.remove(args.output_file)
    n_runs = len(file_paths)

    with alive_bar(n_runs, title="fitting spectra", bar="smooth", spinner="squares", unit="runs", dual_line=True) as bar:
        for file_path in file_paths:
        
            file = ROOT.TFile.Open(file_path, "UPDATE")
        
            thickness_param = file.Get("Thickness")
            if not thickness_param: continue
            thickness = thickness_param.GetVal() * um
            
            energy_param = file.Get("Energy")
            if not energy_param: continue
            energy = energy_param.GetVal() * MeV
            
            distance_param = file.Get("Distance")
            if not distance_param: continue
            distance = distance_param.GetVal() * cm
            
            hist = file.Get("histoEnergy")
            if not hist: continue 
            
            # Vavilov Number Calculation
            mean = hist.GetMean() * MeV
            #
            vavilov = vavilov_number(energy, mean, ALPHA_MASS, ELECTRON_MASS)
            if vavilov < args.vavilov_level:
                if args.verbose:
                    print(f"[WARNING] calculated LOW vavilov number: kappa = {vavilov:.1f} < {args.vavilov_level:.0f}")
                bar()
                continue


            # Fit Specra (with a normal distribution)
            try:
                fit = hist.Fit("gaus", "QES")
                
                # Fit Parameters
                mean      = fit.Parameter(1) * MeV
                mean_err  = fit.ParError(1) * MeV
                sigma     = fit.Parameter(2) * MeV
                sigma_err = fit.ParError(2) * MeV
            
                delta = energy - mean

            except Exception:
                if args.verbose:
                    print(f"[WARNING] ROOT could NOT fit specrum from {file_path}")
                bar()
                continue
            
            # Statistics
            chi2      = fit.Chi2()
            ndf       = fit.Ndf()
            chi2ndf   = chi2/ndf if ndf != 0 else float("inf")
            p_value   = fit.Prob()
            #
            if p_value < args.sign_level:
                if args.verbose:
                    print(f"[WARNING] BAD FIT for specrum from {file_path}")
                bar()
                continue

            # Histogram Style
            hist.SetLineColor(ROOT.kBlue)
            hist.SetLineWidth(2)
            hist.SetMarkerStyle(0)
            hist.SetFillStyle(0)
            #
            hist.GetXaxis().SetTitle("E_in  [MeV]")
            hist.GetYaxis().SetTitle("d\\sigma/dE [counts per bin]")
            #
            fit_func = hist.GetFunction("gaus")
            if fit_func:
                fit_func.SetLineColor(ROOT.kRed)
                fit_func.SetLineWidth(3)
                fit_func.SetLineStyle(2)
            
            # Save And Close
            hist.Write("", ROOT.TObject.kOverwrite)
            file.Close()
            
            # Fill Config List

            config = RutherfordConfig()

            config.dz         = thickness
            config.Ein        = energy
            config.Eout       = mean
            config.Eout_err   = mean_err
            config.sigmaE     = sigma
            config.sigmaE_err = sigma_err
            config.d          = distance
            
            configs.append(config)

            bar()
    
    unique_thicknesses = list(set([ config.dz  for config in configs ]))
    unique_energies_in = list(set([ config.Ein for config in configs ]))
    
    energy_in_min = min(unique_energies_in)
    energy_in_max = max(unique_energies_in)
    
    n_thicknesses = len(unique_thicknesses)
    n_energies_in = len(unique_energies_in)
    n_runs_fitted = len(configs)

    file = ROOT.TFile.Open(args.output_file, "RECREATE")
    
    # Local Graphs
    Ein_Eout_graphs = [ ROOT.TGraphErrors(n_runs_fitted) for _ in unique_thicknesses ]
    Ein_FWHM_graphs = [ ROOT.TGraphErrors(n_runs_fitted) for _ in unique_thicknesses ]
    dz_dE_graphs    = [ ROOT.TGraphErrors(n_runs_fitted) for _ in unique_energies_in ]

    # Global Graphs
    Ein_dEdz_graph = ROOT.TGraphErrors(n_energies_in)

    n = 0
    with alive_bar(n_runs_fitted, title="filling data   ", bar="smooth", spinner="squares", unit="runs") as bar:
        for config in configs:
            
            # Find Corresponding Graph
            dz_index = unique_thicknesses.index(config.dz)
            Ein_Eout_graph = Ein_Eout_graphs[dz_index]
            Ein_FWHM_graph = Ein_FWHM_graphs[dz_index]
            #
            Ein_index = unique_energies_in.index(config.Ein)
            dz_dE_graph = dz_dE_graphs[Ein_index]

            Ein_Eout_graph.SetPoint(n,      config.Ein     / MeV, config.Eout     / MeV)
            Ein_Eout_graph.SetPointError(n, config.Ein_err / MeV, config.Eout_err / MeV)
            
            Ein_FWHM_graph.SetPoint(n,      config.Ein     / MeV, config.FWHM()     / MeV)
            Ein_FWHM_graph.SetPointError(n, config.Ein_err / MeV, config.FWHM_err() / MeV)
            
            dz_dE_graph.SetPoint(n,      config.dz     / um, config.dE()     / MeV)
            dz_dE_graph.SetPointError(n, config.dz_err / um, config.dE_err() / MeV)

            n += 1
            bar()

    n = 0
    for Ein, dz_dE_graph in zip(unique_energies_in, dz_dE_graphs):
        
        # Caculate Stopping Power
        dz_dE_func = ROOT.TF1("funcEinEout", "pol1", energy_in_min / MeV, energy_in_max / MeV)
        dz_dE_fit  = dz_dE_graph.Fit(dz_dE_func, "QES")
        dEdz       = dz_dE_func.GetParameter(1) * MeV/um
        dEdz_err   = dz_dE_func.GetParError(1) * MeV/um
       
        Ein_dEdz_graph.SetPoint(n,      Ein / MeV, dEdz     / (MeV/um))
        Ein_dEdz_graph.SetPointError(n, 0.0,       dEdz_err / (MeV/um))

        dz_dE_graph.GetXaxis().SetTitle("dz [um]")
        dz_dE_graph.GetYaxis().SetTitle("dE [MeV]")
        dz_dE_graph.SetLineStyle(0)
        dz_dE_graph.Write(f"graphDzdE")

        n += 1

    for Ein_Eout_graph, Ein_FWHM_graph in zip(Ein_Eout_graphs, Ein_FWHM_graphs):
        Ein_Eout_graph.SetTitle("Energy In-Out Dependance")
        Ein_Eout_graph.GetXaxis().SetTitle("E_in  [MeV]")
        Ein_Eout_graph.GetYaxis().SetTitle("E_out [MeV]")
        Ein_Eout_graph.SetLineStyle(0)
        Ein_Eout_graph.Write("graphEinEout")

        Ein_FWHM_graph.SetTitle("FWHM Spectrum")
        Ein_FWHM_graph.GetXaxis().SetTitle("E_in [MeV]")
        Ein_FWHM_graph.GetYaxis().SetTitle("FWHM [MeV]")
        Ein_FWHM_graph.SetLineStyle(0)
        Ein_FWHM_graph.Write("graphEinFWHM")
        
    Ein_dEdz_graph.SetTitle("Stopping Power")
    Ein_dEdz_graph.GetXaxis().SetTitle("E_in  [MeV]")
    Ein_dEdz_graph.GetYaxis().SetTitle("dE/dz [MeV/um]")
    Ein_dEdz_graph.SetLineStyle(0)
    Ein_dEdz_graph.Write("graphEinDEdz")
    
    file.Close()
    
    print(f"TOTAL  RUNS: {n_runs}")
    print(f"FITTED RUNS: {n_runs_fitted}")
    print(f"FIT EFF:     {(n_runs_fitted/n_runs*100):.1f}%")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
