#include "../include/RutherfordGeneratorMessenger.hh"
#include "../include/RutherfordGeneratorAction.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

RutherfordGeneratorMessenger::RutherfordGeneratorMessenger(RutherfordGeneratorAction* generator) : fGenerator(generator)
{
	fDirectory = new G4UIdirectory(GENERATE_CMD);
	fDirectory->SetGuidance("Command for particle generation.");

	fEnergyCmd = new G4UIcmdWithADoubleAndUnit(GENERATE_ENERGY_CMD, this);
	fEnergyCmd->SetGuidance("Set inital alpha particle energy.");
	fEnergyCmd->SetUnitCategory("Energy");
	fEnergyCmd->SetDefaultValue(DEFAULT_ENERGY / DEFAULT_ENERGY_UNIT);
	fEnergyCmd->SetDefaultUnit(DEFAULT_ENERGY_UNIT_STRING);

	fDistanceCmd = new G4UIcmdWithADoubleAndUnit(GENERATE_DISTANCE_CMD, this);
        fDistanceCmd->SetGuidance("Set inital alpha particle distance from target.");
        fDistanceCmd->SetUnitCategory("Length");
        fDistanceCmd->SetDefaultValue(DEFAULT_DISTANCE / DEFAULT_LONG_LENGTH_UNIT);
        fDistanceCmd->SetDefaultUnit(DEFAULT_LONG_LENGTH_UNIT_STRING);
}

RutherfordGeneratorMessenger::~RutherfordGeneratorMessenger()
{
	delete fDirectory;
	delete fEnergyCmd;
	delete fDistanceCmd;
}

void RutherfordGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fEnergyCmd)
	{
		auto energy = fEnergyCmd->GetNewDoubleValue(value);
		fGenerator->SetEnergy(energy);
	}
	else if (cmd == fDistanceCmd)
	{
		auto distance = fDistanceCmd->GetNewDoubleValue(value);
		fGenerator->SetDistance(distance);
	}
}
