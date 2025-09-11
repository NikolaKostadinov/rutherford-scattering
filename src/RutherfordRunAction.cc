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
	fTimer = new G4Timer;
	fElapsedTime = 0.0;

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
	
	fAlphaHistogramID          = DEFAULT_HISTOGRAM_ID;
	fAlphaHistogramTitle       = DEFAULT_ALPHA_TITLE;

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

	fDeltaHistogramID          = DEFAULT_HISTOGRAM_ID;
	fDeltaHistogramTitle       = DEFAULT_DELTA_TITLE;
	
	fMessenger = new RutherfordAnalysisMessenger(this);
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

G4double RutherfordRunAction::GetElapsedTime() const
{
	return fElapsedTime;
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

void RutherfordRunAction::SetAlphaHistogramTitle(G4String title)
{
	fAlphaHistogramTitle = title;
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

void RutherfordRunAction::SetDeltaHistogramTitle(G4String title)
{
	fDeltaHistogramTitle = title;
}

G4int RutherfordRunAction::GetAlphaEnergyHistogramID() const
{
	return fAlphaEnergyHistogramID;
}

G4int RutherfordRunAction::GetAlphaThetaHistogramID() const
{
	return fAlphaThetaHistogramID;
}

G4int RutherfordRunAction::GetAlphaHistogramID() const
{
	return fAlphaHistogramID;
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

G4int RutherfordRunAction::GetDeltaHistogramID() const
{
	return fDeltaHistogramID;
}

void RutherfordRunAction::BeginOfRunAction(const G4Run*)
{
	G4cout << G4endl;
	
	fTimer->Start();
	fElapsedTime = 0.0;

	auto analysisManager = G4AnalysisManager::Instance();

	if (analysisManager)
	{
		analysisManager->OpenFile(fFileOut);
		
		fAlphaEnergyHistogramID = analysisManager->CreateH1(DEFAULT_ALPHA_ENERGY_NAME, fAlphaEnergyHistogramTitle, fAlphaEnergyHistogramBins, fAlphaEnergyHistogramMin / DEFAULT_HIGH_ENERGY_UNIT, fAlphaEnergyHistogramMax / DEFAULT_HIGH_ENERGY_UNIT);
		fAlphaThetaHistogramID  = analysisManager->CreateH1(DEFAULT_ALPHA_THETA_NAME,  fAlphaThetaHistogramTitle,  fAlphaThetaHistogramBins,  fAlphaThetaHistogramMin / DEFAULT_ANGLE_UNIT,   fAlphaThetaHistogramMax / DEFAULT_ANGLE_UNIT);
		fDeltasHistogramID      = analysisManager->CreateH1(DEFAULT_DELTAS_NAME,  fDeltasHistogramTitle,      fDeltasHistogramBins,      fDeltasHistogramMin,                            fDeltasHistogramMax);
		fDeltaEnergyHistogramID = analysisManager->CreateH1(DEFAULT_DELTA_ENERGY_NAME, fDeltaEnergyHistogramTitle, fDeltaEnergyHistogramBins, fDeltaEnergyHistogramMin / DEFAULT_LOW_ENERGY_UNIT, fDeltaEnergyHistogramMax / DEFAULT_LOW_ENERGY_UNIT);
		fDeltaThetaHistogramID  = analysisManager->CreateH1(DEFAULT_DELTA_THETA_NAME,  fDeltaThetaHistogramTitle,  fDeltaThetaHistogramBins,  fDeltaThetaHistogramMin / DEFAULT_ANGLE_UNIT,   fDeltaThetaHistogramMax / DEFAULT_ANGLE_UNIT);

		fAlphaHistogramID = analysisManager->CreateH2(
			DEFAULT_ALPHA_NAME,
			fAlphaHistogramTitle,
			fAlphaThetaHistogramBins,  fAlphaThetaHistogramMin  / DEFAULT_ANGLE_UNIT,       fAlphaThetaHistogramMax  / DEFAULT_ANGLE_UNIT,
			fAlphaEnergyHistogramBins, fAlphaEnergyHistogramMin / DEFAULT_HIGH_ENERGY_UNIT, fAlphaEnergyHistogramMax / DEFAULT_HIGH_ENERGY_UNIT
		);
		fDeltaHistogramID = analysisManager->CreateH2(
			DEFAULT_DELTA_NAME,
			fDeltaHistogramTitle,
			fDeltaThetaHistogramBins,  fDeltaThetaHistogramMin  / DEFAULT_ANGLE_UNIT,       fDeltaThetaHistogramMax  / DEFAULT_ANGLE_UNIT,
			fDeltaEnergyHistogramBins, fDeltaEnergyHistogramMin / DEFAULT_LOW_ENERGY_UNIT,  fDeltaEnergyHistogramMax / DEFAULT_LOW_ENERGY_UNIT
		);
	}

}

void RutherfordRunAction::EndOfRunAction(const G4Run*)
{
	G4cout << G4endl;

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

	auto detectorElectronDensity = detectorConstruction->GetDetectorElectronDensity();
	auto detectorThickness       = detectorConstruction->GetDetectorThickness();
	auto alphaEnergyIn           = generatorAction->GetAlphaEnergy();
	auto initialDistance         = generatorAction->GetAlphaDistance();
	
	auto meanAlphaLoss   = alphaEnergyIn - analysisManager->GetH1(fAlphaEnergyHistogramID)->mean();
	auto meanDeltaEnergy = analysisManager->GetH1(fDeltaEnergyHistogramID)->mean();
	auto meanDeltas      = analysisManager->GetH1(fDeltasHistogramID)->mean();	

	auto me = 511 * keV;
	auto ma = 3.5 * GeV;
	auto tmax = 4 * me / ma * alphaEnergyIn;
	auto tion = 7.86 * eV;

	auto hardCrossSection = meanDeltas/detectorElectronDensity/detectorThickness;
	auto minCrossSection  = meanAlphaLoss/tmax/detectorElectronDensity/detectorThickness;
	auto ionCrossSection  = meanAlphaLoss/tion/detectorElectronDensity/detectorThickness;
	auto stoppingPower    = meanAlphaLoss / detectorThickness;
	
	G4cout << std::scientific;
	G4cout << "σ_hard = " << hardCrossSection / barn << " b" << G4endl;
	G4cout << "σ_min  = " << minCrossSection  / barn << " b" << G4endl;
	G4cout << "σ      = " << ionCrossSection  / barn << " b" << G4endl;
	G4cout << std::fixed;
	G4cout << "dE/dz  = " << stoppingPower / (keV/um) << " keV/um" << G4endl;
	G4cout << "t_max  = " << tmax / keV << " keV" << G4endl;

	if (analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();

		TFile file(analysisManager->GetFileName().c_str(), "UPDATE");
		
		TParameter<double> thicknessParameter("Thickness", detectorThickness / DEFAULT_SHORT_LENGTH_UNIT);
		TParameter<double> energyParameter("Energy",       alphaEnergyIn / DEFAULT_HIGH_ENERGY_UNIT);
		TParameter<double> distanceParameter("Distance",   initialDistance / DEFAULT_LONG_LENGTH_UNIT);

		thicknessParameter.Write();
		energyParameter.Write();
		distanceParameter.Write();

		file.Close();
	}

	fTimer->Stop();
}
