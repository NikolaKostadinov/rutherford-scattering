#include "../include/RutherfordAnalysisMessenger.hh"
#include "../include/RutherfordRunAction.hh"

RutherfordAnalysisMessenger::RutherfordAnalysisMessenger(RutherfordRunAction* runAction) : fRunAction(runAction)
{
	fDirectory = new G4UIdirectory("/analysis/");
	fDirectory->SetGuidance("Commands for simulation analysis. This includes (only) ROOT histogram setup.");

	fFileOutCmd = new G4UIcmdWithAString("/analysis/file", this);
	fFileOutCmd->SetGuidance("Path to analysis file.");
	fFileOutCmd->SetDefaultValue(DEFAULT_FILE_OUT);
	
	fETitleCmd = new G4UIcmdWithAString("/analysis/energy/title", this);
	fETitleCmd->SetGuidance("Title of energy spectrum histogram.");
	fETitleCmd->SetDefaultValue(DEFAULT_ENERGY_TITLE);
	
	fEBinsCmd = new G4UIcmdWithAnInteger("/analysis/energy/bins", this);
	fEBinsCmd->SetGuidance("Number of bins for energy spectrum histogram.");
	fEBinsCmd->SetDefaultValue(DEFAULT_ENERGY_BINS);
	
	fEMinCmd = new G4UIcmdWithADoubleAndUnit("/analysis/energy/min", this);
	fEMinCmd->SetGuidance("Minimum histogram energy.");
	fEMinCmd->SetUnitCategory("Energy");
	fEMinCmd->SetDefaultValue(DEFAULT_ENERGY_MIN / MeV);
	fEMinCmd->SetDefaultUnit("MeV");
	
	fEMaxCmd = new G4UIcmdWithADoubleAndUnit("/analysis/energy/max", this);
	fEMaxCmd->SetGuidance("Maximum histogram energy.");
	fEMaxCmd->SetUnitCategory("Energy");
	fEMaxCmd->SetDefaultValue(DEFAULT_ENERGY_MAX / MeV);
	fEMaxCmd->SetDefaultUnit("MeV");
	
	fThetaTitleCmd = new G4UIcmdWithAString("/analysis/theta/title", this);
	fThetaTitleCmd->SetGuidance("Title of differential cross section histogram.");
	fThetaTitleCmd->SetDefaultValue(DEFAULT_THETA_TITLE);
	
	fThetaBinsCmd = new G4UIcmdWithAnInteger("/analysis/theta/bins", this);
	fThetaBinsCmd->SetGuidance("Number of bins for differential cross section (scattering angle distribution).");
	fThetaBinsCmd->SetDefaultValue(DEFAULT_THETA_BINS);
	
	fThetaMinCmd = new G4UIcmdWithADoubleAndUnit("/analysis/theta/min", this);
	fThetaMinCmd->SetGuidance("Minimum histogram theta (scattering angle).");
	fThetaMinCmd->SetUnitCategory("Angle");
	fThetaMinCmd->SetDefaultValue(DEFAULT_THETA_MIN / deg);
	fThetaMinCmd->SetDefaultUnit("deg");
	
	fThetaMaxCmd = new G4UIcmdWithADoubleAndUnit("/analysis/theta/max", this);
	fThetaMaxCmd->SetGuidance("Maximum histogram theta (scattering angle).");
	fThetaMaxCmd->SetUnitCategory("Angle");
	fThetaMaxCmd->SetDefaultValue(DEFAULT_THETA_MAX / deg);
	fThetaMaxCmd->SetDefaultUnit("deg");
}

RutherfordAnalysisMessenger::~RutherfordAnalysisMessenger()
{
	delete fDirectory;
	delete fFileOutCmd;
	delete fETitleCmd;
	delete fEBinsCmd;
	delete fEMinCmd;
	delete fEMaxCmd;
	delete fThetaTitleCmd;
	delete fThetaBinsCmd;
	delete fThetaMinCmd;
	delete fThetaMaxCmd;
}

void RutherfordAnalysisMessenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
	if (cmd == fFileOutCmd)
	{
		fRunAction->SetFileOut(value);
	}
	else if (cmd == fETitleCmd)
	{
		fRunAction->SetETitle(value);
	}
	else if (cmd == fEBinsCmd)
	{
		auto bins = fEBinsCmd->GetNewIntValue(value);
		fRunAction->SetEBins(bins);
	}
	else if (cmd == fEMinCmd)
	{
		auto min = fEMinCmd->GetNewDoubleValue(value);
		fRunAction->SetEMin(min);
	}
	else if (cmd == fEMaxCmd)
	{
		auto max = fEMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetEMax(max);
	}
	else if (cmd == fThetaTitleCmd)
	{
		fRunAction->SetThetaTitle(value);
	}
	else if (cmd == fThetaBinsCmd)
	{
		auto bins = fThetaBinsCmd->GetNewIntValue(value);
		fRunAction->SetThetaBins(bins);
	}
	else if (cmd == fThetaMinCmd)
	{
		auto min = fThetaMinCmd->GetNewDoubleValue(value);
		fRunAction->SetThetaMin(min);
	}
	else if (cmd == fThetaMaxCmd)
	{
		auto max = fThetaMaxCmd->GetNewDoubleValue(value);
		fRunAction->SetThetaMax(max);
	}
}
