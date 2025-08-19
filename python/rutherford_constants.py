from particle        import Particle
from system_of_units import *

# Particles
_ELECTRON = Particle.from_pdgid(11)
_ALPHA    = Particle.from_pdgid(1000020040)

ELECTRON_MASS = _ELECTRON.mass * MeV
ALPHA_MASS    = _ALPHA.mass * MeV

ELECTRON_CHARGE = -1
ALPHA_CHARGE    = +2

# Gold Constants
Z = 79
MEAN_EXCITATION_ENERGY = 790 * eV
NUMBER_DENSITY = 5.91e+22 / cm**3

CLASSICAL_THRESHOLD = 0.25 * ALPHA_MASS / ELECTRON_MASS * MEAN_EXCITATION_ENERGY

# Physical Constants
FINE_STRUCTURE = 1/137

PI = 3.14
