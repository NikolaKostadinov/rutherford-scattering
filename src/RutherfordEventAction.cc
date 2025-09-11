#include "../include/RutherfordEventAction.hh"

#include <iomanip>

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordDetectorConstruction.hh"
#include "../include/RutherfordGeneratorAction.hh"

RutherfordEventAction::RutherfordEventAction()
{

}

RutherfordEventAction::~RutherfordEventAction()
{

}

void RutherfordEventAction::SetAlphaEnergyOut(G4double energy)
{
	fAlphaEnergyOut = energy;
}

void RutherfordEventAction::SetAlphaTheta(G4double theta)
{
	fAlphaTheta = theta;
}

void RutherfordEventAction::IncrementDeltas()
{
	++fDeltas;
}

void RutherfordEventAction::AddDeltaEnergy(G4double energy)
{
	fDeltasEnergy += energy;
}

void RutherfordEventAction::BeginOfEventAction(const G4Event* event)
{
	fAlphaEnergyOut  = DEFAULT_ALPHA_ENERGY;
	fAlphaTheta      = 0.0;
	fDeltas          = 0;
	fDeltasEnergy    = 0.0;
}

void RutherfordEventAction::EndOfEventAction(const G4Event* event)
{
	auto eventID = event->GetEventID();

	auto runManager = G4RunManager::GetRunManager();
	auto runAction  = dynamic_cast<RutherfordRunAction*>(const_cast<G4UserRunAction*>(runManager->GetUserRunAction()));
	auto numberOfEvents = runManager->GetNumberOfEventsToBeProcessed();
	
	auto generatorAction = dynamic_cast<RutherfordGeneratorAction*>(const_cast<G4VUserPrimaryGeneratorAction*>(runManager->GetUserPrimaryGeneratorAction()));
	auto alphaEnergyIn = generatorAction->GetAlphaEnergy();

	auto analysisManager = G4AnalysisManager::Instance();
		
	G4int deltasHistogramID = runAction->GetDeltasHistogramID();
	analysisManager->FillH1(deltasHistogramID, fDeltas);
	
	runAction->SaveLapTime();
	auto elapsedTime = runAction->GetElapsedTime();
	auto progress = (G4double) (eventID + 1) / (G4double) numberOfEvents;
	auto remainingTime = (1.0 - progress)/progress * elapsedTime;

	auto freq = (eventID + 1) / elapsedTime;
	
	int ERTmin = int(elapsedTime/s) / 60;
	int ERTs   = int(elapsedTime/s) % 60;
	int ETAmin = int(remainingTime/s) / 60;
	int ETAs   = int(remainingTime/s) % 60;
		
	G4cout << "\r" << std::string(2*BAR_SIZE, ' ') << "\r";
	G4cout.flush();

	G4cout << std::fixed << std::setprecision(0);
	G4cout << "event [" << eventID << "]";
	G4cout << std::string(TAB_SIZE, ' ');
	G4cout << "α+ loss ";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << (alphaEnergyIn - fAlphaEnergyOut) / keV << " keV";
	G4cout << " = " << alphaEnergyIn / keV << " keV - " << fAlphaEnergyOut / keV << " keV";
	G4cout << std::string(TAB_SIZE, ' ');
	G4cout << "e- init ";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << fDeltasEnergy / keV << " keV";
	G4cout << std::setprecision(1);
	G4cout << " = " << fDeltas << " * " << (fDeltasEnergy/fDeltas) / keV << " keV";
	G4cout << G4endl;

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
	G4cout << "[" << int(progress * 100.0) << "%]";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ERT " << ERTmin << "min " << ERTs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "ETA " << ETAmin << "min " << ETAs << "s";
	G4cout << std::string(MARGIN_SIZE, ' ');
	G4cout << "freq " << int(freq / hertz) << "Hz";
	G4cout.flush();
	if (progress == 1.0) G4cout << G4endl;
}
