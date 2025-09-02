#include "../include/RutherfordRunAction.hh"

#include <G4RunManager.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include <TFile.h>
#include <TParameter.h>

#include "../include/RutherfordGeneratorAction.hh"
#include "../include/RutherfordDetectorConstruction.hh"

RutherfordRunAction::RutherfordRunAction()
{
	fFileOut = DEFAULT_FILE_OUT;

	fAlphaEnergyHistogramID    = DEFAULT_HISTOGRAM_ID;
	fAlphaEnergyHistogramTitle = DEFAULT_ALPHA_ENERGY_TITLE;
	fAlphaEnergyHistogramBins  = DEFAULT_ALPHA_ENERGY_BINS;
	fAlphaEnergyHistogramMin   = DEFAULT_ALPHA_ENERGY_MIN;
	fAlphaEnergyHistogramMax   = DEFAULT_ALPHA_ENERGY_MAX;
	
	fAlphaThetaHistogramID     = DEFAULT_HISTOGRAM_ID;
	fAlphaThetaHistogramTitle  = DEFAULT_ALPHA_THETA_TITLE;
	fAlphaThetaHistogramBins   = DEFAULT_ALPHA_THETA_BINS;
	fAlphaThetaHistogramMin    = DEFAULT_ALPHA_THETA_MIN;
	fAlphaThetaHistogramMax    = DEFAULT_ALPHA_THETA_MAX;

	fDeltasHistogramID         = DEFAULT_HISTOGRAM_ID;
	fDeltasHistogramTitle      = DEFAULT_DELTAS_TITLE;
	fDeltasHistogramBins       = DEFAULT_DELTAS_BINS;
	fDeltasHistogramMin        = DEFAULT_DELTAS_MIN;
	fDeltasHistogramMax        = DEFAULT_DELTAS_MAX;
	
	fDeltaEnergyHistogramID    = DEFAULT_HISTOGRAM_ID;
	fDeltaEnergyHistogramTitle = DEFAULT_DELTA_ENERGY_TITLE;
	fDeltaEnergyHistogramBins  = DEFAULT_DELTA_ENERGY_BINS;
	fDeltaEnergyHistogramMin   = DEFAULT_DELTA_ENERGY_MIN;
	fDeltaEnergyHistogramMax   = DEFAULT_DELTA_ENERGY_MAX;
	
	fDeltaThetaHistogramID     = DEFAULT_HISTOGRAM_ID;
	fDeltaThetaHistogramTitle  = DEFAULT_DELTA_THETA_TITLE;
	fDeltaThetaHistogramBins   = DEFAULT_DELTA_THETA_BINS;
	fDeltaThetaHistogramMin    = DEFAULT_DELTA_THETA_MIN;
	fDeltaThetaHistogramMax    = DEFAULT_DELTA_THETA_MAX;

	fMessenger = new RutherfordAnalysisMessenger(this);
}

RutherfordRunAction::~RutherfordRunAction()
{
	delete fMessenger;
}

void RutherfordRunAction::SetFileOut(G4String file)
{
	fFileOut = file;
}

void RutherfordRunAction::SetAlphaEnergyHistogramTitle(G4String title)
{
	fAlphaEnergyHistogramTitle = title;
}

void RutherfordRunAction::SetAlphaEnergyHistogramBins(G4int bins)
{
	fAlphaEnergyHistogramBins = bins;
}

void RutherfordRunAction::SetAlphaEnergyHistogramMin(G4double min)
{
	fAlphaEnergyHistogramMin = min;
}

void RutherfordRunAction::SetAlphaEnergyHistogramMax(G4double max)
{
	fAlphaEnergyHistogramMax = max;
}

void RutherfordRunAction::SetAlphaThetaHistogramTitle(G4String title)
{
	fAlphaThetaHistogramTitle = title;
}

void RutherfordRunAction::SetAlphaThetaHistogramBins(G4int bins)
{
	fAlphaThetaHistogramBins = bins;
}

void RutherfordRunAction::SetAlphaThetaHistogramMin(G4double min)
{
	fAlphaThetaHistogramMin = min;
}

void RutherfordRunAction::SetAlphaThetaHistogramMax(G4double max)
{
	fAlphaThetaHistogramMax = max;
}

void RutherfordRunAction::SetDeltasHistogramTitle(G4String title)
{
	fDeltasHistogramTitle = title;
}

void RutherfordRunAction::SetDeltasHistogramBins(G4int bins)
{
	fDeltasHistogramBins = bins;
}

void RutherfordRunAction::SetDeltasHistogramMin(G4int min)
{
	fDeltasHistogramMin = min;
}

void RutherfordRunAction::SetDeltasHistogramMax(G4int max)
{
	fDeltasHistogramMax = max;
}

void RutherfordRunAction::SetDeltaEnergyHistogramTitle(G4String title)
{
	fDeltaEnergyHistogramTitle = title;
}

