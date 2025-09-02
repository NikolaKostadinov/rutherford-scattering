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
		
		void SetEnergyHistogramTitle(G4String);
		void SetEnergyHistogramBins(G4int);
		void SetEnergyHistogramMin(G4double);
		void SetEnergyHistogramMax(G4double);

		void SetThetaHistogramTitle(G4String);
		void SetThetaHistogramBins(G4int);
		void SetThetaHistogramMin(G4double);
		void SetThetaHistogramMax(G4double);

		G4int GetEnergyHistogramID() const;
		G4int GetThetaHistogramID()  const;

		void BeginOfRunAction(const G4Run*) override;
		void   EndOfRunAction(const G4Run*) override;

	private:
		
		G4String			fFileOut;
		
		G4int				fEnergyHistogramID;
		G4String			fEnergyHistogramTitle;
		G4int				fEnergyHistogramBins;
		G4double			fEnergyHistogramMin;
		G4double			fEnergyHistogramMax;
		
		G4int				fThetaHistogramID;
		G4String			fThetaHistogramTitle;
		G4int				fThetaHistogramBins;
		G4double			fThetaHistogramMin;
		G4double			fThetaHistogramMax;
		
		RutherfordAnalysisMessenger*	fMessenger;
};

#endif
