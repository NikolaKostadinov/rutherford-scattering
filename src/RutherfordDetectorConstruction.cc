#include "../include/RutherfordDetectorConstruction.hh"

#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordSensitiveDetector.hh"

RutherfordDetectorConstruction::RutherfordDetectorConstruction()
{	
	fMessenger = new RutherfordConstructionMessenger(this);
}

RutherfordDetectorConstruction::~RutherfordDetectorConstruction()
{
	delete fWorldMaterial;
	delete fDetectorMaterial;
	delete fMessenger;
}

void RutherfordDetectorConstruction::SetWorldMaterial()
{
	auto* nist = G4NistManager::Instance();

	G4Element*  vacuumElement   = nist->FindOrBuildElement(VACUUM_ATOMIC_NUMBER);
	G4double    vacuumAtomMass  = vacuumElement->GetA() / CLHEP::Avogadro;
	G4double    vacuumDensity   = vacuumAtomMass * VACUUM_NUMBER_DENSITY;
	
	fWorldMaterial = new G4Material(VACUUM, vacuumDensity, 1);
	fWorldMaterial->AddElement(vacuumElement, 1);
}

void RutherfordDetectorConstruction::SetDetectorMaterial()
{
	auto* nist = G4NistManager::Instance();

	G4Element*  detectorElement  = nist->FindOrBuildElement(fDetectorAtomicNumber);
	G4double    detectorAtomMass = detectorElement->GetA() / CLHEP::Avogadro;
	G4double    detectorDensity  = detectorAtomMass * fDetectorNumberDensity;

	fDetectorMaterial = new G4Material(
		DETECTOR_MATERIAL,
		fDetectorAtomicNumber,
		detectorAtomMass,
		detectorDensity,
		kStateSolid,
		fDetectorTemperature
	);
}

G4double RutherfordDetectorConstruction::GetDetectorElectronDensity() const
{
	return fDetectorMaterial->GetElectronDensity();
}

G4double RutherfordDetectorConstruction::GetDetectorMeanExcitationEnergy() const
{
	return fDetectorMaterial->GetIonisation()->GetMeanExcitationEnergy();
}

G4VPhysicalVolume* RutherfordDetectorConstruction::Construct()
{
	SetWorldMaterial();
	SetDetectorMaterial();
	
	auto* worldSolid = new G4Box(WORLD_NAME, fWorldRadius, fWorldRadius, fWorldRadius);
    	auto* worldLogic = new G4LogicalVolume(worldSolid, fWorldMaterial, WORLD_NAME);
    	auto* world      = new G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			worldLogic,		// placed logical volume
			WORLD_NAME,		// name of volume
			nullptr,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);

	auto* detectorSolid = new G4Tubs(DETECTOR_NAME, 0.0, fDetectorRadius, fDetectorThickness/2, 0.0, 360.0 * deg);
    	auto* detectorLogic = new G4LogicalVolume(detectorSolid, fDetectorMaterial, DETECTOR_NAME);
	new  G4PVPlacement(
			nullptr,		// rotation ?
			G4ThreeVector(),	// placement position
			detectorLogic,		// placed logical volume
			DETECTOR_NAME,		// name of volume
			worldLogic,		// parent volume
			false,			// boolean opertion ?
			0			// number of copies
	);
	
	return world;
}

void RutherfordDetectorConstruction::ConstructSDandField()
{
	auto* sensitiveDetectorManager = G4SDManager::GetSDMpointer();
	auto* sensitiveDetector = new RutherfordSensitiveDetector(DETECTOR_NAME, HITS_COLLECTION_NAME);
	
	sensitiveDetectorManager->AddNewDetector(sensitiveDetector);
	
	auto* logicalVolumeStore = G4LogicalVolumeStore::GetInstance();
	auto* detectorLogic = logicalVolumeStore->GetVolume(DETECTOR_NAME);
	if (detectorLogic)
		detectorLogic->SetSensitiveDetector(sensitiveDetector);
}