void RutherfordArgumentParser(G4UImanager* uiManager, int argc, char** argv)
{
	std::string macro;
	std::string thickness;
	std::string energy;
	std::string distance;
	std::string nEvents;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		
		if ((arg == "-m" || arg == "--macro") && i+1 < argc)
		{
			macro = argv[++i];
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
		else if (arg == "--help" || arg == "-h")
		{
			std::cout <<
				"Usage: rutherford-scattering [options]\n"
				"  -m / --macro <file>             macro file path (all other args are ignored if not false)\n"
				"  -z / --thickness <value in um>  foil thickness\n"
				"  -e / --energy <value in MeV>    initial energy\n"
				"  -d / --distance <value in cm>   initial distance\n"
				"  -n / --n-events <value>         number of events\n";
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
		if (!thickness.empty())
			uiManager->ApplyCommand("/geo/foil/thickness " + thickness + " um");

		if (!energy.empty())
			uiManager->ApplyCommand("/gen/energy " + energy + " MeV");
		
		if (!distance.empty())
			uiManager->ApplyCommand("/gen/distance " + distance + " cm");
		
		uiManager->ApplyCommand("/run/initialize");
		if (!nEvents.empty())
			uiManager->ApplyCommand("/run/beamOn " + nEvents);
	}
}
