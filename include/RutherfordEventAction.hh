#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH

#include <G4UserEventAction.hh>

class RutherfordEventAction : public G4UserEventAction
{
	public:

		RutherfordEventAction();
		~RutherfordEventAction();

		void BeginOfEventAction(const G4Event* event) override;
		void   EndOfEventAction(const G4Event* event) override;
};

#endif
