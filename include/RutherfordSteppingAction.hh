#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include <G4UserSteppingAction.hh>
#include <G4AnalysisManager.hh>
#include <G4Step.hh>
#include <G4Track.hh>
#include <G4EventManager.hh>
#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>

#include "RutherfordDefaults.h"

class RutherfordSteppingAction : public G4UserSteppingAction 
{
	public:
		
		RutherfordSteppingAction();
		~RutherfordSteppingAction();

		virtual void UserSteppingAction(const G4Step*) override;
	
	private:

		bool fIsParticleOut = false;
};

#endif
