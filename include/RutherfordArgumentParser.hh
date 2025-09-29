#ifndef ARGUMENT_PARSER_HH
#define ARGUMENT_PARSER_HH

#include <G4UImanager.hh>

#include "RutherfordArgument.hh"
#include "RutherfordPrint.hh"
#include "RutherfordDefaults.h"


void RutherfordArgumentParser(int argc, char** argv, G4Vector<RutherfordArgument> arguments, G4UImanager* uiManager)
{
	//
	// ok so argument parsing is not one of my strong sides
	// the following lines of code iterate over a vector of already defined cli arguments in the main
	// this is spaghetti
	// take your time
	//
	
	if (argc == 1)
	{
		RutherfordPrintNoArguments();
		exit(0);
	}

	for (int i = 1; i < argc; ++i)
	{
		G4String arg = argv[i];

		if (arg.size() > 1 && arg[0] == '-')
		{
			G4String flag = arg;
			G4String value;

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
				else if (flag == HELP_LONG_FLAG || flag == HELP_SHORT_FLAG)
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

#endif
