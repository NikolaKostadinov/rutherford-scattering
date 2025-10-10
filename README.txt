RUTHERFORD SCATTERING

This is my attempt at a Rutherford scattering simulation.
The simulation is based on `GEANT4` written in `C++`.
The analysis is based on `ROOT` written in `Python`.

SIMULATION:

This program simulates a run of multiple events.
Each event is a Rutherford scattering of an initial primary particle with known initial energy `Ein`.
It is directed to a target detector: a homogeneous medium.
The thickness of the detector is labeled as `dz`.
The primary particle passes through the detector.
During their interaction secondary particles are created.
They are delta electrons ionized from the target's atoms.
The secondaries can be measured by the detector.


                            +---------------------------+
                            |\                           \
                            | \                           \
                            |  \           target          \
                            |   \         detector          \
                            |    \                           \
               Ein          |     \                           \
    _                       |      +---------------------------+
   (_)      --------->      |      |                           |
                            +      |                           |
 primary                     \     |                           |
 particle                     \    |                           |
                               \   |                           |
                                \  |                           |
                                 \ |                           |
                                  \|                           |
                                   +---------------------------+
                                   ^                           ^
                                                dz


The simulation is descretized by "steps".
A step is a screenshot of the state of the simulation.
In each step there are particle interactions which are recorded as "hits".
Because this is a simulation, it is constrained by some physical boundaries.
This is the "production cut" which is set around 1keV.
The production cut is an arbitrary energy or length scale for the production of a secodnary particle.
Everything below this scale is considered as "soft" and than ignored.
However secondaries with energies above the production cut are considered as "hard" and than tracked and recorded.
Soft events are treated as primary particle background processes so their effect is not ignored it eventually.
