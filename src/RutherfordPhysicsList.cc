#include "../include/RutherfordPhysicsList.hh"

#include <G4EmLivermorePhysics.hh>
#include <G4SystemOfUnits.hh>

RutherfordPhysicsList::RutherfordPhysicsList()
{
	RegisterPhysics(new G4EmLivermorePhysics());
}

void RutherfordPhysicsList::SetCuts()
{
	auto cut = 10 * fermi;

	SetDefaultCutValue(cut);
	
	SetCutValue(cut, "gamma");
	SetCutValue(cut, "e-");
	SetCutValue(cut, "e+");
	
	G4VUserPhysicsList::SetCuts();
}
