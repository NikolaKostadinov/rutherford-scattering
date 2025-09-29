#ifndef SENSITIVE_DETECTOR_HH
#define SENSITIVE_DETECTOR_HH

#include <G4VSensitiveDetector.hh>

#include "RutherfordHit.hh"

class RutherfordSensitiveDetector : public G4VSensitiveDetector
{
	public:
		RutherfordSensitiveDetector(const G4String&, const G4String&);
		virtual ~RutherfordSensitiveDetector() = default;

		void   Initialize(G4HCofThisEvent*)              override;
		G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
	
	private:

		G4int				fHitsCollectionID;
		RutherfordHitsCollection*	fHitsCollection;
};

#endif
