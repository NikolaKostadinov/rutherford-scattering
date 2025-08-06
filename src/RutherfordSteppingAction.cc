#include "../include/RutherfordSteppingAction.hh"

RutherfordSteppingAction::RutherfordSteppingAction() : G4UserSteppingAction()
{

}

RutherfordSteppingAction::~RutherfordSteppingAction()
{

}


void RutherfordSteppingAction::UserSteppingAction(const G4Step* step)
{
	G4Track* track = step->GetTrack();
	
	G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() + 1;

	if (track->GetDefinition()->GetParticleName() == "alpha")
		if (track->GetTrackStatus() == fStopAndKill)
		{
			auto direction = step->GetPostStepPoint()->GetMomentumDirection();
			auto theta = direction.theta();
		
			auto energy = track->GetKineticEnergy();
			
			auto analysisManager = G4AnalysisManager::Instance();

			analysisManager->FillH1(0, energy / MeV);
			analysisManager->FillH1(1, theta / deg);

			G4cout << "event [" << eventID << "] final energy: " << energy / MeV << " MeV" << G4endl;

		}
}
