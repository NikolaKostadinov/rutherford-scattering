#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include <G4VUserActionInitialization.hh>

class RutherfordActionInitialization : public G4VUserActionInitialization
{
	public:
	
		RutherfordActionInitialization()          = default;
		virtual ~RutherfordActionInitialization() = default;
		
		virtual void Build() const override;
};

#endif
