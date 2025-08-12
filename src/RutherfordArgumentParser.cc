#include "../include/RutherfordArgumentParser.hh"

#include "../include/RutherfordDefaults.h"

void RutherfordArgumentParser(G4UImanager* uiManager, int argc, char** argv)
{
	std::string macro;
	std::string output;
	std::string thickness;
	std::string energy;
	std::string distance;
	std::string nEvents;
	std::string eMin;
	std::string eMax;
	std::string nEnergies;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		
		if (arg == "-v" || arg == "--version")
		{
			std::cout << RUTHERFORD_VERSION << std::endl;
		}
		else if ((arg == "-m" || arg == "--macro") && i+1 < argc)
		{
			macro = argv[++i];
		}
		else if ((arg == "-o" || arg == "--output") && i+1 < argc)
		{
			output = argv[++i];
		}
		else if ((arg == "-z" || arg == "--thickness") && i+1 < argc)
		{
			thickness = argv[++i];
		}
		else if ((arg == "-e" || arg == "--energy") && i+1 < argc)
		{
			energy = argv[++i];
		}
		else if ((arg == "-d" || arg == "--distance") && i+1 < argc)
		{
			distance = argv[++i];
		}
		else if ((arg == "-n" || arg == "--n-events") && i+1 < argc)
		{
			nEvents = argv[++i];
		}
		else if ((arg == "-i" || arg == "--energy-min") && i+1 < argc)
		{
			eMin = argv[++i];
		}
		else if ((arg == "-u" || arg == "--energy-max") && i+1 < argc)
		{
			eMax = argv[++i];
		}
		else if ((arg == "-b" || arg == "--energy-bins") && i+1 < argc)
		{
			nEnergies = argv[++i];
		}
		else if (arg == "-h" || arg == "--help")
		{
			std::cout <<
				"Usage: rutherford-scattering [options]\n\n"
				"  -v / --version                    version\n"
				"  -m / --macro [file]               macro file path (all other args are ignored if not false)\n"
				"  -o / --output [file]              output analysis file path\n"
				"  -z / --thickness [value in um]    foil thickness\n"
				"  -e / --energy [value in MeV]      initial energy\n"
				"  -d / --distance [value in cm]     initial distance\n"
				"  -n / --n-events [value]           number of events\n"
				"  -i / --energy-min [value in MeV]  minimal final energy\n"
				"  -u / --energy-max [value in MeV]  maximum final energy\n"
				"  -b / --energy-bins [value]        number of final energy bins\n"
				<< std::endl;
			exit(0);
		}
		else
		{
			std::cerr << "Unknown argument: " << arg << std::endl;
			exit(1);
		}
	}

	if (!macro.empty())
	{
		uiManager->ApplyCommand("/control/execute " + macro);
	}
	else
	{
		if (!output.empty())	uiManager->ApplyCommand("/analysis/file " + output);
		if (!thickness.empty())	uiManager->ApplyCommand("/geo/foil/thickness " + thickness + " um");
		if (!energy.empty())	uiManager->ApplyCommand("/gen/energy " + energy + " MeV");
		if (!distance.empty())	uiManager->ApplyCommand("/gen/distance " + distance + " cm");
		if (!eMin.empty())	uiManager->ApplyCommand("/analysis/energy/min " + eMin + " MeV");
		if (!eMax.empty())	uiManager->ApplyCommand("/analysis/energy/max " + eMax + " MeV");
		if (!nEnergies.empty())	uiManager->ApplyCommand("/analysis/energy/bins " + nEnergies);

		uiManager->ApplyCommand("/run/initialize");
		
		if (!nEvents.empty())	uiManager->ApplyCommand("/run/beamOn " + nEvents);
		else			uiManager->ApplyCommand("/run/beamOn " + DEFAULT_N_EVENTS);
	}
}
