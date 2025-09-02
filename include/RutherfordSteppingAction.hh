#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>

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
