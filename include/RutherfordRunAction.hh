#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include <G4UserRunAction.hh>

#include "RutherfordDefaults.h"
#include "RutherfordAnalysisMessenger.hh"

class RutherfordRunAction : public G4UserRunAction
{
	public:

		RutherfordRunAction();
		~RutherfordRunAction();

		void SetFileOut(G4String);
		
		void SetETitle(G4String);
		void SetEBins(G4int);
		void SetEMin(G4double);
		void SetEMax(G4double);

		void SetThetaTitle(G4String);
		void SetThetaBins(G4int);
		void SetThetaMin(G4double);
		void SetThetaMax(G4double);

		void BeginOfRunAction(const G4Run*) override;
		void   EndOfRunAction(const G4Run*) override;

	private:
		
		G4String			fFileOut;

		G4String			fETitle;
		G4int				fEBins;
		G4double			fEMin;
		G4double			fEMax;

		G4String			fThetaTitle;
		G4int				fThetaBins;
		G4double			fThetaMin;
		G4double			fThetaMax;
		
		RutherfordAnalysisMessenger*	fMessenger;
};

#endif
