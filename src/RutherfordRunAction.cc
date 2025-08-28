#include "../include/RutherfordRunAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include <TFile.h>
#include <TParameter.h>

#include "../include/RutherfordGeneratorAction.hh"
#include "../include/RutherfordDetectorConstruction.hh"

RutherfordRunAction::RutherfordRunAction() :

	fFileOut(DEFAULT_FILE_OUT),
	fETitle(DEFAULT_ENERGY_TITLE),
	fEBins(DEFAULT_ENERGY_BINS),
	fEMin(DEFAULT_ENERGY_MIN),
	fEMax(DEFAULT_ENERGY_MAX),
	fThetaTitle(DEFAULT_THETA_TITLE),
	fThetaBins(DEFAULT_THETA_BINS),
	fThetaMin(DEFAULT_THETA_MIN),
	fThetaMax(DEFAULT_THETA_MAX)
{
	fMessenger = new RutherfordAnalysisMessenger(this);
}

RutherfordRunAction::~RutherfordRunAction()
{
	delete fMessenger;

	delete G4AnalysisManager::Instance();
}

void RutherfordRunAction::SetFileOut(G4String file)
{
	fFileOut = file;
}

void RutherfordRunAction::SetETitle(G4String title)
{
	fETitle = title;
}

void RutherfordRunAction::SetEBins(G4int bins)
{
	fEBins = bins;
}

void RutherfordRunAction::SetEMin(G4double min)
{
	fEMin = min;
}

void RutherfordRunAction::SetEMax(G4double max)
{
	fEMax = max;
}

void RutherfordRunAction::SetThetaTitle(G4String title)
{
	fThetaTitle = title;
}

void RutherfordRunAction::SetThetaBins(G4int bins)
{
	fThetaBins = bins;
}

void RutherfordRunAction::SetThetaMin(G4double min)
{
	fThetaMin = min;
}

void RutherfordRunAction::SetThetaMax(G4double max)
{
	fThetaMax = max;
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();

	if (analysisManager)
	{
		analysisManager->OpenFile(fFileOut);
		
		analysisManager->CreateH1("histoEnergy", fETitle,     fEBins,     fEMin / MeV,     fEMax / MeV    );
		analysisManager->CreateH1("histoTheta",  fThetaTitle, fThetaBins, fThetaMin / deg, fThetaMax / deg);
	}
}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	auto construction = dynamic_cast<RutherfordDetectorConstruction*>(
		const_cast<G4VUserDetectorConstruction*>(
			G4RunManager::GetRunManager()->GetUserDetectorConstruction()
		)
	);
	auto generator = dynamic_cast<RutherfordGeneratorAction*>(
		const_cast<G4VUserPrimaryGeneratorAction*>(
			G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()
		)
	);
	
	G4double	thickness;
	if (generator)	thickness = construction->GetDetectorThickness();
	else		thickness = DEFAULT_DETECTOR_THICKNESS;
	
	G4double	energy;
	if (generator)	energy = generator->GetEnergy();
	else		energy = DEFAULT_ENERGY;

	G4double	distance;
	if (generator)	distance = generator->GetDistance();
	else		distance = DEFAULT_DISTANCE;

	if (analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();

		TFile file(analysisManager->GetFileName().c_str(), "UPDATE");
		
		TParameter<double> thicknessParameter("Thickness", thickness / um);
		thicknessParameter.Write();
		
		TParameter<double> energyParameter("Energy", energy / MeV);
		energyParameter.Write();
		
		TParameter<double> distanceParameter("Distance", distance / cm);
		distanceParameter.Write();
		
		file.Close();
	}
}
