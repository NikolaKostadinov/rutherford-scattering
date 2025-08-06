#include <iostream>
#include <ctime>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <Randomize.hh>

#include "include/RutherfordPhysicsList.hh"
#include "include/RutherfordDetectorConstruction.hh"
#include "include/RutherfordActionInitialization.hh"

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheSeed(time(NULL));

        auto runManager = new G4RunManager();

	runManager->SetUserInitialization(new RutherfordPhysicsList());
	runManager->SetUserInitialization(new RutherfordDetectorConstruction());
	runManager->SetUserInitialization(new RutherfordActionInitialization());
	
	G4UImanager* uiManager = G4UImanager::GetUIpointer();
	//
	uiManager->ApplyCommand("/control/execute run.mac");
	//

	delete runManager;
	delete uiManager;
        return 0;
}
