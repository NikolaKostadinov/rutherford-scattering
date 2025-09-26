#include "../include/RutherfordEventAction.hh"

#include <iomanip>

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordDetectorConstruction.hh"
#include "../include/RutherfordGeneratorAction.hh"

void RutherfordEventAction::BeginOfEventAction(const G4Event* event)
{

}

void RutherfordEventAction::EndOfEventAction(const G4Event* event)
{
	auto eventID = event->GetEventID();

	auto runManager = G4RunManager::GetRunManager();
	auto runAction  = dynamic_cast<RutherfordRunAction*>(const_cast<G4UserRunAction*>(runManager->GetUserRunAction()));
	auto numberOfEvents = runManager->GetNumberOfEventsToBeProcessed();
	
	runAction->SaveLapTime();
	auto elapsedTime = runAction->GetElapsedTime();
	auto progress = (G4double) (eventID + 1) / (G4double) numberOfEvents;
	auto remainingTime = (1.0 - progress)/progress * elapsedTime;

	auto freq = (eventID + 1) / elapsedTime;
	
	int ERTmin = int(elapsedTime/s) / 60;
	int ERTs   = int(elapsedTime/s) % 60;
	int ETAmin = int(remainingTime/s) / 60;
	int ETAs   = int(remainingTime/s) % 60;

	G4cout << '\r';
	G4cout << "[*";
	int position = progress * BAR_SIZE;
	for (int i = 0; i < BAR_SIZE; ++i)
	{
		if      (i <  position) G4cout << '-';
		else if (i == position) G4cout << '>';
		else                    G4cout << ' ';
	}	
	G4cout << "*]";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << eventID+1 << "/" << numberOfEvents << " events";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "[ " << int(progress * 100.0) << "%]";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ERT " << ERTmin << "min " << ERTs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ETA " << ETAmin << "min " << ETAs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "freq " << float(int(freq / kilohertz * 10)) / 10 << "kHz";
	G4cout.flush();
	if (progress == 1.0) G4cout << G4endl;
}
