RUTHERFORD SCATTERING

This is my attempt at a Rutherford scattering simulation.
The simulation is based on `GEANT4` written in `C++`.
The analysis is based on `ROOT` written in `Python`.

SIMULATION:

This program simulates a run of multiple events.
Each event is a Rutherford scattering of an alpha particle with a known initial energy `Ein`.
It is directed to a target golden foil.
The thickness of the foil is labeled as `dz`.
The particle passes through the foil.
It scatters at an angle `theta`, and it loses some energy `dE = Eout - Ein`.
The scattering quantities are recorded in histograms.
At the end of the run the histograms are saved in a `ROOT` file which can be further analyzed.



                            +----+             /|
                            |\    \     Eout   /
                            | \    \          /
                            |  \    \        /\  theta
                            |   \    \      /_|_
                            |    \    \
               Ein          |     \    \
    _                       |      +----+
   (_)      --------->      |      |    |
                            +      |    |
  alpha                      \     |    |
 particle                     \    |    |
                               \   |    |
                                \  |    |
                                 \ |    |
                                  \|    |
                                   +----+
                                   ^    ^
                                     dz


PHYSICS:

It is expected that the output spectrum should be normally distributed.
This distribution should be centered around `Eout = Ein + dE/dz * dz`.
The quantity `dE/dz` is the stopping power of the foil.
The stopping power is expected to match the Bethe-Bloch formula:

.-----------------------------------------------------------------------------------------------.
| dE/dz = - (e2/4pi)2 * 4pi * q2 / me * Z * n * 1/beta2 * ( log[2me/I * beta * gamma]  - beta2) |
'-----------------------------------------------------------------------------------------------'

`e2/4pi` is the fine structure constant.
`q` is the charge of the alpha particle which is `q = +2`.
`me` is the mass of the electron which is `me = 551 keV`.
`Z` is the atomic number of the foil which is `Z = 79`.
`n` is the number density of the foil.
`I` is the mean excitation energy defined by the geometrical average of the electrons' binding energy:

.----------------------.
| logI = < log Ebind > |
'----------------------'

`beta` and `gamma` are the relativistic factors.
They are derived from the alpha particle's energy and mass:

.-----------------.
| gamma = E/m + 1 |
'-----------------'

During the analysis of the simulation i found out that this expectation matches the simulation data only in a certain energy range.
Considering energy spectra below or above this range results in unexpected behavior.
This is why we need 3 regimes:
* low  energy regime
* mid  energy regime
* high energy regime
The cutoffs of these regimes can be calculated with the Vavilov number.
The Vavilov number is defined as the minimum number of alpha-electron collisions:

.-----------------.
| kappa = dE/Tmax |
'-----------------'

`Tmax` is the maximum transferred kinetic energy during an alpha-electron collision.
It can be calculated using:

.------------------------.
| Tmax = 2 * m2 * me / s |
'------------------------'

Here by `s` we mean the timelike Mandelstam variable which can be calculated by utilizing the hyperbolic cosine theorem.

.-----------------------------------.
| s = m2 + 2 * m * me * gamma + me2 |
'-----------------------------------'

Given a threshold value for the Vavilov number (like `kappa = 10`) one can calculate the two energies for which the Vavilov number is at the threshold.
For a 1um thick gold foil one can calculate that the energies for this threshold are around the values:

[ low energy regime ]----->( 1.45 MeV )----->[ mid energy regime ]----->( 31.7 MeV )----->[ high energy regime ]


PROGRAMS:
	
* simulation (executable): rutherford-scattering
* run generator (script):  rutherford_run_generator.py
* analyzer (script):       rutherford_analuzer.py


SIMULATION COMPILATION:

To compile the simulation make a build directory.
Setup `CMake` and `make` the simulation.

$ make


RUN SIMULATION:

After the simulation is comiled, locate it in your build directory and execute it with your desired parameters.
There are two ways to do that.
You can write a macro file for `Geant4` like `run.mac` and provide it to the simulation:

$ rutherford-scattering --macro [macro file path]

You can also provide the desired parameters inline:

$ rutherford-scattering \\
	--output [output analysis file path] \\
	--thickness [foil thickness (in um)] \\
	--energy [INITIAL energy (in MeV)] \\
	--distance [INITIAL distance (in cm)] \\
	--n-events [number of events] \\
	--energy-min [minimal FINAL energy (in MeV)] \\
	--energy-max [maximum FINAL energy (in MeV)] \\
	--energy-bins [number of FINAL energy bins]

If you want to specify a range of initial conditions you would need to run the simulation many times.
This task is automized by the `Python` script `rutherford_run_generator.py` which can run as many as you want concurent simulation:

$ python rutherford_run_generator.py [output directory] \\
	--simulation [path to simulation] \\
	--jobs [number of concurent jobs] \\
	--n-events [number of events per run] \\
	--thickness-min [minimum foil thickness (in um)] \\
	--thickness-max [maximum foil thickness (in um)] \\
	--thicknesses [number of foil thicknesses] \\
	--energy-min [minimum INITIAL energy (in MeV)] \\
	--energy-max [maximum INITIAL energy (in MeV)] \\
	--energies [number of INITIAL energies] \\
	--energy-bins [number of FINAL energy bins]
