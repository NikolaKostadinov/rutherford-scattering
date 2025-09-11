#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include <G4UserRunAction.hh>
#include <G4Timer.hh>

#include "RutherfordDefaults.h"
#include "RutherfordAnalysisMessenger.hh"

class RutherfordRunAction : public G4UserRunAction
{
	public:

		RutherfordRunAction();
		~RutherfordRunAction();
		
		G4double SaveLapTime();
		G4double GetElapsedTime() const;

		void SetFileOut(G4String);
		
		void SetAlphaEnergyHistogramTitle(G4String);
		void SetAlphaEnergyHistogramBins(G4int);
		void SetAlphaEnergyHistogramMin(G4double);
		void SetAlphaEnergyHistogramMax(G4double);

		void SetAlphaThetaHistogramTitle(G4String);
		void SetAlphaThetaHistogramBins(G4int);
		void SetAlphaThetaHistogramMin(G4double);
		void SetAlphaThetaHistogramMax(G4double);
		
		void SetAlphaHistogramTitle(G4String);

		void SetDeltasHistogramTitle(G4String);
		void SetDeltasHistogramBins(G4int);
		void SetDeltasHistogramMin(G4int);
		void SetDeltasHistogramMax(G4int);

		void SetDeltaEnergyHistogramTitle(G4String);
		void SetDeltaEnergyHistogramBins(G4int);
		void SetDeltaEnergyHistogramMin(G4double);
		void SetDeltaEnergyHistogramMax(G4double);

		void SetDeltaThetaHistogramTitle(G4String);
		void SetDeltaThetaHistogramBins(G4int);
		void SetDeltaThetaHistogramMin(G4double);
		void SetDeltaThetaHistogramMax(G4double);
		
		void SetDeltaHistogramTitle(G4String);

		G4int GetAlphaEnergyHistogramID() const;
		G4int GetAlphaThetaHistogramID()  const;
		G4int GetAlphaHistogramID()       const;
		G4int GetDeltasHistogramID()      const;
		G4int GetDeltaEnergyHistogramID() const;
		G4int GetDeltaThetaHistogramID()  const;
		G4int GetDeltaHistogramID()       const;

		void BeginOfRunAction(const G4Run*) override;
		void   EndOfRunAction(const G4Run*) override;

	private:
		
		G4Timer*			fTimer;
		G4double			fElapsedTime;

		// Path to Analysis File	
		G4String			fFileOut;
		
		// Final Energy of
		// Alpha Particle Histogram
		G4int				fAlphaEnergyHistogramID;
		G4String			fAlphaEnergyHistogramTitle;
		G4int				fAlphaEnergyHistogramBins;
		G4double			fAlphaEnergyHistogramMin;
		G4double			fAlphaEnergyHistogramMax;
		
		// Scattering Angle of
		// Alpha Particle Histogram
		G4int				fAlphaThetaHistogramID;
		G4String			fAlphaThetaHistogramTitle;
		G4int				fAlphaThetaHistogramBins;
		G4double			fAlphaThetaHistogramMin;
		G4double			fAlphaThetaHistogramMax;
		
		// Product of
		// Alpha Particle Histograms
		G4int				fAlphaHistogramID;
		G4String			fAlphaHistogramTitle;

		// Number of
		// Delta Particles Histogram	
		G4int				fDeltasHistogramID;
		G4String			fDeltasHistogramTitle;
		G4int				fDeltasHistogramBins;
		G4int				fDeltasHistogramMin;
		G4int				fDeltasHistogramMax;
		
		// Inital Energy of
		// Delta Particle Histogram
		G4int				fDeltaEnergyHistogramID;
		G4String			fDeltaEnergyHistogramTitle;
		G4int				fDeltaEnergyHistogramBins;
		G4double			fDeltaEnergyHistogramMin;
		G4double			fDeltaEnergyHistogramMax;
		
		// Scattering angle of
		// Delta Particle Histogram
		G4int				fDeltaThetaHistogramID;
		G4String			fDeltaThetaHistogramTitle;
		G4int				fDeltaThetaHistogramBins;
		G4double			fDeltaThetaHistogramMin;
		G4double			fDeltaThetaHistogramMax;
		
		// Product of
		// Delta Particle Histograms
		G4int				fDeltaHistogramID;
		G4String			fDeltaHistogramTitle;
		
		// Analysis Messenger
		RutherfordAnalysisMessenger*	fMessenger;
};

#endif
