#include "../include/RutherfordGeometryMessenger.hh"
#include "../include/RutherfordDetectorConstruction.hh"

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordCommands.h"

RutherfordGeometryMessenger::RutherfordGeometryMessenger(RutherfordDetectorConstruction* detectorConstruction) : fDetectorConstruction(detectorConstruction)
{
	fDirectory = new G4UIdirectory(GEOMETRY_CMD);
	fDirectory->SetGuidance("Command for detector geometry.");

	fWorldRadiusCmd = new G4UIcmdWithADoubleAndUnit(WORLD_RADIUS_CMD, this);
	fWorldRadiusCmd->SetGuidance("Set radius of the world.");
	fWorldRadiusCmd->SetUnitCategory("Length");
	fWorldRadiusCmd->SetDefaultValue(DEFAULT_WORLD_RADIUS / cm);
	fWorldRadiusCmd->SetDefaultUnit("cm");
	
	fDetectorAtomicNumberCmd = new G4UIcmdWithAnInteger(DETECTOR_ATOMIC_NUMBER_CMD, this);
        fDetectorAtomicNumberCmd->SetGuidance("Set atomic number of the detector material.");
        fDetectorAtomicNumberCmd->SetDefaultValue(DEFAULT_DETECTOR_ATOMIC_NUMBER);

	fDetectorNumberDensityCmd = new G4UIcmdWithADoubleAndUnit(DETECTOR_NUMBER_DENSITY_CMD, this);
        fDetectorNumberDensityCmd->SetGuidance("Set atomic number density of the detector material.");
        fDetectorNumberDensityCmd->SetUnitCategory("NumberDensity");
        fDetectorNumberDensityCmd->SetDefaultValue(DEFAULT_DETECTOR_NUMBER_DENSITY / DEFAULT_NUMBER_DENSITY_UNIT);
        fDetectorNumberDensityCmd->SetDefaultUnit(DEFAULT_NUMBER_DENSITY_UNIT_STRING);

	fDetectorRadiusCmd = new G4UIcmdWithADoubleAndUnit(DETECTOR_RADIUS_CMD, this);
	fDetectorRadiusCmd->SetGuidance("Set radius of the detector.");
	fDetectorRadiusCmd->SetUnitCategory("Length");
	fDetectorRadiusCmd->SetDefaultValue(DEFAULT_DETECTOR_RADIUS / DEFAULT_MID_LENGTH_UNIT);
	fDetectorRadiusCmd->SetDefaultUnit(DEFAULT_MID_LENGTH_UNIT_STRING);
	
	fDetectorThicknessCmd = new G4UIcmdWithADoubleAndUnit(DETECTOR_THICKNESS_CMD, this);
	fDetectorThicknessCmd->SetGuidance("Set thickness of the detector.");
	fDetectorThicknessCmd->SetUnitCategory("Length");
	fDetectorThicknessCmd->SetDefaultValue(DEFAULT_DETECTOR_THICKNESS / DEFAULT_SHORT_LENGTH_UNIT);
	fDetectorThicknessCmd->SetDefaultUnit(DEFAULT_SHORT_LENGTH_UNIT_STRING);
}

RutherfordGeometryMessenger::~RutherfordGeometryMessenger()
{
	delete fDirectory;
	delete fWorldRadiusCmd;
	delete fDetectorAtomicNumberCmd;
	delete fDetectorNumberDensityCmd;
	delete fDetectorRadiusCmd;
	delete fDetectorThicknessCmd;
}

void RutherfordGeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fWorldRadiusCmd)
	{
		auto radius = fWorldRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetWorldRadius(radius);
	}
	else if (cmd == fDetectorAtomicNumberCmd)
	{
		auto Z = fDetectorAtomicNumberCmd->GetNewIntValue(value);
		fDetectorConstruction->SetDetectorAtomicNumber(Z);
	}
	else if (cmd == fDetectorNumberDensityCmd)
	{
		auto n = fDetectorNumberDensityCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorNumberDensity(n);
	}
	else if (cmd == fDetectorRadiusCmd)
	{
		auto radius = fDetectorRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorRadius(radius);
	}
	else if (cmd == fDetectorThicknessCmd)
	{
		auto thickness = fDetectorThicknessCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorThickness(thickness);
	}
}
