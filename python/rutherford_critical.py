from particle        import Particle
from system_of_units import *

def main():

    electron = Particle.from_pdgid(11)
    alpha    = Particle.from_pdgid(1000020040)

    electron_mass = electron.mass * MeV
    alpha_mass    = alpha.mass * MeV

    I = 790 * eV

    E_crit = alpha_mass/electron_mass/4 * I

    print(f"critical energy: {(E_crit / MeV):.2f} MeV")

if __name__ == "__main__":
    main()
