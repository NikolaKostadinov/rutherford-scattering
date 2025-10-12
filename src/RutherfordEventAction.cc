#include "../include/RutherfordEventAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordHit.hh"
#include "../include/RutherfordPrint.hh"

void RutherfordEventAction::BeginOfEventAction(const G4Event* event)
{

}

void RutherfordEventAction::EndOfEventAction(const G4Event* event)
{
	auto eventID = event->GetEventID();

	auto* runManager = G4RunManager::GetRunManager();
	auto* runAction  = dynamic_cast<RutherfordRunAction*>(
		const_cast<G4UserRunAction*>(
			runManager->GetUserRunAction()
		)
	);
	auto numberOfEvents = runAction->GetNumberOfEvents();
	runAction->SaveLapTime();
	auto elapsedTime = runAction->GetElapsedTime();

	auto eventProgressInterval = numberOfEvents / BAR_SIZE / EVENTS_PER_BAR_GLYPH;
	if (eventProgressInterval == 0)
		eventProgressInterval = 1;

	if ((eventID+1) % eventProgressInterval == 0 || (eventID+1) == numberOfEvents)
		RutherfordPrintRunProgressBar(eventID+1, numberOfEvents, elapsedTime);

	auto* hitsCollections = event->GetHCofThisEvent();
	if (!hitsCollections) return;
	
	auto* sensitiveDetectorManager = G4SDManager::GetSDMpointer();
	auto  hitsCollectionID = sensitiveDetectorManager->GetCollectionID(HITS_COLLECTION_NAME);
	
	auto* hitsCollection = static_cast<RutherfordHitsCollection*>(
		hitsCollections->GetHC(hitsCollectionID)
	);
	if (!hitsCollection) return;

	auto* analysisManager = G4AnalysisManager::Instance();
	for (size_t i = 0; i < hitsCollection->entries(); ++i)
	{
		auto* hit = (*hitsCollection)[i];

		analysisManager->FillNtupleIColumn( 0, eventID);
		analysisManager->FillNtupleIColumn( 1, hit->GetTrackID());
		analysisManager->FillNtupleIColumn( 2, hit->GetParentTrackID());
		analysisManager->FillNtupleIColumn( 3, hit->GetPDGCode());
		analysisManager->FillNtupleIColumn( 4, hit->GetProcessType());
		analysisManager->FillNtupleIColumn( 5, hit->GetProcessSubType());
		analysisManager->FillNtupleDColumn( 6, hit->GetEnergyDeposit() / keV);
		analysisManager->FillNtupleDColumn( 7, hit->GetTime() / ns);
		analysisManager->FillNtupleDColumn( 8, hit->GetPosition().x() / mm);
		analysisManager->FillNtupleDColumn( 9, hit->GetPosition().y() / mm);
		analysisManager->FillNtupleDColumn(10, hit->GetPosition().z() / mm);

		analysisManager->AddNtupleRow();
	}
}
