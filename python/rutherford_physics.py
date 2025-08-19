from numpy import sqrt, log

from rutherford_constants import *

# Lorentz Factor (Gamma Factor)
def cosh(energy, mass):

    return energy/mass + 1

# Beta * Gamma Factor
def sinh(*params):
    
    return sqrt(cosh(*params)**2 - 1)

# Relative Proper Velocity (Beta Factor)
def tanh(*params):

    return sinh(*params)/cosh(*params)
    
# Maximum Transfered Kinetic Energy Per Mass (of moving particle)
# (other particle is considered at rest)
def max_kinetic_factor(energy, this_mass, other_mass):

    gamma      = cosh(energy, this_mass)
    beta_gamma = sinh(energy, this_mass)
    
    # Hyperbolic Cosine Theorem
    s_param = this_mass**2 + 2*this_mass*other_mass*gamma + other_mass**2

    return 2*this_mass*other_mass/s_param*beta_gamma**2

# Vavilov Number (number of collisions)
def vavilov_number(energy_in, energy_out, this_mass=ALPHA_MASS, other_mass=ELECTRON_MASS):

    delta_energy = energy_in - energy_out
    t_max = this_mass*max_kinetic_factor(energy_in, this_mass, other_mass)
    
    return delta_energy/t_max

def bethe_stopping_power(energy, mass=ALPHA_MASS, charge=ALPHA_CHARGE, atomic_number=Z, number_density=NUMBER_DENSITY, mean_excitation_energy=MEAN_EXCITATION_ENERGY):
    
    beta_gamma = sinh(energy, mass)
    beta       = tanh(energy, mass)
    
    excitation_factor = 0.5*mean_excitation_energy/ELECTRON_MASS
    bethe = charge**2 / beta**2 * ( log(beta_gamma**2/excitation_factor) - beta**2 )
    
    return FINE_STRUCTURE**2 * 4*PI/ELECTRON_MASS * atomic_number * number_density * bethe

def vavilov_density(energy, mass=ALPHA_MASS, charge=ALPHA_CHARGE, atomic_number=Z, number_density=NUMBER_DENSITY, mean_excitation_energy=MEAN_EXCITATION_ENERGY):

    stopping_power = bethe_stopping_power(energy,
        mass,
        charge,
        atomic_number,
        number_density,
        mean_excitation_energy
    )

    t_max = mass * max_kinetic_factor(energy, mass, ELECTRON_MASS)

    return stopping_power / t_max
