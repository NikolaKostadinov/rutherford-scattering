#ifndef GEOMETRY_MESSENGER_HH
#define GEOMETRY_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "RutherfordDefaults.h"

class RutherfordDetectorConstruction;

class RutherfordGeometryMessenger : public G4UImessenger
{
	public:

		RutherfordGeometryMessenger(RutherfordDetectorConstruction*);
		~RutherfordGeometryMessenger();
		
		void SetNewValue(G4UIcommand*, G4String) override;
	
	private:

		G4UIdirectory*			fDirectory;
		
		G4UIcmdWithADoubleAndUnit* 	fWorldRadiusCmd;
		G4UIcmdWithADoubleAndUnit* 	fFoilRadiusCmd;
		G4UIcmdWithADoubleAndUnit* 	fFoilThicknessCmd;
		
		RutherfordDetectorConstruction* fDetectorConstruction;


};

#endif
