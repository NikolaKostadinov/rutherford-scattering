#include "../include/RutherfordRunAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordDefaults.h"

RutherfordRunAction::RutherfordRunAction()
{	
	fTimer = new G4Timer;
	fElapsedTime = 0.0;
	fNumberOfEvents = 0;

	fFileOut = DEFAULT_FILE_OUT;

	fMessenger = new RutherfordRunMessenger(this);
}

RutherfordRunAction::~RutherfordRunAction()
{
	delete fTimer;
	delete fMessenger;
}

G4double RutherfordRunAction::SaveLapTime()
{
	fTimer->Stop();
	G4double time = fTimer->GetRealElapsed() * s;
	fElapsedTime += time;
	fTimer->Start();
	return time;
}

void RutherfordRunAction::UpdateNumberOfEvents()
{
	auto* runManager = G4RunManager::GetRunManager();
	fNumberOfEvents  = runManager->GetNumberOfEventsToBeProcessed();
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	UpdateNumberOfEvents();

	auto* analysisManager = G4AnalysisManager::Instance();
	if (G4Threading::IsMultithreadedApplication())
		analysisManager->SetNtupleMerging(true);
	analysisManager->OpenFile(fFileOut);
	analysisManager->CreateNtuple("Hits", "Detector hits");
	analysisManager->CreateNtupleIColumn("EventID");
	analysisManager->CreateNtupleIColumn("TrackID");
	analysisManager->CreateNtupleIColumn("ParentTrackID");
	analysisManager->CreateNtupleIColumn("PDGCode");
	analysisManager->CreateNtupleIColumn("ProcessType");
	analysisManager->CreateNtupleIColumn("ProcessSubType");
	analysisManager->CreateNtupleDColumn("Edep_keV");
	analysisManager->CreateNtupleDColumn("X_mm");
	analysisManager->CreateNtupleDColumn("Y_mm");
	analysisManager->CreateNtupleDColumn("Z_mm");
	analysisManager->CreateNtupleDColumn("T_ns");
	analysisManager->FinishNtuple();

	fTimer->Start();
	fElapsedTime = 0.0;
}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	fTimer->Stop();

	auto* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
}
