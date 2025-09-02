#include "../include/RutherfordPhysicsList.hh"

#include <G4EmLivermorePhysics.hh>

RutherfordPhysicsList::RutherfordPhysicsList()
{
	RegisterPhysics(new G4EmLivermorePhysics());
}

RutherfordPhysicsList::~RutherfordPhysicsList()
{

}
