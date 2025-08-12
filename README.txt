RUTHERFORD SCATTERING

This is my attempt for a Rutherford scattering simulation.
The simulation is based on `GEANT4` written in `C++` and the analysis: `ROOT` written in `Python`.

PROGRAMS:
	
* simulation: rutherford-scattering
* run generator: rutherford_run_generator.py
* analyzer: rutherford_analuzer.py

MAKE SIMULATION:

$ make

RUN SIMULATION (MACRO FILE):

$ rutherford-scattering --macro run.mac
