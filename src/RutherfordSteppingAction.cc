#include "../include/RutherfordSteppingAction.hh"

#include <G4Track.hh>
#include <G4EventManager.hh>
#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4Alpha.hh>
#include <G4Electron.hh>
#include <G4RunManager.hh>
#include <G4EventManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordEventAction.hh"
#include "../include/RutherfordDefaults.h"

RutherfordSteppingAction::RutherfordSteppingAction() : G4UserSteppingAction()
{

}

RutherfordSteppingAction::~RutherfordSteppingAction()
{

}

void RutherfordSteppingAction::UserSteppingAction(const G4Step* step)
{
	auto track         = step->GetTrack();
	auto postStepPoint = step->GetPostStepPoint();
	auto process       = postStepPoint->GetProcessDefinedStep();

	auto runManager = G4RunManager::GetRunManager();
	auto runAction  = static_cast<const RutherfordRunAction*>(runManager->GetUserRunAction());

	auto eventManager = G4EventManager::GetEventManager();
	auto eventAction  = const_cast<RutherfordEventAction*>(static_cast<const RutherfordEventAction*>(runManager->GetUserEventAction()));

	auto analysisManager = G4AnalysisManager::Instance();

	G4int alphaEnergyHistogramID = runAction->GetAlphaEnergyHistogramID(); 
	G4int alphaThetaHistogramID  = runAction->GetAlphaThetaHistogramID(); 
	G4int alphaHistogramID       = runAction->GetAlphaHistogramID(); 
	G4int deltaEnergyHistogramID = runAction->GetDeltaEnergyHistogramID(); 
	G4int deltaThetaHistogramID  = runAction->GetDeltaThetaHistogramID(); 
	G4int deltaHistogramID       = runAction->GetDeltaHistogramID(); 

	if (track->GetDefinition() == G4Alpha::Definition())
		if (track->GetParentID() == 0)
			if (
					track->GetTrackStatus() == fStopAndKill ||
					track->GetTrackStatus() == fStopButAlive
			)
			{
				auto energy    = postStepPoint->GetKineticEnergy();
				auto direction = postStepPoint->GetMomentumDirection();
				auto theta     = direction.theta();

				eventAction->SetAlphaEnergyOut(energy);
				
				analysisManager->FillH1(alphaEnergyHistogramID, energy / DEFAULT_HIGH_ENERGY_UNIT);
				analysisManager->FillH1(alphaThetaHistogramID,  theta / DEFAULT_ANGLE_UNIT);
				
				analysisManager->FillH2(alphaHistogramID, theta / DEFAULT_ANGLE_UNIT, energy / DEFAULT_HIGH_ENERGY_UNIT);
			}

	auto secondaries = step->GetSecondaryInCurrentStep();
	for (auto secondary : *secondaries)
		if (secondary->GetDefinition() == G4Electron::Definition())
		{
			auto energy     = secondary->GetKineticEnergy();
			auto direction  = secondary->GetMomentumDirection();
			auto theta      = direction.theta();	
			
			eventAction->IncrementDeltas();
			eventAction->AddDeltaEnergy(energy);
			
			analysisManager->FillH1(deltaEnergyHistogramID, energy / DEFAULT_LOW_ENERGY_UNIT);
			analysisManager->FillH1(deltaThetaHistogramID,  theta / DEFAULT_ANGLE_UNIT);
			
			analysisManager->FillH2(deltaHistogramID, theta / DEFAULT_ANGLE_UNIT, energy / DEFAULT_LOW_ENERGY_UNIT);
		}
}
