#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include <G4VUserActionInitialization.hh>

// Forward declarations
class RutherfordGeneratorAction;
class RutherfordRunAction;
class RutherfordSteppingAction;

class RutherfordActionInitialization : public G4VUserActionInitialization
{
	public:
	
		RutherfordActionInitialization();
		virtual ~RutherfordActionInitialization();
		
		virtual void Build() const override;
};

#endif
