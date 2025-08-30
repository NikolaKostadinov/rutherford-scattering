#include "../include/RutherfordArgumentParser.hh"

#include "../include/RutherfordDefaults.h"

#include "../include/RutherfordArgument.hh"
#include "../include/RutherfordCommands.h"
#include <vector>

void RutherfordPrintVersion()
{
	G4cout << RUTHERFORD_NAME << " " << RUTHERFORD_VERSION << G4endl;
}

void RutherfordPrintHelp(const std::vector<RutherfordArgument>& defArgs)
{
	G4cout << RUTHERFORD_PROGRAM << " [options]" << G4endl;
	G4cout << "\t" << VERSION_FLAG << " version" << G4endl;
	G4cout << "\t" << HELP_LONG_FLAG << " / " << HELP_SHORT_FLAG << " help" << G4endl;
	for (auto defArg = defArgs.begin(); defArg != defArgs.end(); ++defArg)
	{
		G4cout << "\t";
		defArg->PrintDescription();
	}
}

void RutherfordPrintUnknownFlag(G4String flag)
{
	G4cout << "[WARNING] UNKNOWN FLAG: " << flag << G4endl;
}

void RutherfordArgumentParser(G4UImanager* uiManager, int argc, char** argv)
{
	std::vector<RutherfordArgument> defArgs;
	defArgs.push_back(RutherfordArgument("--macro",       "-m", MACRO_CMD,                   "file",   "macro file path (all other args are ignored if macro file is provided)"));
	defArgs.push_back(RutherfordArgument("--output",      "-o", OUTPUT_CMD,                  "file",   "output analysis file path"));
	defArgs.push_back(RutherfordArgument("--atomic-n",    "-Z", DETECTOR_ATOMIC_NUMBER_CMD,  "value",  "detector atomic number"));
	defArgs.push_back(RutherfordArgument("--n-density",   "-a", DETECTOR_NUMBER_DENSITY_CMD, "value",  "detector atomic number density"));
	defArgs.push_back(RutherfordArgument("--thickness",   "-z", DETECTOR_THICKNESS_CMD,      "value",  "detector thickness"));
	defArgs.push_back(RutherfordArgument("--energy",      "-e", PARTICLE_ENERGY_CMD,         "value",  "particle initial energy"));
	defArgs.push_back(RutherfordArgument("--distance",    "-d", PARTICLE_DISTANCE_CMD,       "value",  "particle initial distance"));
	defArgs.push_back(RutherfordArgument("--energy-min",  "-i", ANALYSIS_ENERGY_MIN_CMD,     "value",  "minimum final energy of particle"));
	defArgs.push_back(RutherfordArgument("--energy-max",  "-u", ANALYSIS_ENERGY_MAX_CMD,     "value",  "maximum final energy of particle"));
	defArgs.push_back(RutherfordArgument("--energy-bins", "-b", ANALYSIS_ENERGY_BINS_CMD,    "number", "number of final energy bins"));
	defArgs.push_back(RutherfordArgument("--n-events",    "-n", RUN_SIMULATION_CMD,          "number", "number of events"));

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];

		if (arg.size() > 1 && arg[0] == '-')
		{
			std::string flag = arg;
			std::string value;

			while (i+1 < argc && argv[i+1][0] != '-')
			{
				if (!value.empty()) value += " ";
				value += argv[++i];
			}
			
			bool isArgFound = false;	
			for (auto defArg = defArgs.begin(); defArg != defArgs.end(); ++defArg)
			{
				if (flag == defArg->GetLongFlag() || flag == defArg->GetShortFlag())
				{
					isArgFound = true;
					defArg->SetValue(value);
					break;
				}
				else if (flag == VERSION_FLAG)
				{
					isArgFound = true;
					RutherfordPrintVersion();
					exit(0);
				}
				else if (flag == HELP_SHORT_FLAG || flag == HELP_LONG_FLAG)
				{
					isArgFound = true;
					RutherfordPrintHelp(defArgs);
					exit(0);
				}
				else
				{
					isArgFound = false;
				}
			}
			
			if (!isArgFound)
			{
				RutherfordPrintUnknownFlag(flag);
			}
		}
	}

	for (auto defArg = defArgs.begin(); defArg != defArgs.end(); ++defArg)
		defArg->Execute(uiManager);
}
