#include "../include/RutherfordSteppingAction.hh"

#include <G4Track.hh>
#include <G4EventManager.hh>
#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4RunManager.hh>
#include <G4EventManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordDefaults.h"

RutherfordSteppingAction::RutherfordSteppingAction() : G4UserSteppingAction()
{

}

RutherfordSteppingAction::~RutherfordSteppingAction()
{

}

void RutherfordSteppingAction::UserSteppingAction(const G4Step* step)
{
	auto track = step->GetTrack();
	
	const G4StepPoint*       postStepPoint = step->GetPostStepPoint();
	const G4VPhysicalVolume* postVolume    = postStepPoint->GetPhysicalVolume();

	if (track->GetDefinition()->GetParticleName() == PARTICLE_NAME)
		if (postVolume && postVolume->GetName() == WORLD_NAME)
		{
			auto runManager = G4RunManager::GetRunManager();
			auto runAction  = static_cast<const RutherfordRunAction*>(runManager->GetUserRunAction());
	
			auto eventManager = G4EventManager::GetEventManager();
			auto event        = eventManager->GetConstCurrentEvent();
	
			auto analysisManager = G4AnalysisManager::Instance();
			
			G4int energyHistogramID = runAction->GetEnergyHistogramID(); 
			G4int thetaHistogramID  = runAction->GetThetaHistogramID(); 
			G4int eventID           = event->GetEventID();
			
			auto energyOut = track->GetKineticEnergy();
			auto direction = step->GetPostStepPoint()->GetMomentumDirection();
			auto theta     = direction.theta();
			
			analysisManager->FillH1(energyHistogramID, energyOut / DEFAULT_ENERGY_UNIT);
			analysisManager->FillH1(thetaHistogramID,  theta / DEFAULT_ANGLE_UNIT);

			G4cout << "event [" << (eventID + 1) << "] final energy: " << energyOut / MeV << G4endl;
		}
}
