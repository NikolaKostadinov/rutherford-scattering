from rutherford_constants import *
from rutherford_physics   import *

def rutherford_critical_energy():

    return 0.25 * ALPHA_MASS/ELECTRON_MASS * MEAN_EXCITATION_ENERGY

def main():

    E_crit = rutherford_critical_energy()

    print(f"critical energy: {(E_crit / MeV):.2f} MeV")

if __name__ == "__main__":
    main()
