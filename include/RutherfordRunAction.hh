#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include <G4UserRunAction.hh>
#include <G4Timer.hh>

#include "RutherfordRunMessenger.hh"

class RutherfordRunAction : public G4UserRunAction
{
	public:

		RutherfordRunAction();
		virtual ~RutherfordRunAction();
		
		void SetFileOut(G4String file) { fFileOut = file; };

		G4double SaveLapTime();

		G4int    GetNumberOfEvents() const { return fNumberOfEvents; };
		G4double GetElapsedTime()    const { return fElapsedTime;    };

		void UpdateNumberOfEvents();
		
		void BeginOfRunAction(const G4Run*) override;
		void   EndOfRunAction(const G4Run*) override;

	private:
		
		G4int			fNumberOfEvents;
		G4Timer*		fTimer;
		G4double		fElapsedTime;

		G4String		fFileOut;
		
		RutherfordRunMessenger*	fMessenger;
};

#endif
