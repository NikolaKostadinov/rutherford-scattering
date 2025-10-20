#ifndef	DETECTOR_CONTRUCTION_HH
#define	DETECTOR_CONTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Material.hh>

#include "RutherfordConstructionMessenger.hh"
#include "RutherfordDefaults.h"

class RutherfordDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		
		RutherfordDetectorConstruction();
		virtual ~RutherfordDetectorConstruction();
		
		void SetWorldRadius(G4double value)                 { fWorldRadius           = value; };
		void SetDetectorAtomicNumber(G4int value)           { fDetectorAtomicNumber  = value; };
		void SetDetectorNumberDensity(G4double value)       { fDetectorNumberDensity = value; };
		void SetDetectorTemperature(G4double value)         { fDetectorTemperature   = value; };
		void SetDetectorRadius(G4double value)              { fDetectorRadius        = value; };
		void SetDetectorThickness(G4double value)           { fDetectorThickness     = value; };
		void SetDetectorDeadLayer(G4double value)           { fDetectorDeadLayer     = value; };
		void SetWorldMaterial();
		void SetDetectorMaterial();

		G4int       GetDetectorAtomicNumber()         const { return fDetectorAtomicNumber;   };
		G4double    GetDetectorNumberDensity()        const { return fDetectorNumberDensity;  };
		G4double    GetDetectorTemperature()          const { return fDetectorTemperature;    };
		G4double    GetDetectorRadius()               const { return fDetectorRadius;         };
		G4double    GetDetectorThickness()            const { return fDetectorThickness;      };
		G4double    GetDetectorDeadLayer()            const { return fDetectorDeadLayer;      };
		G4Material* GetWorldMaterial()                const { return fWorldMaterial;          };
		G4Material* GetDetectorMaterial()             const { return fDetectorMaterial;       };
		G4double    GetDetectorElectronDensity()      const ;
		G4double    GetDetectorIntegratedLuminosity() const ;
		G4double    GetDetectorMeanExcitationEnergy() const ;

		virtual G4VPhysicalVolume* Construct()           override;
		virtual void               ConstructSDandField() override;
	
	private:
		
		G4double				fWorldRadius           = DEFAULT_WORLD_RADIUS;

		G4int					fDetectorAtomicNumber  = DEFAULT_DETECTOR_ATOMIC_NUMBER;
		G4double				fDetectorNumberDensity = DEFAULT_DETECTOR_NUMBER_DENSITY;
		G4double				fDetectorTemperature   = DEFAULT_DETECTOR_TEMPERATURE;
		G4double				fDetectorRadius        = DEFAULT_DETECTOR_RADIUS;
		G4double				fDetectorThickness     = DEFAULT_DETECTOR_THICKNESS;
		G4double				fDetectorDeadLayer     = DEFAULT_DETECTOR_DEAD_LAYER;

		G4Material*				fWorldMaterial;
		G4Material*				fDetectorMaterial;

		RutherfordConstructionMessenger*	fMessenger;
};

#endif
