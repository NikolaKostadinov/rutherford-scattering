#include "../include/RutherfordActionInitialization.hh"
#include "../include/RutherfordGeneratorAction.hh"
#include "../include/RutherfordRunAction.hh"
#include "../include/RutherfordSteppingAction.hh"

RutherfordActionInitialization::RutherfordActionInitialization()
{

}

RutherfordActionInitialization::~RutherfordActionInitialization()
{

}

void RutherfordActionInitialization::Build() const
{
	auto generator = new RutherfordGeneratorAction();

	SetUserAction(generator);
	SetUserAction(new RutherfordRunAction());
	SetUserAction(new RutherfordSteppingAction());
}
