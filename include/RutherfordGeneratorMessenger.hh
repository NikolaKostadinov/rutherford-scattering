#ifndef GENERATOR_MESSENGER_HH
#define GENERATOR_MESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

#include "RutherfordCommands.h"

class RutherfordGeneratorAction;

class RutherfordGeneratorMessenger : public G4UImessenger
{
	public:

		RutherfordGeneratorMessenger(RutherfordGeneratorAction*);
		virtual ~RutherfordGeneratorMessenger();
	
		void SetNewValue(G4UIcommand*, G4String) override;

	private:
		
		G4UIdirectory*			fDirectory = new G4UIdirectory(GENERATOR_CMD);
		
		G4UIcmdWithAString*		fPrimaryParticleDefinitionCmd = new G4UIcmdWithAString(       GENERATOR_PRIMARY_PARTICLE_CMD,          this);
		G4UIcmdWithAnInteger*		fPrimaryIonAtomicNumberCmd    = new G4UIcmdWithAnInteger(     GENERATOR_PRIMARY_ION_ATOMIC_NUMBER_CMD, this);
		G4UIcmdWithAnInteger*		fPrimaryIonMassNumberCmd      = new G4UIcmdWithAnInteger(     GENERATOR_PRIMARY_ION_MASS_NUMBER_CMD,   this);
		G4UIcmdWithADoubleAndUnit*	fPrimaryEnergyCmd             = new G4UIcmdWithADoubleAndUnit(GENERATOR_PRIMARY_ENERGY_CMD,            this);
		G4UIcmdWithADoubleAndUnit*	fPrimaryDistanceCmd           = new G4UIcmdWithADoubleAndUnit(GENERATOR_PRIMARY_DISTANCE_CMD,          this);
		G4UIcmdWithAString*		fPrimaryGeneratorTypeCmd      = new G4UIcmdWithAString(       GENERATOR_TYPE_CMD,                      this);

		RutherfordGeneratorAction*	fGenerator;
};

#endif
