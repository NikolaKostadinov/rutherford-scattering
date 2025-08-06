#ifndef PHYSCIS_LIST_HH
#define PHYSICS_LIST_HH

#include <G4VModularPhysicsList.hh>
#include <G4EmStandardPhysics_option4.hh>

class RutherfordPhysicsList : public G4VModularPhysicsList
{
	public:

		RutherfordPhysicsList();
		~RutherfordPhysicsList();
};

#endif
