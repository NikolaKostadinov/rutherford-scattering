#include "../include/RutherfordGeneratorAction.hh"

#include <G4Alpha.hh>
#include <G4SystemOfUnits.hh>

RutherfordGeneratorAction::RutherfordGeneratorAction()
{
	fAlphaEnergy   = DEFAULT_ALPHA_ENERGY;
	fAlphaDistance = DEFAULT_ALPHA_DISTANCE;

	fMessenger 	= new RutherfordGeneratorMessenger(this);
	
	auto particle 	= G4Alpha::AlphaDefinition();
	auto position	= G4ThreeVector(0., 0., -fAlphaDistance);
	auto direction 	= G4ThreeVector(0., 0., +1.);

	fParticleGun 	= new G4ParticleGun(1);
	
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(direction);
	fParticleGun->SetParticleEnergy(fAlphaEnergy);
}

RutherfordGeneratorAction::~RutherfordGeneratorAction()
{
	delete fParticleGun;
	delete fMessenger;
}

void RutherfordGeneratorAction::SetAlphaEnergy(G4double energy)
{
	fAlphaEnergy = energy;
}

void RutherfordGeneratorAction::SetAlphaDistance(G4double distance)
{
	fAlphaDistance = distance;
}

G4double RutherfordGeneratorAction::GetAlphaEnergy() const
{
	return fAlphaEnergy;
}

G4double RutherfordGeneratorAction::GetAlphaDistance() const
{
	return fAlphaDistance;
}
void RutherfordGeneratorAction::GeneratePrimaries(G4Event* event)
{
	fParticleGun->SetParticleEnergy(fAlphaEnergy);
	fParticleGun->GeneratePrimaryVertex(event);
}
