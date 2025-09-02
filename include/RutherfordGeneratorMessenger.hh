#ifndef GENERATOR_MESSENGER_HH
#define GENERATOR_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "RutherfordDefaults.h"

class RutherfordGeneratorAction;

class RutherfordGeneratorMessenger : public G4UImessenger
{
	public:
		RutherfordGeneratorMessenger(RutherfordGeneratorAction*);
		~RutherfordGeneratorMessenger();
	
		void SetNewValue(G4UIcommand*, G4String) override;

	private:
		
		G4UIdirectory*			fDirectory;
		
		G4UIcmdWithADoubleAndUnit* 	fAlphaEnergyCmd;
		G4UIcmdWithADoubleAndUnit* 	fAlphaDistanceCmd;
		
		RutherfordGeneratorAction* 	fGenerator;
};

#endif