void RutherfordRunAction::SetDeltaEnergyHistogramBins(G4int bins)
{
	fDeltaEnergyHistogramBins = bins;
}

void RutherfordRunAction::SetDeltaEnergyHistogramMin(G4double min)
{
	fDeltaEnergyHistogramMin = min;
}

void RutherfordRunAction::SetDeltaEnergyHistogramMax(G4double max)
{
	fDeltaEnergyHistogramMax = max;
}

void RutherfordRunAction::SetDeltaThetaHistogramTitle(G4String title)
{
	fDeltaThetaHistogramTitle = title;
}

void RutherfordRunAction::SetDeltaThetaHistogramBins(G4int bins)
{
	fDeltaThetaHistogramBins = bins;
}

void RutherfordRunAction::SetDeltaThetaHistogramMin(G4double min)
{
	fDeltaThetaHistogramMin = min;
}

void RutherfordRunAction::SetDeltaThetaHistogramMax(G4double max)
{
	fDeltaThetaHistogramMax = max;
}

G4int RutherfordRunAction::GetAlphaEnergyHistogramID() const
{
	return fAlphaEnergyHistogramID;
}

G4int RutherfordRunAction::GetAlphaThetaHistogramID() const
{
	return fAlphaThetaHistogramID;
}

G4int RutherfordRunAction::GetDeltasHistogramID() const
{
	return fDeltasHistogramID;
}

G4int RutherfordRunAction::GetDeltaEnergyHistogramID() const
{
	return fDeltaEnergyHistogramID;
}

G4int RutherfordRunAction::GetDeltaThetaHistogramID() const
{
	return fDeltaThetaHistogramID;
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();

	if (analysisManager)
	{
		analysisManager->OpenFile(fFileOut);
		
		fAlphaEnergyHistogramID = analysisManager->CreateH1("histoEnergy", fAlphaEnergyHistogramTitle, fAlphaEnergyHistogramBins, fAlphaEnergyHistogramMin / DEFAULT_HIGH_ENERGY_UNIT, fAlphaEnergyHistogramMax / DEFAULT_HIGH_ENERGY_UNIT);
		fAlphaThetaHistogramID  = analysisManager->CreateH1("histoTheta",  fAlphaThetaHistogramTitle,  fAlphaThetaHistogramBins,  fAlphaThetaHistogramMin / DEFAULT_ANGLE_UNIT,   fAlphaThetaHistogramMax / DEFAULT_ANGLE_UNIT);
		fDeltasHistogramID      = analysisManager->CreateH1("histoDelta",  fDeltasHistogramTitle,      fDeltasHistogramBins,      fDeltasHistogramMin,                            fDeltasHistogramMax);
		fDeltaEnergyHistogramID = analysisManager->CreateH1("histoEnergy", fDeltaEnergyHistogramTitle, fDeltaEnergyHistogramBins, fDeltaEnergyHistogramMin / DEFAULT_LOW_ENERGY_UNIT, fDeltaEnergyHistogramMax / DEFAULT_LOW_ENERGY_UNIT);
		fDeltaThetaHistogramID  = analysisManager->CreateH1("histoTheta",  fDeltaThetaHistogramTitle,  fDeltaThetaHistogramBins,  fDeltaThetaHistogramMin / DEFAULT_ANGLE_UNIT,   fDeltaThetaHistogramMax / DEFAULT_ANGLE_UNIT);
	}
}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	auto detectorConstruction = dynamic_cast<RutherfordDetectorConstruction*>(
		const_cast<G4VUserDetectorConstruction*>(
			G4RunManager::GetRunManager()->GetUserDetectorConstruction()
		)
	);
	auto generatorAction = dynamic_cast<RutherfordGeneratorAction*>(
		const_cast<G4VUserPrimaryGeneratorAction*>(
			G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()
		)
	);

	G4double		thickness;
	if (generatorAction)	thickness = detectorConstruction->GetDetectorThickness();
	else			thickness = DEFAULT_DETECTOR_THICKNESS;

	G4double		energy;
	if (generatorAction)	energy = generatorAction->GetAlphaEnergy();
	else			energy = DEFAULT_ALPHA_ENERGY;

	G4double		distance;
	if (generatorAction)	distance = generatorAction->GetAlphaDistance();
	else			distance = DEFAULT_ALPHA_DISTANCE;

	if (analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();

		TFile file(analysisManager->GetFileName().c_str(), "UPDATE");
		
		TParameter<double> thicknessParameter("Thickness", thickness / DEFAULT_SHORT_LENGTH_UNIT);
		TParameter<double> energyParameter("Energy", energy / DEFAULT_HIGH_ENERGY_UNIT);
		TParameter<double> distanceParameter("Distance", distance / DEFAULT_LONG_LENGTH_UNIT);

		thicknessParameter.Write();
		energyParameter.Write();
		distanceParameter.Write();

		file.Close();
	}
}
