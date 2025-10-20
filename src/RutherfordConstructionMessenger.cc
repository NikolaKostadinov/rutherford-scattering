#include "../include/RutherfordConstructionMessenger.hh"
#include "../include/RutherfordDetectorConstruction.hh"

#include "../include/RutherfordDefaults.h"

RutherfordConstructionMessenger::RutherfordConstructionMessenger(RutherfordDetectorConstruction* detectorConstruction) : fDetectorConstruction(detectorConstruction)
{
	fDirectory->SetGuidance("Command for detector geometry.");

	fWorldRadiusCmd->SetGuidance("Set radius of the world.");
	fWorldRadiusCmd->SetUnitCategory("Length");
	fWorldRadiusCmd->SetDefaultValue(DEFAULT_WORLD_RADIUS / DEFAULT_LONG_LENGTH_UNIT);
	fWorldRadiusCmd->SetDefaultUnit(DEFAULT_LONG_LENGTH_UNIT_STRING);
	
	fDetectorAtomicNumberCmd->SetGuidance("Set atomic number of the detector material.");
	fDetectorAtomicNumberCmd->SetDefaultValue(DEFAULT_DETECTOR_ATOMIC_NUMBER);

	fDetectorNumberDensityCmd->SetGuidance("Set atomic number density of the detector material.");
	fDetectorNumberDensityCmd->SetUnitCategory("NumberDensity");
	fDetectorNumberDensityCmd->SetDefaultValue(DEFAULT_DETECTOR_NUMBER_DENSITY / DEFAULT_NUMBER_DENSITY_UNIT);
	fDetectorNumberDensityCmd->SetDefaultUnit(DEFAULT_NUMBER_DENSITY_UNIT_STRING);

	fDetectorTemperatureCmd->SetGuidance("Set temperature of the detector.");
	fDetectorTemperatureCmd->SetUnitCategory("Temperature");
	fDetectorTemperatureCmd->SetDefaultValue(DEFAULT_DETECTOR_TEMPERATURE / DEFAULT_TEMPERATURE_UNIT);
	fDetectorTemperatureCmd->SetDefaultUnit(DEFAULT_TEMPERATURE_UNIT_STRING);

	fDetectorRadiusCmd->SetGuidance("Set radius of the detector.");
	fDetectorRadiusCmd->SetUnitCategory("Length");
	fDetectorRadiusCmd->SetDefaultValue(DEFAULT_DETECTOR_RADIUS / DEFAULT_MID_LENGTH_UNIT);
	fDetectorRadiusCmd->SetDefaultUnit(DEFAULT_MID_LENGTH_UNIT_STRING);
	
	fDetectorThicknessCmd->SetGuidance("Set thickness of the detector.");
	fDetectorThicknessCmd->SetUnitCategory("Length");
	fDetectorThicknessCmd->SetDefaultValue(DEFAULT_DETECTOR_THICKNESS / DEFAULT_SHORT_LENGTH_UNIT);
	fDetectorThicknessCmd->SetDefaultUnit(DEFAULT_SHORT_LENGTH_UNIT_STRING);

	fDetectorDeadLayerCmd->SetGuidance("Set dead layer thickness of the detector.");
	fDetectorDeadLayerCmd->SetUnitCategory("Length");
	fDetectorDeadLayerCmd->SetDefaultValue(DEFAULT_DETECTOR_DEAD_LAYER / DEFAULT_SHORT_LENGTH_UNIT);
	fDetectorDeadLayerCmd->SetDefaultUnit(DEFAULT_SHORT_LENGTH_UNIT_STRING);
}

RutherfordConstructionMessenger::~RutherfordConstructionMessenger()
{
	delete fDirectory;
	delete fWorldRadiusCmd;
	delete fDetectorAtomicNumberCmd;
	delete fDetectorNumberDensityCmd;
	delete fDetectorTemperatureCmd;
	delete fDetectorRadiusCmd;
	delete fDetectorThicknessCmd;
	delete fDetectorDeadLayerCmd;
}

void RutherfordConstructionMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if      (cmd == fWorldRadiusCmd)
	{
		auto evalue = fWorldRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetWorldRadius(evalue);
	}
	else if (cmd == fDetectorAtomicNumberCmd)
	{
		auto evalue = fDetectorAtomicNumberCmd->GetNewIntValue(value);
		fDetectorConstruction->SetDetectorAtomicNumber(evalue);
	}
	else if (cmd == fDetectorNumberDensityCmd)
	{
		auto evalue = fDetectorNumberDensityCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorNumberDensity(evalue);
	}
	else if (cmd == fDetectorTemperatureCmd)
	{
		auto evalue = fDetectorTemperatureCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorTemperature(evalue);
	}
	else if (cmd == fDetectorRadiusCmd)
	{
		auto evalue = fDetectorRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorRadius(evalue);
	}
	else if (cmd == fDetectorThicknessCmd)
	{
		auto evalue = fDetectorThicknessCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorThickness(evalue);
	}
	else if (cmd == fDetectorDeadLayerCmd)
	{
		auto evalue = fDetectorDeadLayerCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetDetectorDeadLayer(evalue);
	}
}
