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
		G4UIcmdWithAString*		fEnergyHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fEnergyHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fEnergyHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fEnergyHistogramMaxCmd;
		
		// Differential Cross Section dσ/dΩ
		G4UIcmdWithAString*		fThetaHistogramTitleCmd;
		G4UIcmdWithAnInteger*		fThetaHistogramBinsCmd;
		G4UIcmdWithADoubleAndUnit*	fThetaHistogramMinCmd;
		G4UIcmdWithADoubleAndUnit*	fThetaHistogramMaxCmd;
		
		RutherfordRunAction*		fRunAction;
};

#endif
