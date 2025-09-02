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

		G4UIcmdWithAString*		fAlphaEnergyHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fAlphaEnergyHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fAlphaEnergyHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fAlphaEnergyHistogramMaxCmd;
		
		G4UIcmdWithAString*		fAlphaThetaHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fAlphaThetaHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fAlphaThetaHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fAlphaThetaHistogramMaxCmd;
		
		G4UIcmdWithAString*		fDeltasHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fDeltasHistogramBinsCmd;
		G4UIcmdWithAnInteger*		fDeltasHistogramMinCmd;
		G4UIcmdWithAnInteger*		fDeltasHistogramMaxCmd;
		
		G4UIcmdWithAString*		fDeltaEnergyHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fDeltaEnergyHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fDeltaEnergyHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fDeltaEnergyHistogramMaxCmd;
		
		G4UIcmdWithAString*		fDeltaThetaHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fDeltaThetaHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fDeltaThetaHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fDeltaThetaHistogramMaxCmd;
		
		RutherfordRunAction*		fRunAction;
};

#endif
