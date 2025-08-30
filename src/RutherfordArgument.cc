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

G4String RutherfordArgument::GetType() const
{
	return fType;
}

void RutherfordArgument::SetValue(G4String value)
{
	fValue = value;
}

void RutherfordArgument::PrintDescription(int longSize, int shortSize, int typeSize) const
{
	// --flag / -f [type] description
	G4cout << fLongFlag;
	G4cout << std::string((longSize + MARGIN_SIZE) - fLongFlag.size(), ' ');
	G4cout << "/";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << fShortFlag;
	G4cout << std::string((shortSize + MARGIN_SIZE) - fShortFlag.size(), ' ');
	G4cout << "[" << fType << "]";
	G4cout << std::string((typeSize + MARGIN_SIZE) - fType.size(), ' ');
	G4cout << fDescription;
	G4cout << G4endl;
}

void RutherfordArgument::Execute(G4UImanager* uiManager) const
{
	if (fValue.empty()) return;
	std::string command = fCommand + DELIM + fValue;
	
	std::istringstream commandStream(command);
	std::string commandLine;
	while(std::getline(commandStream, commandLine))
	{
		if (commandLine.empty()) continue;
		G4cout << commandLine << G4endl;
		uiManager->ApplyCommand(commandLine);
	}
}
