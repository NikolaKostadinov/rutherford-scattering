#ifndef GENERATOR_ACTION_HH
#define GENERATOR_ACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

#include "RutherfordDefaults.h"
#include "RutherfordGeneratorMessenger.hh"

class RutherfordGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:

		RutherfordGeneratorAction();
		virtual ~RutherfordGeneratorAction();
		
		void SetEnergy(G4double);
		void SetDistance(G4double);

		G4double GetEnergy() const;

		virtual void GeneratePrimaries(G4Event*) override;

	private:

		G4double			fEnergy;
		G4double			fDistance;
		
		G4ParticleGun*			fParticleGun;
		
		RutherfordGeneratorMessenger*	fMessenger;
};

#endif

