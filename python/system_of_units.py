import scipy.constants

HBAR_C = scipy.constants.hbar * scipy.constants.c / scipy.constants.e # in [eV*m]

# ENERGY UNITS
eV  = 1e+0
keV = 1e+3  * eV
MeV = 1e+6  * eV
GeV = 1e+9  * eV
TeV = 1e+12 * eV

# LENGTH UNITS
m  = 1 / HBAR_C / eV
cm = 1e-2 * m
mm = 1e-3 * m
um = 1e-6 * m
nm = 1e-9 * m
