#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH

#include <G4UserEventAction.hh>
#include <globals.hh>

class RutherfordEventAction : public G4UserEventAction
{
	public:

		RutherfordEventAction();
		~RutherfordEventAction();
		
		void SetAlphaEnergyOut(G4double);
		void SetAlphaTheta(G4double);
		void IncrementDeltas();
		void AddDeltaEnergy(G4double);
		
		void BeginOfEventAction(const G4Event* event) override;
		void   EndOfEventAction(const G4Event* event) override;
	
	private:
		
		G4double	fAlphaEnergyOut;
		G4double	fAlphaTheta;
		G4int		fDeltas;
		G4double	fDeltasEnergy;
};

#endif
