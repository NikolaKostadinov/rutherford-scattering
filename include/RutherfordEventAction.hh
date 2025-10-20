#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH

#include <G4UserEventAction.hh>

class RutherfordEventAction : public G4UserEventAction
{
	public:

		RutherfordEventAction()          = default;
		virtual ~RutherfordEventAction() = default;
		
		void BeginOfEventAction(const G4Event*) override;
		void   EndOfEventAction(const G4Event*) override;
};

#endif
