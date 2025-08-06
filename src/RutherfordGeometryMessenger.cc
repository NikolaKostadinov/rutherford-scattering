#include "../include/RutherfordGeometryMessenger.hh"
#include "../include/RutherfordDetectorConstruction.hh"

RutherfordGeometryMessenger::RutherfordGeometryMessenger(RutherfordDetectorConstruction* detectorConstruction) : fDetectorConstruction(detectorConstruction)
{
	fDirectory = new G4UIdirectory("/geo/");
	fDirectory->SetGuidance("Command for detector geometry.");

	fWorldRadiusCmd = new G4UIcmdWithADoubleAndUnit("/geo/world/radius", this);
	fWorldRadiusCmd->SetGuidance("Set radius of the world.");
	fWorldRadiusCmd->SetUnitCategory("Length");
	fWorldRadiusCmd->SetDefaultValue(DEFAULT_WORLD_RADIUS / cm);
	fWorldRadiusCmd->SetDefaultUnit("cm");

	fFoilRadiusCmd = new G4UIcmdWithADoubleAndUnit("/geo/foil/radius", this);
	fFoilRadiusCmd->SetGuidance("Set radius of the foil.");
	fFoilRadiusCmd->SetUnitCategory("Length");
	fFoilRadiusCmd->SetDefaultValue(DEFAULT_FOIL_RADIUS / mm);
	fFoilRadiusCmd->SetDefaultUnit("mm");
	
	fFoilThicknessCmd = new G4UIcmdWithADoubleAndUnit("/geo/foil/thickness", this);
	fFoilThicknessCmd->SetGuidance("Set thickness of the foil.");
	fFoilThicknessCmd->SetUnitCategory("Length");
	fFoilThicknessCmd->SetDefaultValue(DEFAULT_FOIL_THICKNESS / um);
	fFoilThicknessCmd->SetDefaultUnit("um");
}

RutherfordGeometryMessenger::~RutherfordGeometryMessenger()
{
	delete fWorldRadiusCmd;
	delete fFoilRadiusCmd;
	delete fFoilThicknessCmd;
}

void RutherfordGeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fWorldRadiusCmd)
	{
		auto radius = fWorldRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetWorldRadius(radius);
	}
	else if (cmd == fFoilRadiusCmd)
	{
		auto radius = fFoilRadiusCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetFoilRadius(radius);
	}
	else if (cmd == fFoilThicknessCmd)
	{
		auto thickness = fFoilThicknessCmd->GetNewDoubleValue(value);
		fDetectorConstruction->SetFoilThickness(thickness);
	}
}
