#include "../include/RutherfordGeneratorMessenger.hh"
#include "../include/RutherfordGeneratorAction.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

RutherfordGeneratorMessenger::RutherfordGeneratorMessenger(RutherfordGeneratorAction* generator) : fGenerator(generator)
{
	fDirectory = new G4UIdirectory(GENERATE_CMD);
	fDirectory->SetGuidance("Command for particle generation.");

	fAlphaEnergyCmd = new G4UIcmdWithADoubleAndUnit(GENERATE_ALPHA_ENERGY_CMD, this);
	fAlphaEnergyCmd->SetGuidance("Set inital alpha particle energy.");
	fAlphaEnergyCmd->SetUnitCategory("Energy");
	fAlphaEnergyCmd->SetDefaultValue(DEFAULT_ALPHA_ENERGY / DEFAULT_HIGH_ENERGY_UNIT);
	fAlphaEnergyCmd->SetDefaultUnit(DEFAULT_HIGH_ENERGY_UNIT_STRING);

	fAlphaDistanceCmd = new G4UIcmdWithADoubleAndUnit(GENERATE_ALPHA_DISTANCE_CMD, this);
        fAlphaDistanceCmd->SetGuidance("Set inital alpha particle distance from target center.");
        fAlphaDistanceCmd->SetUnitCategory("Length");
        fAlphaDistanceCmd->SetDefaultValue(DEFAULT_ALPHA_DISTANCE / DEFAULT_LONG_LENGTH_UNIT);
        fAlphaDistanceCmd->SetDefaultUnit(DEFAULT_LONG_LENGTH_UNIT_STRING);
}

RutherfordGeneratorMessenger::~RutherfordGeneratorMessenger()
{
	delete fDirectory;
	delete fAlphaEnergyCmd;
	delete fAlphaDistanceCmd;
}

void RutherfordGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fAlphaEnergyCmd)
	{
		auto energy = fAlphaEnergyCmd->GetNewDoubleValue(value);
		fGenerator->SetAlphaEnergy(energy);
	}
	else if (cmd == fAlphaDistanceCmd)
	{
		auto distance = fAlphaDistanceCmd->GetNewDoubleValue(value);
		fGenerator->SetAlphaDistance(distance);
	}
}
