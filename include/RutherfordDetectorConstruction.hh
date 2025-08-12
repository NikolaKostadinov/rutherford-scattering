#ifndef	DETECTOR_CONTRUCTION_HH
#define	DETECTOR_CONTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

#include "RutherfordGeometryMessenger.hh"
#include "RutherfordDefaults.h"

class RutherfordDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		
		RutherfordDetectorConstruction();
		~RutherfordDetectorConstruction();
		
		void	SetFoilThickness(G4double);
		void	SetFoilRadius(G4double);
		void	SetWorldRadius(G4double);

		virtual	G4VPhysicalVolume* Construct() override;		
	
	private:
		
		G4double			fFoilThickness;
		G4double			fFoilRadius;
		G4double			fWorldRadius;
		
		RutherfordGeometryMessenger*	fMessenger;
};

#endif
