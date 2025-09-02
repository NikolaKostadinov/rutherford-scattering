#include "../include/RutherfordDetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordDefaults.h"

RutherfordDetectorConstruction::RutherfordDetectorConstruction() : G4VUserDetectorConstruction()
{
	fWorldRadius           = DEFAULT_WORLD_RADIUS;
	fDetectorAtomicNumber  = DEFAULT_DETECTOR_ATOMIC_NUMBER;
	fDetectorNumberDensity = DEFAULT_DETECTOR_NUMBER_DENSITY;
	fDetectorRadius        = DEFAULT_DETECTOR_RADIUS;
	fDetectorThickness     = DEFAULT_DETECTOR_THICKNESS;
	
	fMessenger = new RutherfordGeometryMessenger(this);
}

RutherfordDetectorConstruction::~RutherfordDetectorConstruction()
{
	delete fMessenger;
}

void RutherfordDetectorConstruction::SetWorldRadius(G4double radius)
{
	fWorldRadius = radius;
}

void RutherfordDetectorConstruction::SetDetectorAtomicNumber(G4int Z)
{
	fDetectorAtomicNumber = Z;
}

void RutherfordDetectorConstruction::SetDetectorNumberDensity(G4double n)
{
	fDetectorNumberDensity = n;
}

void RutherfordDetectorConstruction::SetDetectorRadius(G4double radius)
{
	fDetectorRadius = radius;
}

void RutherfordDetectorConstruction::SetDetectorThickness(G4double thickness)
{
	fDetectorThickness = thickness;
}

G4double RutherfordDetectorConstruction::GetDetectorThickness() const
{
	return fDetectorThickness;
}

G4VPhysicalVolume* RutherfordDetectorConstruction::Construct() 
{
	// NIST Manager
	auto nist = G4NistManager::Instance();

	// Vacuum Material
	G4Element*	vacuumElement		= nist->FindOrBuildElement(VACUUM_ATOMIC_NUMBER);
	G4double	vacuumAtomMass		= vacuumElement->GetA() / CLHEP::Avogadro;
	G4double	vacuumDensity		= vacuumAtomMass * VACUUM_NUMBER_DENSITY;
	G4Material*	vacuumMaterial		= new G4Material(VACUUM, vacuumDensity, 1);
	vacuumMaterial->AddElement(vacuumElement, 1);

	// Detector Material
	G4Element*	detectorElement		= nist->FindOrBuildElement(fDetectorAtomicNumber);
	G4double	detectorAtomMass	= detectorElement->GetA() / CLHEP::Avogadro;
	G4double	detectorDensity		= detectorAtomMass * fDetectorNumberDensity;
	G4Material*	detectorMaterial	= new G4Material(DETECTOR_MATERIAL, detectorDensity, 1);
	detectorMaterial->AddElement(detectorElement, 1);
	
	// World Background
	auto solidWorld = new G4Box(WORLD_NAME, fWorldRadius, fWorldRadius, fWorldRadius);
    	auto logicWorld	= new G4LogicalVolume(solidWorld, vacuumMaterial, WORLD_NAME);
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
	auto solidDetector = new G4Tubs(DETECTOR_NAME, 0.0, fDetectorRadius, fDetectorThickness/2, 0.0, 10.0 * deg);
    	auto logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, DETECTOR_NAME);
	new  G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			logicDetector,		// placed logical volume
			DETECTOR_NAME,		// name of volume
			logicWorld,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	return world;
}
