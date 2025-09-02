#include "../include/RutherfordAnalysisMessenger.hh"
#include "../include/RutherfordRunAction.hh"

#include <G4UnitsTable.hh>

#include "../include/RutherfordCommands.h"

RutherfordAnalysisMessenger::RutherfordAnalysisMessenger(RutherfordRunAction* runAction) : fRunAction(runAction)
{
	fDirectory = new G4UIdirectory(ANALYSIS_CMD);
	fDirectory->SetGuidance("Commands for simulation analysis. This includes (only) ROOT histogram setup.");

	fFileOutCmd = new G4UIcmdWithAString(ANALYSIS_FILE_CMD, this);
	fFileOutCmd->SetGuidance("Path to analysis file.");
	fFileOutCmd->SetDefaultValue(DEFAULT_FILE_OUT);
	
	fAlphaEnergyHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_ALPHA_ENERGY_TITLE_CMD, this);
	fAlphaEnergyHistogramTitleCmd->SetGuidance("Title of energy spectrum histogram.");
	fAlphaEnergyHistogramTitleCmd->SetDefaultValue(DEFAULT_ALPHA_ENERGY_TITLE);
	
	fAlphaEnergyHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_ALPHA_ENERGY_BINS_CMD, this);
	fAlphaEnergyHistogramBinsCmd->SetGuidance("Number of bins for energy spectrum histogram.");
	fAlphaEnergyHistogramBinsCmd->SetDefaultValue(DEFAULT_ALPHA_ENERGY_BINS);
	
	fAlphaEnergyHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ALPHA_ENERGY_MIN_CMD, this);
	fAlphaEnergyHistogramMinCmd->SetGuidance("Minimum histogram energy.");
	fAlphaEnergyHistogramMinCmd->SetUnitCategory("Energy");
	fAlphaEnergyHistogramMinCmd->SetDefaultValue(DEFAULT_ALPHA_ENERGY_MIN / DEFAULT_HIGH_ENERGY_UNIT);
	fAlphaEnergyHistogramMinCmd->SetDefaultUnit(DEFAULT_HIGH_ENERGY_UNIT_STRING);
	
	fAlphaEnergyHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ALPHA_ENERGY_MAX_CMD, this);
	fAlphaEnergyHistogramMaxCmd->SetGuidance("Maximum histogram energy.");
	fAlphaEnergyHistogramMaxCmd->SetUnitCategory("Energy");
	fAlphaEnergyHistogramMaxCmd->SetDefaultValue(DEFAULT_ALPHA_ENERGY_MAX / DEFAULT_HIGH_ENERGY_UNIT);
	fAlphaEnergyHistogramMaxCmd->SetDefaultUnit(DEFAULT_HIGH_ENERGY_UNIT_STRING);
	
	fAlphaThetaHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_ALPHA_THETA_TITLE_CMD, this);
	fAlphaThetaHistogramTitleCmd->SetGuidance("Title of differential cross section histogram.");
	fAlphaThetaHistogramTitleCmd->SetDefaultValue(DEFAULT_ALPHA_THETA_TITLE);
	
	fAlphaThetaHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_ALPHA_THETA_BINS_CMD, this);
	fAlphaThetaHistogramBinsCmd->SetGuidance("Number of bins for differential cross section (scattering angle distribution).");
	fAlphaThetaHistogramBinsCmd->SetDefaultValue(DEFAULT_ALPHA_THETA_BINS);
	
	fAlphaThetaHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ALPHA_THETA_MIN_CMD, this);
	fAlphaThetaHistogramMinCmd->SetGuidance("Minimum histogram theta (scattering angle).");
	fAlphaThetaHistogramMinCmd->SetUnitCategory("Angle");
	fAlphaThetaHistogramMinCmd->SetDefaultValue(DEFAULT_ALPHA_THETA_MIN / DEFAULT_ANGLE_UNIT);
	fAlphaThetaHistogramMinCmd->SetDefaultUnit(DEFAULT_ANGLE_UNIT_STRING);
	
	fAlphaThetaHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_ALPHA_THETA_MAX_CMD, this);
	fAlphaThetaHistogramMaxCmd->SetGuidance("Maximum histogram theta (scattering angle).");
	fAlphaThetaHistogramMaxCmd->SetUnitCategory("Angle");
	fAlphaThetaHistogramMaxCmd->SetDefaultValue(DEFAULT_ALPHA_THETA_MAX / DEFAULT_ANGLE_UNIT);
	fAlphaThetaHistogramMaxCmd->SetDefaultUnit(DEFAULT_ANGLE_UNIT_STRING);

	fDeltasHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_DELTAS_TITLE_CMD, this);
	fDeltasHistogramTitleCmd->SetGuidance("Title of number of deltas.");
	fDeltasHistogramTitleCmd->SetDefaultValue(DEFAULT_DELTAS_TITLE);
	
	fDeltasHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_DELTAS_BINS_CMD, this);
	fDeltasHistogramBinsCmd->SetGuidance("Number of bins for number of deltas.");
	fDeltasHistogramBinsCmd->SetDefaultValue(DEFAULT_DELTAS_BINS);
	
	fDeltasHistogramMinCmd = new G4UIcmdWithAnInteger(ANALYSIS_DELTAS_MIN_CMD, this);
	fDeltasHistogramMinCmd->SetGuidance("Minimum number of deltas.");
	fDeltasHistogramMinCmd->SetDefaultValue(DEFAULT_DELTAS_MIN);
	
	fDeltasHistogramMaxCmd = new G4UIcmdWithAnInteger(ANALYSIS_DELTAS_MAX_CMD, this);
	fDeltasHistogramMaxCmd->SetGuidance("Maximum number of deltas.");
	fDeltasHistogramMaxCmd->SetDefaultValue(DEFAULT_DELTAS_MAX);
	
	fDeltaEnergyHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_DELTA_ENERGY_TITLE_CMD, this);
	fDeltaEnergyHistogramTitleCmd->SetGuidance("Title of energy spectrum histogram.");
	fDeltaEnergyHistogramTitleCmd->SetDefaultValue(DEFAULT_DELTA_ENERGY_TITLE);
	
	fDeltaEnergyHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_DELTA_ENERGY_BINS_CMD, this);
	fDeltaEnergyHistogramBinsCmd->SetGuidance("Number of bins for energy spectrum histogram.");
	fDeltaEnergyHistogramBinsCmd->SetDefaultValue(DEFAULT_DELTA_ENERGY_BINS);
	
	fDeltaEnergyHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_DELTA_ENERGY_MIN_CMD, this);
	fDeltaEnergyHistogramMinCmd->SetGuidance("Minimum histogram energy.");
	fDeltaEnergyHistogramMinCmd->SetUnitCategory("Energy");
	fDeltaEnergyHistogramMinCmd->SetDefaultValue(DEFAULT_DELTA_ENERGY_MIN / DEFAULT_LOW_ENERGY_UNIT);
	fDeltaEnergyHistogramMinCmd->SetDefaultUnit(DEFAULT_LOW_ENERGY_UNIT_STRING);
	
	fDeltaEnergyHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_DELTA_ENERGY_MAX_CMD, this);
	fDeltaEnergyHistogramMaxCmd->SetGuidance("Maximum histogram energy.");
	fDeltaEnergyHistogramMaxCmd->SetUnitCategory("Energy");
	fDeltaEnergyHistogramMaxCmd->SetDefaultValue(DEFAULT_DELTA_ENERGY_MAX / DEFAULT_LOW_ENERGY_UNIT);
	fDeltaEnergyHistogramMaxCmd->SetDefaultUnit(DEFAULT_LOW_ENERGY_UNIT_STRING);
	
	fDeltaThetaHistogramTitleCmd = new G4UIcmdWithAString(ANALYSIS_DELTA_THETA_TITLE_CMD, this);
	fDeltaThetaHistogramTitleCmd->SetGuidance("Title of differential cross section histogram.");
	fDeltaThetaHistogramTitleCmd->SetDefaultValue(DEFAULT_DELTA_THETA_TITLE);
	
	fDeltaThetaHistogramBinsCmd = new G4UIcmdWithAnInteger(ANALYSIS_DELTA_THETA_BINS_CMD, this);
	fDeltaThetaHistogramBinsCmd->SetGuidance("Number of bins for differential cross section (scattering angle distribution).");
	fDeltaThetaHistogramBinsCmd->SetDefaultValue(DEFAULT_DELTA_THETA_BINS);
	
	fDeltaThetaHistogramMinCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_DELTA_THETA_MIN_CMD, this);
	fDeltaThetaHistogramMinCmd->SetGuidance("Minimum histogram theta (scattering angle).");
	fDeltaThetaHistogramMinCmd->SetUnitCategory("Angle");
	fDeltaThetaHistogramMinCmd->SetDefaultValue(DEFAULT_DELTA_THETA_MIN / DEFAULT_ANGLE_UNIT);
	fDeltaThetaHistogramMinCmd->SetDefaultUnit(DEFAULT_ANGLE_UNIT_STRING);
	
	fDeltaThetaHistogramMaxCmd = new G4UIcmdWithADoubleAndUnit(ANALYSIS_DELTA_THETA_MAX_CMD, this);
	fDeltaThetaHistogramMaxCmd->SetGuidance("Maximum histogram theta (scattering angle).");
	fDeltaThetaHistogramMaxCmd->SetUnitCategory("Angle");
	fDeltaThetaHistogramMaxCmd->SetDefaultValue(DEFAULT_DELTA_THETA_MAX / DEFAULT_ANGLE_UNIT);
}

