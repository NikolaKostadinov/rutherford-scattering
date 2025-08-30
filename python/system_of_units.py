import scipy.constants

HBAR_C = scipy.constants.hbar * scipy.constants.c / scipy.constants.e # in [eV*m]

# ENERGY UNITS
eV  = 1.e+0
keV = 1.e+3  * eV
MeV = 1.e+6  * eV
GeV = 1.e+9  * eV
TeV = 1.e+12 * eV

# LENGTH UNITS
m  = 1 / HBAR_C / eV
cm = 1.e-2 * m
mm = 1.e-3 * m
um = 1.e-6 * m
nm = 1.e-9 * m

# AREA UNITS
m2   = m**2
cm2  = cm**2
mm2  = mm**2
um2  = um**2
nm2  = nm**2
#
barn  = 1.e-28 * m2
mbarn = 1.e-3 * barn
ubarn = 1.e-6 * barn

# VOLUME UNITS
m3  = m**3
cm3 = cm**3
mm3 = mm**3
um3 = um**3
nm3 = nm**3
