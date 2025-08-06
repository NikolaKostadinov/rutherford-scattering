#include "../include/RutherfordDetectorConstruction.hh"
#include <G4LogicalVolume.hh>
#include "../include/RutherfordDefaults.h"

RutherfordDetectorConstruction::RutherfordDetectorConstruction() : G4VUserDetectorConstruction()
{
	// Initialize with default values
	fWorldRadius = DEFAULT_WORLD_RADIUS;
	fFoilRadius = DEFAULT_FOIL_RADIUS;
	fFoilThickness = DEFAULT_FOIL_THICKNESS;
	
	fMessenger = new RutherfordGeometryMessenger(this);
}

RutherfordDetectorConstruction::~RutherfordDetectorConstruction()
{

}

void RutherfordDetectorConstruction::SetFoilThickness(G4double thickness)
{
	fFoilThickness = thickness;
}

void RutherfordDetectorConstruction::SetFoilRadius(G4double radius)
{
	fFoilRadius = radius;
}

void RutherfordDetectorConstruction::SetWorldRadius(G4double radius)
{
	fWorldRadius = radius;
}

G4VPhysicalVolume* RutherfordDetectorConstruction::Construct() 
{
	// NIST Manager
	auto nist 	= G4NistManager::Instance();
    	auto air 	= nist->FindOrBuildMaterial("G4_AIR");
	auto gold 	= nist->FindOrBuildMaterial("G4_Au");
	
	// Vacuum
	G4Element*  hydrogen = new G4Element("Hydrogen", "H", 1., 1.01*g/mole);
	G4Material* vacuum   = new G4Material("Vacuum", 1e-25*g/cm3, 1);
	vacuum->AddElement(hydrogen, 1);

	// World Background
	auto solidWorld = new G4Box(WORLD_NAME, fWorldRadius, fWorldRadius, fWorldRadius);
    	auto logicWorld	= new G4LogicalVolume(solidWorld, vacuum, WORLD_NAME);
    	auto world 	= new G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			logicWorld,		// placed logical volume
			WORLD_NAME,		// name of volume
			nullptr,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	// Golden Foil
	auto solidFoil 	= new G4Box(FOIL_NAME, fFoilRadius, fFoilRadius, fFoilThickness/2);
    	auto logicFoil 	= new G4LogicalVolume(solidFoil, gold, FOIL_NAME);
	new G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			logicFoil,		// placed logical volume
			FOIL_NAME,		// name of volume
			logicWorld,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	return world;
}
