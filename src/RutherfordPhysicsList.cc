#include "../include/RutherfordPhysicsList.hh"

RutherfordPhysicsList::RutherfordPhysicsList()
{
	RegisterPhysics(new G4EmStandardPhysics_option4());
}

RutherfordPhysicsList::~RutherfordPhysicsList()
{

}
