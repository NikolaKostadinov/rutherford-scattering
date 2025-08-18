from dataclasses import dataclass
from numpy       import sqrt

FWHM_CONST = 2.3548200450309493

@dataclass
class RutherfordConfig:
    
    dz:         float = 0.0
    dz_err:     float = 0.0

    Ein:        float = 0.0
    Ein_err:    float = 0.0
    
    Eout:       float = 0.0
    Eout_err:   float = 0.0
    
    sigmaE:     float = 0.0
    sigmaE_err: float = 0.0

    d:          float = 0.0
    d_err:      float = 0.0

    def dE(self):
        return self.Ein - self.Eout

    def dE_err(self):
        return sqrt(self.Ein_err**2 + self.Eout_err**2)
    
    def FWHM(self):
            return FWHM_CONST * self.sigmaE

    def FWHM_err(self):
            return FWHM_CONST * self.sigmaE_err
