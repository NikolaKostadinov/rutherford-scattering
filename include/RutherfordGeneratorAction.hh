#ifndef GENERATOR_ACTION_HH
#define GENERATOR_ACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4VPrimaryGenerator.hh>
#include <G4ParticleTable.hh>

#include "RutherfordDefaults.h"
#include "RutherfordGeneratorType.h"
#include "RutherfordGeneratorMessenger.hh"

#define PARTICLE_DEFINITION(name) G4ParticleTable::GetParticleTable()->FindParticle(name)

class RutherfordGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:

		RutherfordGeneratorAction();
		virtual ~RutherfordGeneratorAction();
		
		void SetPrimaryParticleDefinition(G4ParticleDefinition* value) { fPrimaryParticleDefinition = value;                      };
		void SetPrimaryParticleDefinition(G4String value)              { fPrimaryParticleDefinition = PARTICLE_DEFINITION(value); };
		void SetPrimaryIonAtomicNumber(G4int value)                    { fPrimaryIonAtomicNumber    = value;                      };
		void SetPrimaryIonMassNumber(G4int value)                      { fPrimaryIonMassNumber      = value;                      };
		void SetPrimaryEnergy(G4double value)                          { fPrimaryEnergy             = value;                      };
		void SetPrimaryDistance(G4double value)                        { fPrimaryDistance           = value;                      };
		void SetPrimaryGeneratorType(G4int value)                      { fPrimaryGeneratorType      = value;                      };
		void SetPrimaryGeneratorType(G4String value)                   { fPrimaryGeneratorType      = TYPE_ID(value);             };
		
		void SetParticleGun();
		void SetIsotropicSource();
		void SetDecaySource();

		G4ParticleDefinition* GetPrimaryParticleDefinition() const     { return fPrimaryParticleDefinition; };
		G4double              GetPrimaryEnergy()             const     { return fPrimaryEnergy;             };
		G4double              GetPrimaryDistance()           const     { return fPrimaryDistance;           };

		virtual void GeneratePrimaries(G4Event*) override;

	private:

		G4ParticleDefinition*		fPrimaryParticleDefinition = PARTICLE_DEFINITION(DEFAULT_PRIMARY_PARTICLE);
		G4int				fPrimaryIonAtomicNumber    = DEFAULT_PRIMARY_ION_ATOMIC_NUMBER;
		G4int 				fPrimaryIonMassNumber      = DEFAULT_PRIMARY_ION_MASS_NUMBER;
		G4double			fPrimaryEnergy             = DEFAULT_PRIMARY_ENERGY;
		G4double			fPrimaryDistance           = DEFAULT_PRIMARY_DISTANCE;
		G4int                           fPrimaryGeneratorType      = DEFAULT_PRIMARY_GENERATOR_TYPE;
		
		G4VPrimaryGenerator*		fPrimaryGenerator;
		
		RutherfordGeneratorMessenger*	fMessenger;
};

#endif
