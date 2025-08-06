#include "../include/RutherfordRunAction.hh"

RutherfordRunAction::RutherfordRunAction() :
	G4UserRunAction(),
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
		analysisManager->OpenFile(OUTPUT_FILE);
		analysisManager->CreateH1("histoEnergy", fETitle,     fEBins,     fEMin / MeV,     fEMax / MeV    );
		analysisManager->CreateH1("histoTheta",  fThetaTitle, fThetaBins, fThetaMin / deg, fThetaMax / deg);
	}
}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	if (analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();
	}
}