RutherfordAnalysisMessenger::~RutherfordAnalysisMessenger()
{
	delete fDirectory;
	delete fFileOutCmd;
	delete fAlphaEnergyHistogramTitleCmd;
	delete fAlphaEnergyHistogramBinsCmd;
	delete fAlphaEnergyHistogramMinCmd;
	delete fAlphaEnergyHistogramMaxCmd;
	delete fAlphaThetaHistogramTitleCmd;
	delete fAlphaThetaHistogramBinsCmd;
	delete fAlphaThetaHistogramMinCmd;
	delete fAlphaThetaHistogramMaxCmd;
	delete fDeltasHistogramTitleCmd;
	delete fDeltasHistogramBinsCmd;
	delete fDeltasHistogramMinCmd;
	delete fDeltasHistogramMaxCmd;
	delete fDeltaEnergyHistogramTitleCmd;
	delete fDeltaEnergyHistogramBinsCmd;
	delete fDeltaEnergyHistogramMinCmd;
	delete fDeltaEnergyHistogramMaxCmd;
	delete fDeltaThetaHistogramTitleCmd;
	delete fDeltaThetaHistogramBinsCmd;
	delete fDeltaThetaHistogramBinsCmd;
	delete fDeltaThetaHistogramMinCmd;
}

void RutherfordAnalysisMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fFileOutCmd)
	{
		fRunAction->SetFileOut(value);
	}
	else if (cmd == fAlphaEnergyHistogramTitleCmd)
	{
		fRunAction->SetAlphaEnergyHistogramTitle(value);
	}
	else if (cmd == fAlphaEnergyHistogramBinsCmd)
	{
		auto bins = fAlphaEnergyHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetAlphaEnergyHistogramBins(bins);
	}
	else if (cmd == fAlphaEnergyHistogramMinCmd)
	{
		auto min = fAlphaEnergyHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetAlphaEnergyHistogramMin(min);
	}
	else if (cmd == fAlphaEnergyHistogramMaxCmd)
	{
		auto max = fAlphaEnergyHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetAlphaEnergyHistogramMax(max);
	}
	else if (cmd == fAlphaThetaHistogramTitleCmd)
	{
		fRunAction->SetAlphaThetaHistogramTitle(value);
	}
	else if (cmd == fAlphaThetaHistogramBinsCmd)
	{
		auto bins = fAlphaThetaHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetAlphaThetaHistogramBins(bins);
	}
	else if (cmd == fAlphaThetaHistogramMinCmd)
	{
		auto min = fAlphaThetaHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetAlphaThetaHistogramMin(min);
	}
	else if (cmd == fAlphaThetaHistogramMaxCmd)
	{
		auto max = fAlphaThetaHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetAlphaThetaHistogramMax(max);
	}
	else if (cmd == fDeltasHistogramTitleCmd)
	{
		fRunAction->SetDeltasHistogramTitle(value);
	}
	else if (cmd == fDeltasHistogramBinsCmd)
	{
		auto bins = fDeltasHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetDeltasHistogramBins(bins);
	}
	else if (cmd == fDeltasHistogramMinCmd)
	{
		auto min = fDeltasHistogramMinCmd->GetNewIntValue(value);
		fRunAction->SetDeltasHistogramMin(min);
	}
	else if (cmd == fDeltasHistogramMaxCmd)
	{
		auto max = fDeltasHistogramMaxCmd->GetNewIntValue(value);
		fRunAction->SetDeltasHistogramMax(max);
	}
	else if (cmd == fDeltaEnergyHistogramTitleCmd)
	{
		fRunAction->SetDeltaEnergyHistogramTitle(value);
	}
	else if (cmd == fDeltaEnergyHistogramBinsCmd)
	{
		auto bins = fDeltaEnergyHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetDeltaEnergyHistogramBins(bins);
	}
	else if (cmd == fDeltaEnergyHistogramMinCmd)
	{
		auto min = fDeltaEnergyHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetDeltaEnergyHistogramMin(min);
	}
	else if (cmd == fDeltaEnergyHistogramMaxCmd)
	{
		auto max = fDeltaEnergyHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetDeltaEnergyHistogramMax(max);
	}
	else if (cmd == fDeltaThetaHistogramTitleCmd)
	{
		fRunAction->SetDeltaThetaHistogramTitle(value);
	}
	else if (cmd == fDeltaThetaHistogramBinsCmd)
	{
		auto bins = fDeltaThetaHistogramBinsCmd->GetNewIntValue(value);
		fRunAction->SetDeltaThetaHistogramBins(bins);
	}
	else if (cmd == fDeltaThetaHistogramMinCmd)
	{
		auto min = fDeltaThetaHistogramMinCmd->GetNewDoubleValue(value);
		fRunAction->SetDeltaThetaHistogramMin(min);
	}
	else if (cmd == fDeltaThetaHistogramMaxCmd)
	{
		auto max = fDeltaThetaHistogramMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetDeltaThetaHistogramMax(max);
	}
}
