import argparse

from concurrent.futures import ProcessPoolExecutor, as_completed

from rutherford_scales import *

from alive_progress import alive_bar

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("output_file",           type=str,   default="./.data/analysis.root", help="path to analysis output file")
    parser.add_argument("-j", "--jobs",          type=int,   default=1,                       help="number of concurent jobs")
    parser.add_argument("-t", "--thickness-min", type=float, default=1.0,                     help="minimum foil thickness (in um)")
    parser.add_argument("-T", "--thickness-max", type=float, default=2.0,                     help="maximum foil thickness (in um)")
    parser.add_argument("-z", "--thicknesses",   type=int,   default=1,                       help="number of foil thicknesses")
    parser.add_argument("-V", "--vavilov-level", type=float, default=10,                      help="vavilov number threshold")
    args = parser.parse_args()

    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
    ROOT.gErrorIgnoreLevel = ROOT.kFatal

    thickness_min  = args.thickness_min * um
    thickness_max  = args.thickness_max * um
    n_thicknesses  = args.thicknesses

    thicknesses = [ thickness_min + n*(thickness_max - thickness_min)/n_thicknesses for n in range(n_thicknesses) ]
    
    file = ROOT.TFile.Open(args.output_file, "UPDATE")

    GRAPH_IR = "graphIR"
    GRAPH_UV = "graphUV"
   
    ir_graph  = file.Get(GRAPH_IR)
    if not ir_graph: ir_graph = ROOT.TGraph(n_thicknesses)

    uv_graph  = file.Get(GRAPH_UV)
    if not uv_graph: uv_graph = ROOT.TGraph(n_thicknesses)

    with ProcessPoolExecutor(max_workers = args.jobs) as executor:
        try:
            futures = {
                executor.submit(
                    ir_uv_cutoffs,
                    args.vavilov_level / thickness
                ): i
                for i, thickness in enumerate(thicknesses)
            }

            with alive_bar(n_thicknesses, title="calculating regime scales", bar="smooth", spinner="circles", unit=" geometries", dual_line=True) as bar:
                for future in as_completed(futures):
                    n = futures[future]
                    ir_cutoff, uv_cutoff = future.result()
                    ir_graph.SetPoint(n, ir_cutoff / MeV, thicknesses[n] / um)
                    uv_graph.SetPoint(n, uv_cutoff / MeV, thicknesses[n] / um)
                    bar()

        except KeyboardInterrupt:
            executor.shutdown(wait=False, cancel_futures=True)
    
    ir_graph.SetTitle("IR Regime")
    ir_graph.GetXaxis().SetTitle("Ein [MeV]")
    ir_graph.GetYaxis().SetTitle("dz  [um]")
    ir_graph.SetLineStyle(0)
    ir_graph.Write(GRAPH_IR, ROOT.TObject.kOverwrite)

    uv_graph.SetTitle("UV Regime")
    uv_graph.GetXaxis().SetTitle("Ein [MeV]")
    uv_graph.GetYaxis().SetTitle("dz  [um]")
    uv_graph.SetLineStyle(0)
    uv_graph.Write(GRAPH_UV, ROOT.TObject.kOverwrite)

    file.Close()

if __name__ == "__main__":
    main()
