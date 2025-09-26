#ifndef ANALYSIS_MESSENGER_HH
#define ANALYSIS_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>

#include "RutherfordCommands.h"

class RutherfordRunAction;

class RutherfordRunMessenger : public G4UImessenger
{
	public:

		RutherfordRunMessenger(RutherfordRunAction*);
		virtual ~RutherfordRunMessenger();

		void SetNewValue(G4UIcommand*, G4String) override;

	private:
		
		G4UIdirectory*			fDirectory = new G4UIdirectory(ANALYSIS_CMD);
		
		G4UIcmdWithAString*		fFileOutCmd = new G4UIcmdWithAString(ANALYSIS_FILE_CMD, this);
		
		RutherfordRunAction*		fRunAction;
};

#endif
