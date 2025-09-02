#include "../include/RutherfordEventAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>

#include "../include/RutherfordRunAction.hh"

RutherfordEventAction::RutherfordEventAction()
{
	fDeltas = 0;
}

RutherfordEventAction::~RutherfordEventAction()
{

}

void RutherfordEventAction::IncrementDeltas()
{
	++fDeltas;
}

void RutherfordEventAction::BeginOfEventAction(const G4Event* event)
{
	fDeltas = 0;
}

void RutherfordEventAction::EndOfEventAction(const G4Event* event)
{
	auto runManager = G4RunManager::GetRunManager();
	auto runAction  = static_cast<const RutherfordRunAction*>(runManager->GetUserRunAction());
	
	auto analysisManager = G4AnalysisManager::Instance();
	
	G4int deltasHistogramID = runAction->GetDeltasHistogramID();
	
	analysisManager->FillH1(deltasHistogramID, fDeltas);
}
