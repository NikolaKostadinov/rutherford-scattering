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
	// random engine, random seed
	CLHEP::HepRandom::setTheSeed(time(NULL));
	
	// start Geant4
	G4RunManager* runManager = new G4RunManager();
	
	// define new non Geant4 units
	RutherfordUnitDefinition();
	
	runManager->SetUserInitialization(new RutherfordPhysicsList());
	runManager->SetUserInitialization(new RutherfordDetectorConstruction());
	runManager->SetUserInitialization(new RutherfordActionInitialization());
	
	G4UImanager* uiManager = G4UImanager::GetUIpointer();
	
	// CLI arguments
	std::vector<RutherfordArgument> arguments;
	arguments.push_back(RutherfordArgument("--macro",       "-m", MACRO_CMD,                      "file",   "macro file path (all other arguments will be ignored if macro file is provided)"));
	arguments.push_back(RutherfordArgument("--output",      "-o", ANALYSIS_FILE_CMD,              "file",   "output analysis file path"));
	arguments.push_back(RutherfordArgument("--atomic-n",    "-Z", DETECTOR_ATOMIC_NUMBER_CMD,     "value",  "detector atomic number"));
	arguments.push_back(RutherfordArgument("--n-density",   "-a", DETECTOR_NUMBER_DENSITY_CMD,    "value",  "detector number density of atoms"));
	arguments.push_back(RutherfordArgument("--radius",      "-r", DETECTOR_RADIUS_CMD,            "value",  "detector radius"));
	arguments.push_back(RutherfordArgument("--thickness",   "-z", DETECTOR_THICKNESS_CMD,         "value",  "detector thickness"));
	arguments.push_back(RutherfordArgument("--energy",      "-e", GENERATE_ALPHA_ENERGY_CMD,      "value",  "particle initial energy"));
	arguments.push_back(RutherfordArgument("--distance",    "-d", GENERATE_ALPHA_DISTANCE_CMD,    "value",  "particle initial distance"));
	arguments.push_back(RutherfordArgument("--energy-min",  "-i", ANALYSIS_ALPHA_ENERGY_MIN_CMD,  "value",  "minimum final energy of particle"));
	arguments.push_back(RutherfordArgument("--energy-max",  "-u", ANALYSIS_ALPHA_ENERGY_MAX_CMD,  "value",  "maximum final energy of particle"));
	arguments.push_back(RutherfordArgument("--energy-bins", "-b", ANALYSIS_ALPHA_ENERGY_BINS_CMD, "number", "number of final energy bins"));
	arguments.push_back(RutherfordArgument("--theta-min",   "-S", ANALYSIS_ALPHA_THETA_MIN_CMD,   "angle",  "minimum scattering angle"));
	arguments.push_back(RutherfordArgument("--theta-max",   "-D", ANALYSIS_ALPHA_THETA_MAX_CMD,   "angle",  "maximum scattering angle"));
	arguments.push_back(RutherfordArgument("--theta-bins",  "-B", ANALYSIS_ALPHA_THETA_BINS_CMD,  "number", "number of scattering angle bins"));
	arguments.push_back(RutherfordArgument("--cut",         "-c", CUT_LOW_ENERGY_CMD,             "value",  "low energy production cut"));
	arguments.push_back(RutherfordArgument("--n-events",    "-n", RUN_SIMULATION_CMD,             "number", "number of events"));

	RutherfordArgumentParser(argc, argv, arguments, uiManager);
	
	exit(0);
}
