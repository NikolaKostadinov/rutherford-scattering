#include <iostream>
#include <ctime>
#include <vector>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <Randomize.hh>

#include "include/RutherfordCommands.h"
#include "include/RutherfordArgument.hh"
#include "include/RutherfordArgumentParser.hh"
#include "include/RutherfordUnitDefinition.hh"
#include "include/RutherfordPhysicsList.hh"
#include "include/RutherfordDetectorConstruction.hh"
#include "include/RutherfordActionInitialization.hh"

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheSeed(time(NULL));

	auto runManager = new G4RunManager();
	
	RutherfordUnitDefinition();
	
	runManager->SetUserInitialization(new RutherfordPhysicsList());
	runManager->SetUserInitialization(new RutherfordDetectorConstruction());
	runManager->SetUserInitialization(new RutherfordActionInitialization());
	
	G4UImanager* uiManager = G4UImanager::GetUIpointer();
	
	std::vector<RutherfordArgument> arguments;
	arguments.push_back(RutherfordArgument("--macro",       "-m", MACRO_CMD,                   "file",   "macro file path (all other arguments will be ignored if macro file is provided)"));
	arguments.push_back(RutherfordArgument("--output",      "-o", OUTPUT_CMD,                  "file",   "output analysis file path"));
	arguments.push_back(RutherfordArgument("--atomic-n",    "-Z", DETECTOR_ATOMIC_NUMBER_CMD,  "value",  "detector atomic number"));
	arguments.push_back(RutherfordArgument("--n-density",   "-a", DETECTOR_NUMBER_DENSITY_CMD, "value",  "detector number density of atoms"));
	arguments.push_back(RutherfordArgument("--thickness",   "-z", DETECTOR_THICKNESS_CMD,      "value",  "detector thickness"));
	arguments.push_back(RutherfordArgument("--energy",      "-e", PARTICLE_ENERGY_CMD,         "value",  "particle initial energy"));
	arguments.push_back(RutherfordArgument("--distance",    "-d", PARTICLE_DISTANCE_CMD,       "value",  "particle initial distance"));
	arguments.push_back(RutherfordArgument("--energy-min",  "-i", ANALYSIS_ENERGY_MIN_CMD,     "value",  "minimum final energy of particle"));
	arguments.push_back(RutherfordArgument("--energy-max",  "-u", ANALYSIS_ENERGY_MAX_CMD,     "value",  "maximum final energy of particle"));
	arguments.push_back(RutherfordArgument("--energy-bins", "-b", ANALYSIS_ENERGY_BINS_CMD,    "number", "number of final energy bins"));
	arguments.push_back(RutherfordArgument("--n-events",    "-n", RUN_SIMULATION_CMD,          "number", "number of events"));

	RutherfordArgumentParser(argc, argv, arguments, uiManager);

	delete runManager;
	return 0;
}
