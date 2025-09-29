#include "../include/RutherfordEventAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

#include <iomanip>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordHit.hh"
#include "../include/RutherfordDefaults.h"

void RutherfordEventAction::BeginOfEventAction(const G4Event* event)
{

}

void RutherfordEventAction::EndOfEventAction(const G4Event* event)
{
	auto eventID = event->GetEventID();

	auto runManager = G4RunManager::GetRunManager();
	auto runAction  = dynamic_cast<RutherfordRunAction*>(
		const_cast<G4UserRunAction*>(
			runManager->GetUserRunAction()
		)
	);
	auto numberOfEvents = runAction->GetNumberOfEvents();
	runAction->SaveLapTime();
	auto elapsedTime = runAction->GetElapsedTime();
	auto progress = (G4double) (eventID + 1) / (G4double) numberOfEvents;
	auto remainingTime = (1.0 - progress)/progress * elapsedTime;
	auto freq = (eventID + 1) / elapsedTime;
	int  ERTmin = int(elapsedTime  /s) / 60;
	int  ERTs   = int(elapsedTime  /s) % 60;	// Elapsed Running Time
	int  ETAmin = int(remainingTime/s) / 60;
	int  ETAs   = int(remainingTime/s) % 60;	// Estimated Time of Arrival

	G4cout << '\r';
	G4cout << "[*";
	int position = progress * BAR_SIZE;
	for (int i = 0; i < BAR_SIZE; ++i)
	{
		if      (i <  position) G4cout << '-';
		else if (i == position) G4cout << '>';
		else                    G4cout << ' ';
	}	
	G4cout << "*]";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << eventID+1 << "/" << numberOfEvents << " events";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "[ " << int(progress * 100.0) << "%]";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ERT " << ERTmin << "min " << ERTs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ETA " << ETAmin << "min " << ETAs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "freq " << float(int(freq / kilohertz * 10)) / 10 << "kHz";
	G4cout.flush();
	if (progress == 1.0) G4cout << G4endl;

	auto hitsCollections = event->GetHCofThisEvent();
	if (!hitsCollections) return;
	
	auto sensitiveDetectorManager = G4SDManager::GetSDMpointer();
	auto hitsCollectionID = sensitiveDetectorManager->GetCollectionID(HITS_COLLECTION_NAME);
	
	auto hitsCollection = static_cast<RutherfordHitsCollection*>(
		hitsCollections->GetHC(hitsCollectionID)
	);
	if (!hitsCollection) return;

	auto analysisManager = G4AnalysisManager::Instance();
	for (size_t i = 0; i < hitsCollection->entries(); ++i)
	{
		auto hit = (*hitsCollection)[i];

		analysisManager->FillNtupleIColumn( 0, eventID);
		analysisManager->FillNtupleIColumn( 1, hit->GetTrackID());
		analysisManager->FillNtupleIColumn( 2, hit->GetParentTrackID());
		analysisManager->FillNtupleIColumn( 3, hit->GetPDGCode());
		analysisManager->FillNtupleIColumn( 4, hit->GetProcessType());
		analysisManager->FillNtupleIColumn( 5, hit->GetProcessSubType());
		analysisManager->FillNtupleDColumn( 6, hit->GetEnergyDeposit() / keV);
		analysisManager->FillNtupleDColumn( 7, hit->GetPosition().x() / mm);
		analysisManager->FillNtupleDColumn( 8, hit->GetPosition().y() / mm);
		analysisManager->FillNtupleDColumn( 9, hit->GetPosition().z() / mm);
		analysisManager->FillNtupleDColumn(10, hit->GetTime() / ns);

		analysisManager->AddNtupleRow();
	}
}
