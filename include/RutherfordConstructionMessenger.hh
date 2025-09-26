#ifndef GEOMETRY_MESSENGER_HH
#define GEOMETRY_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "RutherfordCommands.h"

class RutherfordDetectorConstruction;

class RutherfordConstructionMessenger : public G4UImessenger
{
	public:

		RutherfordConstructionMessenger(RutherfordDetectorConstruction*);
		virtual ~RutherfordConstructionMessenger();
		
		void SetNewValue(G4UIcommand*, G4String) override;
	
	private:

		G4UIdirectory*			fDirectory                = new G4UIdirectory(CONSTRUCTION_CMD);
		
		G4UIcmdWithADoubleAndUnit*	fWorldRadiusCmd           = new G4UIcmdWithADoubleAndUnit(WORLD_RADIUS_CMD, this);

		G4UIcmdWithAnInteger*		fDetectorAtomicNumberCmd  = new G4UIcmdWithAnInteger(DETECTOR_ATOMIC_NUMBER_CMD, this);
		G4UIcmdWithADoubleAndUnit*	fDetectorNumberDensityCmd = new G4UIcmdWithADoubleAndUnit(DETECTOR_NUMBER_DENSITY_CMD, this);
		G4UIcmdWithADoubleAndUnit*	fDetectorTemperatureCmd   = new G4UIcmdWithADoubleAndUnit(DETECTOR_TEMPERATURE_CMD, this);
		G4UIcmdWithADoubleAndUnit*	fDetectorRadiusCmd        = new G4UIcmdWithADoubleAndUnit(DETECTOR_RADIUS_CMD, this);
		G4UIcmdWithADoubleAndUnit*	fDetectorThicknessCmd     = new G4UIcmdWithADoubleAndUnit(DETECTOR_THICKNESS_CMD, this);
		
		RutherfordDetectorConstruction*	fDetectorConstruction;
};

#endif
