#ifndef GENERATOR_ACTION_HH
#define GENERATOR_ACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>

#include "RutherfordDefaults.h"
#include "RutherfordGeneratorMessenger.hh"

#define PARTICLE_DEFINITION(name) G4ParticleTable::GetParticleTable()->FindParticle(name)

class RutherfordGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:

		RutherfordGeneratorAction();
		virtual ~RutherfordGeneratorAction();
		
		void SetPrimaryParticleDefinition(G4ParticleDefinition* value) { fPrimaryParticleDefinition = value;                         };
		void SetPrimaryParticleDefinition(G4String value)              { fPrimaryParticleDefinition = PARTICLE_DEFINITION(value); };
		void SetPrimaryEnergy(G4double value)                          { fPrimaryEnergy             = value;                         };
		void SetPrimaryDistance(G4double value)                        { fPrimaryDistance           = value;                         };
		void SetParticleGun();

		G4ParticleDefinition* GetPrimaryParticleDefinition() const     { return fPrimaryParticleDefinition; };
		G4double              GetPrimaryEnergy()             const     { return fPrimaryEnergy;             };
		G4double              GetPrimaryDistance()           const     { return fPrimaryDistance;           };

		virtual void GeneratePrimaries(G4Event*) override;

	private:

		G4ParticleDefinition*		fPrimaryParticleDefinition = PARTICLE_DEFINITION(DEFAULT_PRIMARY_PARTICLE);
		G4double			fPrimaryEnergy             = DEFAULT_PRIMARY_ENERGY;
		G4double			fPrimaryDistance           = DEFAULT_PRIMARY_DISTANCE;
		
		G4ParticleGun*			fParticleGun               = new G4ParticleGun(1);
		
		RutherfordGeneratorMessenger*	fMessenger;
};

#endif
