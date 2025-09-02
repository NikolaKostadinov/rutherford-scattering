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
		
		void SetAlphaEnergy(G4double);
		void SetAlphaDistance(G4double);

		G4double GetAlphaEnergy() const;
		G4double GetAlphaDistance() const;

		virtual void GeneratePrimaries(G4Event*) override;

	private:

		G4double			fAlphaEnergy;
		G4double			fAlphaDistance;
		
		G4ParticleGun*			fParticleGun;
		
		RutherfordGeneratorMessenger*	fMessenger;
};

#endif

