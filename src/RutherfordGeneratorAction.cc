#include "../include/RutherfordGeneratorAction.hh"

#include <G4Alpha.hh>
#include <G4SystemOfUnits.hh>

#include "../include/RutherfordDefaults.h"

RutherfordGeneratorAction::RutherfordGeneratorAction()
{
	fMessenger = new RutherfordGeneratorMessenger(this);
}

RutherfordGeneratorAction::~RutherfordGeneratorAction()
{
	delete fParticleGun;
	delete fMessenger;
}

void RutherfordGeneratorAction::SetParticleGun()
{
	auto* particle  = fPrimaryParticleDefinition;
	auto  position  = G4ThreeVector(0.0, 0.0, -fPrimaryDistance);
	auto  direction = G4ThreeVector(0.0, 0.0, +1.0);

	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(direction);
	fParticleGun->SetParticleEnergy(fPrimaryEnergy);
}

void RutherfordGeneratorAction::GeneratePrimaries(G4Event* event)
{
	SetParticleGun();
	fParticleGun->GeneratePrimaryVertex(event);
}