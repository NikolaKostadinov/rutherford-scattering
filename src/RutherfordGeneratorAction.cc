#include "../include/RutherfordGeneratorAction.hh"

#include <Randomize.hh>
#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>

#include <G4GeneralParticleSource.hh>
#include <G4IonTable.hh>

#include "../include/RutherfordDefaults.h"
#include "../include/RutherfordGeneratorType.h"

RutherfordGeneratorAction::RutherfordGeneratorAction()
{
	fMessenger = new RutherfordGeneratorMessenger(this);
}

RutherfordGeneratorAction::~RutherfordGeneratorAction()
{
	delete fPrimaryGenerator;
	delete fMessenger;
}

void RutherfordGeneratorAction::SetParticleGun()
{
	auto* particleGun = new G4ParticleGun(1);

	auto  position  = G4ThreeVector(0.0, 0.0, -fPrimaryDistance);
	auto direction  = G4ThreeVector(0, 0, -1);

	particleGun->SetParticleDefinition(fPrimaryParticleDefinition);
	particleGun->SetParticlePosition(position);
	particleGun->SetParticleMomentumDirection(direction);
	particleGun->SetParticleEnergy(fPrimaryEnergy);

	fPrimaryGenerator = particleGun;
}

void RutherfordGeneratorAction::SetIsotropicSource()
{
	auto* isotropicSource = new G4ParticleGun(1);

	auto  position  = G4ThreeVector(0.0, 0.0, -fPrimaryDistance);

	auto cosTheta = 2 * G4UniformRand() - 1;
	auto sinTheta = sqrt(1 - cosTheta*cosTheta);
	
	auto phi    = 2 * CLHEP::pi * G4UniformRand();
	auto cosPhi = cos(phi);
	auto sinPhi = sin(phi);

	auto direction = G4ThreeVector(
		sinTheta * cosPhi,
		sinTheta * sinPhi,
		cosTheta
	);

	isotropicSource->SetParticleDefinition(fPrimaryParticleDefinition);
	isotropicSource->SetParticlePosition(position);
	isotropicSource->SetParticleMomentumDirection(direction);
	isotropicSource->SetParticleEnergy(fPrimaryEnergy);

	fPrimaryGenerator = isotropicSource;
}

void RutherfordGeneratorAction::SetDecaySource()
{
	auto* decaySource = new G4GeneralParticleSource();

	auto* ion = G4IonTable::GetIonTable()->GetIon(fPrimaryIonAtomicNumber, fPrimaryIonMassNumber, 0.0);

	decaySource->SetParticleDefinition(ion);
	decaySource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0,0,-fPrimaryDistance));
	decaySource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(fPrimaryEnergy);
	decaySource->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

	fPrimaryGenerator = decaySource;
}

void RutherfordGeneratorAction::GeneratePrimaries(G4Event* event)
{
	if      (fPrimaryGeneratorType == PARTICLE_GUN_ID)     SetParticleGun();
	else if (fPrimaryGeneratorType == ISOTROPIC_SOURCE_ID) SetIsotropicSource();
	else if (fPrimaryGeneratorType == DECAY_SOURCE_ID)     SetDecaySource();

	fPrimaryGenerator->GeneratePrimaryVertex(event);
}