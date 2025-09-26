#include "../include/RutherfordGeneratorMessenger.hh"
#include "../include/RutherfordGeneratorAction.hh"

#include "../include/RutherfordDefaults.h"

RutherfordGeneratorMessenger::RutherfordGeneratorMessenger(RutherfordGeneratorAction* generator) : fGenerator(generator)
{
	fDirectory->SetGuidance("Command for particle generation.");

	fPrimaryParticleDefinitionCmd->SetGuidance("Set primary particle type.");
	fPrimaryParticleDefinitionCmd->SetDefaultValue(DEFAULT_PRIMARY_PARTICLE);

	fPrimaryEnergyCmd->SetGuidance("Set primary particle inital energy.");
	fPrimaryEnergyCmd->SetUnitCategory("Energy");
	fPrimaryEnergyCmd->SetDefaultValue(DEFAULT_PRIMARY_ENERGY / DEFAULT_HIGH_ENERGY_UNIT);
	fPrimaryEnergyCmd->SetDefaultUnit(DEFAULT_HIGH_ENERGY_UNIT_STRING);

        fPrimaryDistanceCmd->SetGuidance("Set primary particle initial distance from target center.");
        fPrimaryDistanceCmd->SetUnitCategory("Length");
        fPrimaryDistanceCmd->SetDefaultValue(DEFAULT_PRIMARY_DISTANCE / DEFAULT_LONG_LENGTH_UNIT);
        fPrimaryDistanceCmd->SetDefaultUnit(DEFAULT_LONG_LENGTH_UNIT_STRING);
}

RutherfordGeneratorMessenger::~RutherfordGeneratorMessenger()
{
	delete fDirectory;
	delete fPrimaryParticleDefinitionCmd;
	delete fPrimaryEnergyCmd;
	delete fPrimaryDistanceCmd;
}

void RutherfordGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if      (cmd == fPrimaryParticleDefinitionCmd)
	{
		fGenerator->SetPrimaryParticleDefinition(value);
	}
	else if (cmd == fPrimaryEnergyCmd)
	{
		auto evalue = fPrimaryEnergyCmd->GetNewDoubleValue(value);
		fGenerator->SetPrimaryEnergy(evalue);
	}
	else if (cmd == fPrimaryDistanceCmd)
	{
		auto evalue = fPrimaryDistanceCmd->GetNewDoubleValue(value);
		fGenerator->SetPrimaryEnergy(evalue);
	}
}
