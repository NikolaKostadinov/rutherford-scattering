#ifndef ANALYSIS_MESSENGER_HH
#define ANALYSIS_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithAString.hh>

#include "RutherfordDefaults.h"

class RutherfordRunAction;

class RutherfordAnalysisMessenger : public G4UImessenger
{
	public:

		RutherfordAnalysisMessenger(RutherfordRunAction*);
		~RutherfordAnalysisMessenger();


		void SetNewValue(G4UIcommand*, G4String) override;

	private:
		
		G4UIdirectory*			fDirectory;
		
		G4UIcmdWithAString*		fFileOutCmd;

		// Energy Spectrum dσ/dE
		G4UIcmdWithAString*		fETitleCmd;
		G4UIcmdWithAnInteger*		fEBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fEMinCmd;
		G4UIcmdWithADoubleAndUnit*	fEMaxCmd;
		
		// Differential Cross Section dσ/dΩ
		G4UIcmdWithAString*		fThetaTitleCmd;
		G4UIcmdWithAnInteger*		fThetaBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fThetaMinCmd;
		G4UIcmdWithADoubleAndUnit*	fThetaMaxCmd;
		
		RutherfordRunAction*		fRunAction;
		
};

#endif
