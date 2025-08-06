#include "../include/RutherfordGeneratorMessenger.hh"
#include "../include/RutherfordGeneratorAction.hh"
#include <G4SystemOfUnits.hh>

RutherfordGeneratorMessenger::RutherfordGeneratorMessenger(RutherfordGeneratorAction* generator) : fGenerator(generator)
{
	fDirectory = new G4UIdirectory("/gen/");
	fDirectory->SetGuidance("Command for particle generation.");

	fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/gen/energy", this);
	fEnergyCmd->SetGuidance("Set inital alpha particle energy.");
	fEnergyCmd->SetUnitCategory("Energy");
	fEnergyCmd->SetDefaultValue(DEFAULT_ENERGY / MeV);
	fEnergyCmd->SetDefaultUnit("MeV");

	fDistanceCmd = new G4UIcmdWithADoubleAndUnit("/gen/distance", this);
        fDistanceCmd->SetGuidance("Set inital alpha particle distance from target.");
        fDistanceCmd->SetUnitCategory("Length");
        fDistanceCmd->SetDefaultValue(DEFAULT_DISTANCE / cm);
        fDistanceCmd->SetDefaultUnit("cm");
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
