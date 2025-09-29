#include "../include/RutherfordSensitiveDetector.hh"

#include <G4SDManager.hh>

RutherfordSensitiveDetector::RutherfordSensitiveDetector(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name)
{
	fHitsCollectionID = -1;
	fHitsCollection   = nullptr;

	collectionName.insert(hitsCollectionName);
}

void RutherfordSensitiveDetector::Initialize(G4HCofThisEvent* hitsCollection)
{
	fHitsCollection = new RutherfordHitsCollection(SensitiveDetectorName, collectionName[0]);

	if (fHitsCollectionID < 0)
	{
		auto sensitiveDetectorManager = G4SDManager::GetSDMpointer();
		fHitsCollectionID = sensitiveDetectorManager->GetCollectionID(fHitsCollection);
	}

	hitsCollection->AddHitsCollection(fHitsCollectionID, fHitsCollection);
}

G4bool RutherfordSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	auto hit = new RutherfordHit(step);

	if (hit->GetEnergyDeposit() == 0.0)
	{
		delete hit;
		return false;
	}

	fHitsCollection->insert(hit);

	return true;
}