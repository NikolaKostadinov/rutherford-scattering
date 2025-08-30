#include "../include/RutherfordArgumentParser.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

void RutherfordPrintVersion()
{
	G4cout << RUTHERFORD_NAME << " " << RUTHERFORD_VERSION << G4endl;
}

void RutherfordPrintHelp(const std::vector<RutherfordArgument>& arguments)
{
	G4cout << RUTHERFORD_PROGRAM << " [options]" << G4endl;
	G4cout << "\t" << VERSION_FLAG << " version" << G4endl;
	G4cout << "\t" << HELP_LONG_FLAG << " / " << HELP_SHORT_FLAG << " help" << G4endl;
	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
	{
		G4cout << "\t";
		argument->PrintDescription();
	}
}

void RutherfordPrintUnknownFlag(G4String flag)
{
	G4cout << "[WARNING] UNKNOWN FLAG: " << flag << G4endl;
}

void RutherfordArgumentParser(int argc, char** argv, std::vector<RutherfordArgument> arguments, G4UImanager* uiManager)
{
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
			for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
			{
				if (flag == argument->GetLongFlag() || flag == argument->GetShortFlag())
				{
					isArgFound = true;
					argument->SetValue(value);
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
					RutherfordPrintHelp(arguments);
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

	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
		argument->Execute(uiManager);
}
