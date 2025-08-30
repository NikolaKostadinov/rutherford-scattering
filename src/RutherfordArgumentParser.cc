#include "../include/RutherfordArgumentParser.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

void RutherfordPrintVersion()
{
	G4cout << RUTHERFORD_NAME << " " << RUTHERFORD_VERSION << G4endl;
}

void RutherfordPrintHelp(const std::vector<RutherfordArgument>& arguments)
{
	int longSize   = 0;
	int shortSize  = 0;
	int typeSize   = 0;

	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
	{
		int thisLongSize  = argument->GetLongFlag().size();
		int thisShortSize = argument->GetShortFlag().size();
		int thisTypeSize  = argument->GetType().size();

		if (longSize  < thisLongSize)  longSize  = thisLongSize;
		if (shortSize < thisShortSize) shortSize = thisShortSize;
		if (typeSize  < thisTypeSize)  typeSize  = thisTypeSize;
	}
	
	// rutherford-scattering [options]
	G4cout << RUTHERFORD_PROGRAM;
	G4cout << std::string((TAB_SIZE + longSize + MARGIN_SIZE + 1 + MARGIN_SIZE + shortSize + MARGIN_SIZE) - (sizeof(RUTHERFORD_PROGRAM) - 1), ' ');
	G4cout << "[options]";
	G4cout << G4endl;
	G4cout << G4endl;
	
	// --version
	G4cout << std::string(TAB_SIZE, ' ');
	G4cout << VERSION_FLAG;
	G4cout << std::string((longSize + MARGIN_SIZE + 1 + MARGIN_SIZE + shortSize + MARGIN_SIZE + 1 + typeSize + 1 + MARGIN_SIZE) - (sizeof(VERSION_FLAG) - 1), ' ');
	G4cout << "version of " << RUTHERFORD_PROGRAM;
	G4cout << G4endl;
	
	// --help / -h
	G4cout << std::string(TAB_SIZE, ' ');
	G4cout << HELP_LONG_FLAG;
	G4cout << std::string((longSize + MARGIN_SIZE) - (sizeof(HELP_LONG_FLAG) - 1), ' ');
	G4cout << "/";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << HELP_SHORT_FLAG;
	G4cout << std::string((shortSize + MARGIN_SIZE + 1 + typeSize + 1 + MARGIN_SIZE) - (sizeof(HELP_SHORT_FLAG) - 1), ' ');
	G4cout << "help (this is help)";
	G4cout << G4endl;
	
	// --flag / -f [type] description
	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
	{
		G4cout << std::string(TAB_SIZE, ' ');
		argument->PrintDescription(longSize, shortSize, typeSize);
	}

	G4cout << G4endl;

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
