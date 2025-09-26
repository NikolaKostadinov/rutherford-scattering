#include "../include/RutherfordRunAction.hh"

#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordDefaults.h"

RutherfordRunAction::RutherfordRunAction()
{
	fTimer = new G4Timer;
	fElapsedTime = 0.0;

	fFileOut = DEFAULT_FILE_OUT;
	
	fMessenger = new RutherfordRunMessenger(this);
}

RutherfordRunAction::~RutherfordRunAction()
{
	delete fTimer;
	delete fMessenger;
}

G4double RutherfordRunAction::SaveLapTime()
{
	fTimer->Stop();
	G4double time = fTimer->GetRealElapsed() * s;
	fElapsedTime += time;
	fTimer->Start();
	return time;
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	fTimer->Start();
	fElapsedTime = 0.0;
}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	fTimer->Stop();
}
