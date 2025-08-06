#include "../include/RutherfordGeneratorAction.hh"
#include <G4Alpha.hh>
#include <G4SystemOfUnits.hh>

RutherfordGeneratorAction::RutherfordGeneratorAction() :
	fEnergy(DEFAULT_ENERGY),
	fDistance(DEFAULT_DISTANCE)
{
	fMessenger 	= new RutherfordGeneratorMessenger(this);
	
	auto particle 	= G4Alpha::AlphaDefinition();
	auto position	= G4ThreeVector(0., 0., -fDistance);
	auto direction 	= G4ThreeVector(0., 0., +1.);

	fParticleGun 	= new G4ParticleGun(1);
	
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(direction);
	fParticleGun->SetParticleEnergy(fEnergy);
}

RutherfordGeneratorAction::~RutherfordGeneratorAction()
{
	delete fParticleGun;
	delete fMessenger;
}

void RutherfordGeneratorAction::SetEnergy(G4double energy)
{
	fEnergy = energy;
}

void RutherfordGeneratorAction::SetDistance(G4double distance)
{
	fDistance = distance;
}

void RutherfordGeneratorAction::GeneratePrimaries(G4Event* event)
{
	fParticleGun->SetParticleEnergy(fEnergy);
	fParticleGun->GeneratePrimaryVertex(event);
}
