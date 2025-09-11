#ifndef	DETECTOR_CONTRUCTION_HH
#define	DETECTOR_CONTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Material.hh>

#include "RutherfordGeometryMessenger.hh"

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
		
		G4int		GetDetectorAtomicNumber()    const;
		G4double	GetDetectorNumberDensity()   const;
		G4double	GetDetectorElectronDensity() const;
		G4double	GetDetectorRadius()          const;
		G4double	GetDetectorThickness()       const;
		G4Material*	GetWorldMaterial()           const;
		G4Material*	GetDetectorMaterial()        const;
		G4double	GetDetectorMeanExcitation()  const;

		virtual G4VPhysicalVolume* Construct() override;
	
	private:
		
		G4double			fWorldRadius;
		G4int				fDetectorAtomicNumber;
		G4double			fDetectorNumberDensity;
		G4double			fDetectorRadius;
		G4double			fDetectorThickness;

		G4Material*			fWorldMaterial;
		G4Material*			fDetectorMaterial;

		RutherfordGeometryMessenger*	fMessenger;
};

#endif
