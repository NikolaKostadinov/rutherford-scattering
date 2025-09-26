#include "../include/RutherfordRunMessenger.hh"
#include "../include/RutherfordRunAction.hh"

#include <G4UnitsTable.hh>

#include "../include/RutherfordDefaults.h"

RutherfordRunMessenger::RutherfordRunMessenger(RutherfordRunAction* runAction) : fRunAction(runAction)
{
	fDirectory->SetGuidance("Commands for simulation analysis. This includes (only) ROOT histogram setup.");

	fFileOutCmd->SetGuidance("Path to analysis file.");
	fFileOutCmd->SetDefaultValue(DEFAULT_FILE_OUT);
}

RutherfordRunMessenger::~RutherfordRunMessenger()
{
	delete fDirectory;
	delete fFileOutCmd;
}

void RutherfordRunMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if      (cmd == fFileOutCmd)
	{
		fRunAction->SetFileOut(value);
	}
}
