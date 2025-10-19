#include "../include/RutherfordPhysicsList.hh"

#include <G4EmStandardPhysics_option4.hh>
#include <G4DecayPhysics.hh>
#include <G4HadronPhysicsQGSP_BIC.hh>
#include <G4SystemOfUnits.hh>

RutherfordPhysicsList::RutherfordPhysicsList()
{
	RegisterPhysics(new G4EmStandardPhysics_option4());
	RegisterPhysics(new G4DecayPhysics());
	RegisterPhysics(new G4HadronPhysicsQGSP_BIC());
}

void RutherfordPhysicsList::SetCuts()
{
	auto cut = 1.0 * um;

	SetDefaultCutValue(cut);
	
	SetCutValue(cut, "gamma");
	SetCutValue(cut, "e-");
	SetCutValue(cut, "e+");
	
	G4VUserPhysicsList::SetCuts();
}
