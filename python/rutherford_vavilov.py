import ROOT

from rutherford_physics import *
from rutherford_constants import *

def ir_scale(vavilov_threshold):

    vavilov_lambda = lambda x, par: vavilov_density(x[0] * MeV) / (1/um)
    
    vavilov_func = ROOT.TF1("vavilov", vavilov_lambda, 0, ALPHA_MASS / MeV)

    classical_cutoff = 0.25 * ALPHA_MASS / ELECTRON_MASS * MEAN_EXCITATION_ENERGY
    ir_cutoff = vavilov_func.GetX(vavilov_threshold / (1/um), classical_cutoff / MeV, 2*classical_cutoff / MeV) * MeV

    return ir_cutoff

def uv_scale(vavilov_threshold):

    vavilov_lambda = lambda x, par: vavilov_density(x[0] * MeV) / (1/um)
    
    vavilov_func = ROOT.TF1("vavilov", vavilov_lambda, 0, ALPHA_MASS / MeV)

    classical_cutoff = 0.25 * ALPHA_MASS / ELECTRON_MASS * MEAN_EXCITATION_ENERGY
    uv_cutoff = vavilov_func.GetX(vavilov_threshold / (1/um), 2*classical_cutoff / MeV, ALPHA_MASS / MeV) * MeV

    return uv_cutoff


def main():

    ir_cutoff = ir_scale(10 * 1/um)
    uv_cutoff = uv_scale(10 * 1/um)

    print(f"low  energy regime below {(ir_cutoff / MeV):.2f} MeV")
    print(f"high energy regime above {(uv_cutoff / MeV):.1f} MeV")

if __name__ == "__main__":
    main()
