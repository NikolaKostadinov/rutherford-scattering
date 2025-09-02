#include "../include/RutherfordAnalysisMessenger.hh"
#include "../include/RutherfordRunAction.hh"

#include <G4UnitsTable.hh>
#include "../include/RutherfordCommands.h"

RutherfordAnalysisMessenger::RutherfordAnalysisMessenger(RutherfordRunAction* runAction) : fRunAction(runAction)
{
	fDirectory = new G4UIdirectory(ANALYSIS_CMD);
	fDirectory->SetGuidance("Commands for simulation analysis. This includes (only) ROOT histogram setup.");

	fFileOutCmd = new G4UIcmdWithAString(OUTPUT_CMD, this);
	fFileOutCmd->SetGuidance("Path to analysis file.");
	fFileOutCmd->SetDefaultValue(DEFAULT_FILE_OUT);
	
	fEnergyHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_ENERGY_TITLE_CMD, this);
	fEnergyHistogramTitleCmd->SetGuidance("Title of energy spectrum histogram.");
	fEnergyHistogramTitleCmd->SetDefaultValue(DEFAULT_ENERGY_TITLE);
	
	fEnergyHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_ENERGY_BINS_CMD, this);
	fEnergyHistogramBinsCmd->SetGuidance("Number of bins for energy spectrum histogram.");
	fEnergyHistogramBinsCmd->SetDefaultValue(DEFAULT_ENERGY_BINS);
	
	fEnergyHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ENERGY_MIN_CMD, this);
	fEnergyHistogramMinCmd->SetGuidance("Minimum histogram energy.");
	fEnergyHistogramMinCmd->SetUnitCategory("Energy");
	fEnergyHistogramMinCmd->SetDefaultValue(DEFAULT_ENERGY_MIN / DEFAULT_ENERGY_UNIT);
	fEnergyHistogramMinCmd->SetDefaultUnit(DEFAULT_ENERGY_UNIT_STRING);
	
	fEnergyHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ENERGY_MAX_CMD, this);
	fEnergyHistogramMaxCmd->SetGuidance("Maximum histogram energy.");
	fEnergyHistogramMaxCmd->SetUnitCategory("Energy");
	fEnergyHistogramMaxCmd->SetDefaultValue(DEFAULT_ENERGY_MAX / DEFAULT_ENERGY_UNIT);
	fEnergyHistogramMaxCmd->SetDefaultUnit(DEFAULT_ENERGY_UNIT_STRING);
	
	fThetaHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_THETA_TITLE_CMD, this);
	fThetaHistogramTitleCmd->SetGuidance("Title of differential cross section histogram.");
	fThetaHistogramTitleCmd->SetDefaultValue(DEFAULT_THETA_TITLE);
	
	fThetaHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_THETA_BINS_CMD, this);
	fThetaHistogramBinsCmd->SetGuidance("Number of bins for differential cross section (scattering angle distribution).");
	fThetaHistogramBinsCmd->SetDefaultValue(DEFAULT_THETA_BINS);
	
	fThetaHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_THETA_MIN_CMD, this);
	fThetaHistogramMinCmd->SetGuidance("Minimum histogram theta (scattering angle).");
	fThetaHistogramMinCmd->SetUnitCategory("Angle");
	fThetaHistogramMinCmd->SetDefaultValue(DEFAULT_THETA_MIN / DEFAULT_ANGLE_UNIT);
	fThetaHistogramMinCmd->SetDefaultUnit(DEFAULT_ANGLE_UNIT_STRING);
	
	fThetaHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_THETA_MAX_CMD, this);
	fThetaHistogramMaxCmd->SetGuidance("Maximum histogram theta (scattering angle).");
	fThetaHistogramMaxCmd->SetUnitCategory("Angle");
	fThetaHistogramMaxCmd->SetDefaultValue(DEFAULT_THETA_MAX / DEFAULT_ANGLE_UNIT);
	fThetaHistogramMaxCmd->SetDefaultUnit(DEFAULT_ANGLE_UNIT_STRING);
}

RutherfordAnalysisMessenger::~RutherfordAnalysisMessenger()
{
	delete fDirectory;
	delete fFileOutCmd;
	delete fEnergyHistogramTitleCmd;
	delete fEnergyHistogramBinsCmd;
	delete fEnergyHistogramMinCmd;
	delete fEnergyHistogramMaxCmd;
	delete fThetaHistogramTitleCmd;
	delete fThetaHistogramBinsCmd;
	delete fThetaHistogramMinCmd;
	delete fThetaHistogramMaxCmd;
}

void RutherfordAnalysisMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fFileOutCmd)
	{
		fRunAction->SetFileOut(value);
	}
	else if (cmd == fEnergyHistogramTitleCmd)
	{
		fRunAction->SetEnergyHistogramTitle(value);
	}
	else if (cmd == fEnergyHistogramBinsCmd)
	{
		auto bins = fEnergyHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetEnergyHistogramBins(bins);
	}
	else if (cmd == fEnergyHistogramMinCmd)
	{
		auto min = fEnergyHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetEnergyHistogramMin(min);
	}
	else if (cmd == fEnergyHistogramMaxCmd)
	{
		auto max = fEnergyHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetEnergyHistogramMax(max);
	}
	else if (cmd == fThetaHistogramTitleCmd)
	{
		fRunAction->SetThetaHistogramTitle(value);
	}
	else if (cmd == fThetaHistogramBinsCmd)
	{
		auto bins = fThetaHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetThetaHistogramBins(bins);
	}
	else if (cmd == fThetaHistogramMinCmd)
	{
		auto min = fThetaHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetThetaHistogramMin(min);
	}
	else if (cmd == fThetaHistogramMaxCmd)
	{
		auto max = fThetaHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetThetaHistogramMax(max);
	}
}
