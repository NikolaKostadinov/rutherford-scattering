#include "../include/RutherfordArgument.hh"

#include "../include/RutherfordCommands.h"

RutherfordArgument::RutherfordArgument(G4String longFlag, G4String shortFlag, G4String command, G4String type, G4String description)
{
	fLongFlag    = longFlag;
	fShortFlag   = shortFlag;
	fCommand     = command;
	fType        = type;
	fDescription = description;
}

RutherfordArgument::~RutherfordArgument()
{

}

G4String RutherfordArgument::GetLongFlag() const
{
	return fLongFlag;
}

G4String RutherfordArgument::GetShortFlag() const
{
	return fShortFlag;
}

void RutherfordArgument::SetValue(G4String value)
{
	fValue = value;
}

void RutherfordArgument::PrintDescription() const
{
	G4cout << fLongFlag;
	if (fLongFlag != fShortFlag)
		G4cout << " / " << fShortFlag;
	G4cout << " [" << fType << "] ";
	G4cout << fDescription;
	G4cout << G4endl;
}

void RutherfordArgument::Execute(G4UImanager* uiManager) const
{
	std::string command = fCommand + DELIM + fValue;
	
	std::istringstream commandStream(command);
	std::string commandLine;
	while(std::getline(commandStream, commandLine))
	{
		if (commandLine.empty()) continue;
		uiManager->ApplyCommand(commandLine);
	}
}
