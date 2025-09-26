#include "../include/RutherfordActionInitialization.hh"
#include "../include/RutherfordGeneratorAction.hh"
#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordEventAction.hh"
#include "../include/RutherfordSteppingAction.hh"

void RutherfordActionInitialization::Build() const
{
	SetUserAction(new RutherfordGeneratorAction());
	SetUserAction(new RutherfordRunAction());
	SetUserAction(new RutherfordEventAction());
	SetUserAction(new RutherfordSteppingAction());
}
