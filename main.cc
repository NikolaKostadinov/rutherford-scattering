#include <G4RunManager.hh>

#ifdef   G4MULTITHREADED
#include <G4MTRunManager.hh>
#endif

#include <G4UImanager.hh>

#include "include/RutherfordUnitDefinition.hh"
#include "include/RutherfordPhysicsList.hh"
#include "include/RutherfordDetectorConstruction.hh"
#include "include/RutherfordActionInitialization.hh"
#include "include/RutherfordCommands.h"
#include "include/RutherfordArgument.hh"
#include "include/RutherfordArgumentParser.hh"

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheSeed(time(NULL));
	
	G4RunManager* runManager =
	#ifdef G4MULTITHREADED
		new G4MTRunManager();
	#else
		new G4RunManager();
	#endif
	
	RutherfordUnitDefinition();
	
	runManager->SetUserInitialization(new RutherfordPhysicsList());
	runManager->SetUserInitialization(new RutherfordDetectorConstruction());
	runManager->SetUserInitialization(new RutherfordActionInitialization());
	
	G4cout.precision(1);
	G4cout.setf(G4IOFixed);

	G4Vector<RutherfordArgument> arguments =
	{
		RutherfordArgument("--macro",     "-m", MACRO_CMD,                      "file",   "macro file path (all other arguments will be ignored if macro file is provided)"),
		RutherfordArgument("--jobs",      "-j", RUN_THREADS_CMD,                "number", "number of concurent jobs (events)"),
		RutherfordArgument("--output",    "-o", ANALYSIS_FILE_CMD,              "file",   "output analysis file path"),
		RutherfordArgument("--temp",      "-t", DETECTOR_TEMPERATURE_CMD,       "value",  "detector temperature"),
		RutherfordArgument("--atomic-n",  "-Z", DETECTOR_ATOMIC_NUMBER_CMD,     "value",  "detector atomic number"),
		RutherfordArgument("--n-density", "-a", DETECTOR_NUMBER_DENSITY_CMD,    "value",  "detector number density of atoms"),
		RutherfordArgument("--radius",    "-r", DETECTOR_RADIUS_CMD,            "value",  "detector radius"),
		RutherfordArgument("--thickness", "-z", DETECTOR_THICKNESS_CMD,         "value",  "detector thickness"),
		RutherfordArgument("--particle",  "-p", GENERATOR_PRIMARY_PARTICLE_CMD, "type",   "primary particle"),
		RutherfordArgument("--energy",    "-e", GENERATOR_PRIMARY_ENERGY_CMD,   "value",  "particle initial energy"),
		RutherfordArgument("--distance",  "-d", GENERATOR_PRIMARY_DISTANCE_CMD, "value",  "particle initial distance"),
		RutherfordArgument("--n-events",  "-n", RUN_SIMULATION_CMD,             "number", "number of events")
	};
	
	auto* uiManager = G4UImanager::GetUIpointer();
	uiManager->SetCoutDestination(nullptr);
	RutherfordArgumentParser(argc, argv, arguments, uiManager);
	
	exit(0);
}
