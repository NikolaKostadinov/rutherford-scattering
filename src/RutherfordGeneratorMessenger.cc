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
	fPrimaryEnergyCmd->SetDefaultValue(DEFAULT_PRIMARY_ENERGY / HIGH_ENERGY_UNIT_VAL);
	fPrimaryEnergyCmd->SetDefaultUnit(HIGH_ENERGY_UNIT_STR);

        fPrimaryDistanceCmd->SetGuidance("Set primary particle initial distance from target center.");
        fPrimaryDistanceCmd->SetUnitCategory("Length");
        fPrimaryDistanceCmd->SetDefaultValue(DEFAULT_PRIMARY_DISTANCE / LONG_LENGTH_UNIT_VAL);
        fPrimaryDistanceCmd->SetDefaultUnit(LONG_LENGTH_UNIT_STR);

	fPrimaryGeneratorTypeCmd->SetGuidance("Set primary generator type.");
	fPrimaryGeneratorTypeCmd->SetDefaultValue("");
}

RutherfordGeneratorMessenger::~RutherfordGeneratorMessenger()
{
	delete fDirectory;
	delete fPrimaryParticleDefinitionCmd;
	delete fPrimaryEnergyCmd;
	delete fPrimaryDistanceCmd;
	delete fPrimaryGeneratorTypeCmd;
}

void RutherfordGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if      (cmd == fPrimaryParticleDefinitionCmd)
	{
		fGenerator->SetPrimaryParticleDefinition(value);
	}
	else if (cmd == fPrimaryIonAtomicNumberCmd)
	{
		auto evalue = fPrimaryIonAtomicNumberCmd->GetNewIntValue(value);
		fGenerator->SetPrimaryIonAtomicNumber(evalue);
	}
	else if (cmd == fPrimaryIonMassNumberCmd)
	{
		auto evalue = fPrimaryIonMassNumberCmd->GetNewIntValue(value);
		fGenerator->SetPrimaryIonMassNumber(evalue);
	}
	else if (cmd == fPrimaryEnergyCmd)
	{
		auto evalue = fPrimaryEnergyCmd->GetNewDoubleValue(value);
		fGenerator->SetPrimaryEnergy(evalue);
	}
	else if (cmd == fPrimaryDistanceCmd)
	{
		auto evalue = fPrimaryDistanceCmd->GetNewDoubleValue(value);
		fGenerator->SetPrimaryDistance(evalue);
	}
	else if (cmd == fPrimaryGeneratorTypeCmd)
	{
		fGenerator->SetPrimaryGeneratorType(value);
	}
}
