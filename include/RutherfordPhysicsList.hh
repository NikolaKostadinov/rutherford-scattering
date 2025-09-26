#ifndef PHYSCIS_LIST_HH
#define PHYSICS_LIST_HH

#include <G4VModularPhysicsList.hh>

class RutherfordPhysicsList : public G4VModularPhysicsList
{
	public:

		RutherfordPhysicsList();
		virtual ~RutherfordPhysicsList() = default;

		virtual void SetCuts() override;
};

#endif
