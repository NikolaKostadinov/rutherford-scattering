import argparse

import ROOT

from math import isnan

from rutherford_physics import *
from rutherford_constants import *

def vavilov_mode():

    vavilov_lambda = lambda x, par: vavilov_density(x[0] * MeV) / (1/um)
    vavilov_func = ROOT.TF1("vavilov", vavilov_lambda, CLASSICAL_THRESHOLD / MeV, ALPHA_MASS / MeV)
    
    mode = vavilov_func.GetMaximumX(CLASSICAL_THRESHOLD / MeV, ALPHA_MASS / MeV) * MeV
    
    if isnan(mode):
        mode = CLASSICAL_THRESHOLD

    return mode

def ir_uv_cutoffs(vavilov_threshold):

    vavilov_lambda = lambda x, par: vavilov_density(x[0] * MeV) / (1/um)
    vavilov_func = ROOT.TF1("vavilov", vavilov_lambda, CLASSICAL_THRESHOLD / MeV, ALPHA_MASS / MeV)
    mode = vavilov_mode()
    
    ir_cutoff = vavilov_func.GetX(vavilov_threshold / (1/um), CLASSICAL_THRESHOLD / MeV, mode / MeV) * MeV
    uv_cutoff = vavilov_func.GetX(vavilov_threshold / (1/um), mode / MeV, ALPHA_MASS / MeV) * MeV
    
    if isnan(ir_cutoff):
        ir_cutoff = mode
    if isnan(uv_cutoff):    
        uv_cutoff = mode

    return ir_cutoff, uv_cutoff

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-z", "--thickness",     type=float, default=1,    help="thickness (in um)")
    parser.add_argument("-V", "--vavilov-level", type=float, default=10.0, help="vavilov number threshold")
    args = parser.parse_args()

    ROOT.gROOT.SetBatch(True)
    ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
    ROOT.gErrorIgnoreLevel = ROOT.kFatal

    dz    = args.thickness * um
    kappa = args.vavilov_level
    kappa_dz = kappa / dz

    ir_cutoff, uv_cutoff = ir_uv_cutoffs(kappa/dz)
    mode = vavilov_mode()
    peak = vavilov_density(mode)

    dz_min = kappa / peak

    print()
    print(f"vavilov number                         {kappa:.1f}")
    print(f"foil thickness                         {(dz / um):.2f} um")
    print(f"vavilov density                        {(kappa_dz / (1/um)):.1f} per um")
    print()
    print(f"low  energy regime below  (IR cutoff)  {(ir_cutoff / MeV):.2f} MeV")
    print(f"mid  energy regime around (peak)       {(mode / MeV):.2f} MeV")
    print(f"high energy regime above  (UV cutoff)  {(uv_cutoff / MeV):.1f} MeV")
    print()
    print(f"max vavilov density       (at peak)    {(peak / (1/um)):.1f} per um")
    print(f"min foil thickness                     {(dz_min / nm):.1f} nm")
    print()

if __name__ == "__main__":
    main()
