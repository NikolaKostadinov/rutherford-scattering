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

	fEnergyHistogramID    = DEFAULT_HISTOGRAM_ID;
	fEnergyHistogramTitle = DEFAULT_ENERGY_TITLE;
	fEnergyHistogramBins  = DEFAULT_ENERGY_BINS;
	fEnergyHistogramMin   = DEFAULT_ENERGY_MIN;
	fEnergyHistogramMax   = DEFAULT_ENERGY_MAX;
	
	fThetaHistogramID     = DEFAULT_HISTOGRAM_ID;
	fThetaHistogramTitle  = DEFAULT_THETA_TITLE;
	fThetaHistogramBins   = DEFAULT_THETA_BINS;
	fThetaHistogramMin    = DEFAULT_THETA_MIN;
	fThetaHistogramMax    = DEFAULT_THETA_MAX;

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

void RutherfordRunAction::SetEnergyHistogramTitle(G4String title)
{
	fEnergyHistogramTitle = title;
}

void RutherfordRunAction::SetEnergyHistogramBins(G4int bins)
{
	fEnergyHistogramBins = bins;
}

void RutherfordRunAction::SetEnergyHistogramMin(G4double min)
{
	fEnergyHistogramMin = min;
}

void RutherfordRunAction::SetEnergyHistogramMax(G4double max)
{
	fEnergyHistogramMax = max;
}

void RutherfordRunAction::SetThetaHistogramTitle(G4String title)
{
	fThetaHistogramTitle = title;
}

void RutherfordRunAction::SetThetaHistogramBins(G4int bins)
{
	fThetaHistogramBins = bins;
}

void RutherfordRunAction::SetThetaHistogramMin(G4double min)
{
	fThetaHistogramMin = min;
}

void RutherfordRunAction::SetThetaHistogramMax(G4double max)
{
	fThetaHistogramMax = max;
}

G4int RutherfordRunAction::GetEnergyHistogramID() const
{
	return fEnergyHistogramID;
}

G4int RutherfordRunAction::GetThetaHistogramID() const
{
	return fThetaHistogramID;
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();

	if (analysisManager)
	{
		analysisManager->OpenFile(fFileOut);
		
		fEnergyHistogramID = analysisManager->CreateH1("histoEnergy", fEnergyHistogramTitle, fEnergyHistogramBins, fEnergyHistogramMin / DEFAULT_ENERGY_UNIT, fEnergyHistogramMax / DEFAULT_ENERGY_UNIT);
		fThetaHistogramID  = analysisManager->CreateH1("histoTheta",  fThetaHistogramTitle,  fThetaHistogramBins,  fThetaHistogramMin / DEFAULT_ANGLE_UNIT,   fThetaHistogramMax / DEFAULT_ENERGY_UNIT);
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
	if (generatorAction)	energy = generatorAction->GetEnergy();
	else			energy = DEFAULT_ENERGY;

	G4double		distance;
	if (generatorAction)	distance = generatorAction->GetDistance();
	else			distance = DEFAULT_DISTANCE;

	if (analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();

		TFile file(analysisManager->GetFileName().c_str(), "UPDATE");
		
		TParameter<double> thicknessParameter("Thickness", thickness / DEFAULT_SHORT_LENGTH_UNIT);
		thicknessParameter.Write();
		
		TParameter<double> energyParameter("Energy", energy / DEFAULT_ENERGY_UNIT);
		energyParameter.Write();
		
		TParameter<double> distanceParameter("Distance", distance / DEFAULT_LONG_LENGTH_UNIT);
		distanceParameter.Write();
		
		file.Close();
	}
}
