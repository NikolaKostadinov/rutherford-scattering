#include "../include/RutherfordGeometryMessenger.hh"
#include "../include/RutherfordDetectorConstruction.hh"

RutherfordGeometryMessenger::RutherfordGeometryMessenger(RutherfordDetectorConstruction* detectorConstruction) : fDetectorConstruction(detectorConstruction)
{
	fDirectory = new G4UIdirectory("/geometry/");
	fDirectory->SetGuidance("Command for detector geometry.");

	fWorldRadiusCmd = new G4UIcmdWithADoubleAndUnit("/geometry/world/radius", this);
	fWorldRadiusCmd->SetGuidance("Set radius of the world.");
	fWorldRadiusCmd->SetUnitCategory("Length");
	fWorldRadiusCmd->SetDefaultValue(DEFAULT_WORLD_RADIUS / cm);
	fWorldRadiusCmd->SetDefaultUnit("cm");
	
	fDetectorAtomicNumberCmd = new G4UIcmdWithAnInteger("/geometry/detector/atomicNumber", this);
        fDetectorAtomicNumberCmd->SetGuidance("Set atomic number of the detector material.");
        fDetectorAtomicNumberCmd->SetDefaultValue(DEFAULT_DETECTOR_ATOMIC_NUMBER);

	fDetectorNumberDensityCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detector/numberDensity", this);
        fDetectorNumberDensityCmd->SetGuidance("Set atomic number density of the detector material.");
        fDetectorNumberDensityCmd->SetUnitCategory("NumberDensity");
        fDetectorNumberDensityCmd->SetDefaultValue(DEFAULT_DETECTOR_NUMBER_DENSITY / (1/cm3));
        fDetectorNumberDensityCmd->SetDefaultUnit("1/cm3");

	fDetectorRadiusCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detector/radius", this);
	fDetectorRadiusCmd->SetGuidance("Set radius of the detector.");
	fDetectorRadiusCmd->SetUnitCategory("Length");
	fDetectorRadiusCmd->SetDefaultValue(DEFAULT_DETECTOR_RADIUS / mm);
	fDetectorRadiusCmd->SetDefaultUnit("mm");
	
	fDetectorThicknessCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detector/thickness", this);
	fDetectorThicknessCmd->SetGuidance("Set thickness of the detector.");
	fDetectorThicknessCmd->SetUnitCategory("Length");
	fDetectorThicknessCmd->SetDefaultValue(DEFAULT_DETECTOR_THICKNESS / um);
	fDetectorThicknessCmd->SetDefaultUnit("um");
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
