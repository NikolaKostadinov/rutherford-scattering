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
		
		void SetWorldRadius(G4double);
		void SetDetectorAtomicNumber(G4int);
		void SetDetectorNumberDensity(G4double);
		void SetDetectorRadius(G4double);
		void SetDetectorThickness(G4double);
		
		G4double GetDetectorThickness() const;

		virtual G4VPhysicalVolume* Construct() override;		
	
	private:
		
		G4double			fWorldRadius;
		G4int				fDetectorAtomicNumber;
		G4double			fDetectorNumberDensity;
		G4double			fDetectorRadius;
		G4double			fDetectorThickness;
		
		RutherfordGeometryMessenger*	fMessenger;
};

#endif
