import os
import sys
import argparse

import ROOT

import math

from particle import Particle

from rutherford_config import RutherfordConfig
from system_of_units   import *

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
    
    # Particles
    electron = Particle.from_pdgid(11)
    alpha    = Particle.from_pdgid(1000020040)
    #
    electron_mass = electron.mass * MeV
    alpha_mass    = alpha.mass * MeV

    # Data Setup
    configs = []
    
    # Simulation Files / Runs
    file_names = os.listdir(args.input_dir)
    file_paths = [ os.path.join(args.input_dir, file_name) for file_name in file_names ]
    if args.output_file in file_paths: file_paths.remove(args.output_file)
    n_runs = len(file_paths)

    with alive_bar(n_runs, title="fitting specra", bar="smooth", spinner="squares", unit="runs", dual_line=True) as bar:
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
            
            # Vavilov Parameter Calculation
            mean = hist.GetMean() * MeV
            #
            cosh = energy/alpha_mass + 1
            sinh = math.sqrt(cosh**2 - 1)
            #
            s = alpha_mass**2 + 2*alpha_mass*electron_mass*cosh + electron_mass**2
            #
            transfer_coef = 2*electron_mass*alpha_mass/s*sinh**2
            transfer_max  = transfer_coef * alpha_mass
            #
            vavilov = (energy - mean)/transfer_max
            if vavilov < args.vavilov_level:
                if args.verbose:
                    print(f"[WARNING] calculated LOW vavilov number: kappa = {vavilov:.1f} < {VAVILOV_THRESHOLD:.0f}")
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

            config.dz        = thickness
            config.Ein       = energy
            config.Eout      = mean
            config.Eout_err  = mean_err
            config.sigma     = sigma
            config.sigma_err = sigma_err
            config.d         = distance
            
            configs.append(config)

            bar()
    
    unique_thicknesses = list(set([ config.dz  for config in configs ]))
    unique_energies_in = list(set([ config.Ein for config in configs ]))

    energy_in_min = min(unique_energies_in)
    energy_in_max = max(unique_energies_in)

    n_thicknesses = len(unique_thicknesses)
    n_energies_in = len(unique_energies_in)
    n_runs_fitted = len(configs)

    in_out_graphs  = [ ]
    in_fwhm_graphs = [ ]
    for thickness in unique_thicknesses:

        in_out_graph  = ROOT.TGraphErrors(n_runs)
        in_fwhm_graph = ROOT.TGraphErrors(n_runs)
        
        in_out_graphs.append(in_out_graph)
        in_fwhm_graphs.append(in_fwhm_graph)

    n = 0
    with alive_bar(n_runs_fitted, title="filling data  ", bar="smooth", spinner="squares", unit="runs") as bar:
        for config in configs:
        
            index = unique_thicknesses.index(config.dz)
            in_out_graph  = in_out_graphs[index]
            in_fwhm_graph = in_fwhm_graphs[index]

            in_out_graph.SetPoint(n,      config.Ein     / MeV, config.Eout     / MeV)
            in_out_graph.SetPointError(n, config.Ein_err / MeV, config.Eout_err / MeV)
        
            in_fwhm_graph.SetPoint(n,      config.Ein     / MeV, config.FWHM()     / MeV)
            in_fwhm_graph.SetPointError(n, config.Ein_err / MeV, config.FWHM_err() / MeV)
        
            n += 1
            bar()

    file = ROOT.TFile.Open(args.output_file, "RECREATE")
    
    dE_dz_graph = ROOT.TGraphErrors(n_thicknesses)
    n = 0
    for thickness, in_out_graph, in_fwhm_graph in zip(unique_thicknesses, in_out_graphs, in_fwhm_graphs):
        in_out_func = ROOT.TF1("funcEinEout", "pol1", energy_in_min / MeV, energy_in_max / MeV)
        in_out_graph.Fit(in_out_func, "QE")
        scale     = in_out_func.GetParameter(1)
        scale_err = in_out_func.GetParError(1)
        dE        = in_out_func.GetParameter(0) * MeV
        dE_err    = in_out_func.GetParError(0) * MeV
        
        dE_dz_graph.SetPoint(n,      thickness / um, -dE     / MeV)
        dE_dz_graph.SetPointError(n, 0.0,             dE_err / MeV)

        in_out_graph.GetXaxis().SetTitle("E_in  [MeV]")
        in_out_graph.GetYaxis().SetTitle("E_out [MeV]")
        in_out_graph.SetLineStyle(0)
        in_out_graph.Write("graphEinEout")

        in_fwhm_graph.GetXaxis().SetTitle("E_in [MeV]")
        in_fwhm_graph.GetYaxis().SetTitle("FWHM [MeV]")
        in_fwhm_graph.SetLineStyle(0)
        in_fwhm_graph.Write("graphEinFWHM")
        
        n += 1
    dE_dz_graph.GetXaxis().SetTitle("\\Delta z [um]")
    dE_dz_graph.GetYaxis().SetTitle("\\Delta E [MeV]")
    dE_dz_graph.SetLineStyle(0)
    dE_dz_graph.Write("graphDEDZ")
    
    file.Close()
    
    print(f"TOTAL  RUNS: {n_runs}")
    print(f"FITTED RUNS: {n_runs_fitted}")
    print(f"FIT EFF:     {(n_runs_fitted/n_runs*100):.1f}%")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
