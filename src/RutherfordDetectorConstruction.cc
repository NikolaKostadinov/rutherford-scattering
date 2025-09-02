#include "../include/RutherfordDetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4PVPlacement.hh>
#include <G4Region.hh>
#include <G4ProductionCuts.hh>
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
	G4Element*  vacuumElement   = nist->FindOrBuildElement(VACUUM_ATOMIC_NUMBER);
	G4double    vacuumAtomMass  = vacuumElement->GetA() / CLHEP::Avogadro;
	G4double    vacuumDensity   = vacuumAtomMass * VACUUM_NUMBER_DENSITY;
	G4Material* vacuumMaterial = new G4Material(VACUUM, vacuumDensity, 1);
	vacuumMaterial->AddElement(vacuumElement, 1);

	// Detector Material
	G4Element*  detectorElement  = nist->FindOrBuildElement(fDetectorAtomicNumber);
	G4double    detectorAtomMass = detectorElement->GetA() / CLHEP::Avogadro;
	G4double    detectorDensity  = detectorAtomMass * fDetectorNumberDensity;
	G4Material* detectorMaterial = new G4Material(DETECTOR_MATERIAL, detectorDensity, 1);
	detectorMaterial->AddElement(detectorElement, 1);
	
	// World Background
	auto worldSolid = new G4Box(WORLD_NAME, fWorldRadius, fWorldRadius, fWorldRadius);
    	auto worldLogic	= new G4LogicalVolume(worldSolid, vacuumMaterial, WORLD_NAME);
    	auto world 	= new G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			worldLogic,		// placed logical volume
			WORLD_NAME,		// name of volume
			nullptr,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	// Detector
	auto detectorSolid = new G4Tubs(DETECTOR_NAME, 0.0, fDetectorRadius, fDetectorThickness/2, 0.0, 360.0 * deg);
    	auto detectorLogic = new G4LogicalVolume(detectorSolid, detectorMaterial, DETECTOR_NAME);
	new  G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			detectorLogic,		// placed logical volume
			DETECTOR_NAME,		// name of volume
			worldLogic,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	auto detectorRegion = new G4Region("DetectorRegion");
	detectorRegion->AddRootLogicalVolume(detectorLogic);

	auto cuts = new G4ProductionCuts();
	cuts->SetProductionCut(1.0 * nm, "e-");
	cuts->SetProductionCut(1.0 * nm, "e+");
	cuts->SetProductionCut(1.0 * nm, "gamma");

	detectorRegion->SetProductionCuts(cuts);

	return world;
}
