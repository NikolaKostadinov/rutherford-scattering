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
	
	const G4StepPoint* postStepPoint = step->GetPostStepPoint();
	const G4VPhysicalVolume* postVolume = postStepPoint->GetPhysicalVolume();

	if (track->GetDefinition()->GetParticleName() == PARTICLE_NAME)
		if (postVolume && postVolume->GetName() == WORLD_NAME)
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
