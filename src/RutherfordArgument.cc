#include "../include/RutherfordArgument.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

RutherfordArgument::RutherfordArgument(G4String longFlag, G4String shortFlag, G4String command, G4String type, G4String description)
{
	fLongFlag    = longFlag;
	fShortFlag   = shortFlag;
	fCommand     = command;
	fType        = type;
	fDescription = description;
}

void RutherfordArgument::Execute(G4UImanager* uiManager) const
{
	if (fValue.empty()) return;

	G4String command = fCommand + DELIM + fValue;
	
	G4IStringStream commandStream(command);
	G4String commandLine;
	while (G4GetLine(commandStream, commandLine))
	{
		if (!commandLine.empty())
			uiManager->ApplyCommand(commandLine);
	}
}