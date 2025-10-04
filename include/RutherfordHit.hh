#ifndef HIT_HH
#define HIT_HH

#include <G4VHit.hh>
#include <G4Step.hh>
#include <G4ThreeVector.hh>
#include <G4THitsCollection.hh>

class RutherfordHit : public G4VHit
{
	public:

		RutherfordHit(G4Step*);
		virtual ~RutherfordHit() = default;

		G4int		GetTrackID()        const { return fTrackID;        };
		G4int		GetParentTrackID()  const { return fParentTrackID;  };
		G4int		GetPDGCode()        const { return fPDGCode;        };
		G4int		GetProcessType()    const { return fProcessType;    };
		G4int		GetProcessSubType() const { return fProcessSubType; };
		G4double	GetEnergyDeposit()  const { return fEnergyDeposit;  };
		G4ThreeVector	GetPosition()       const { return fPosition;       };
		G4double	GetTime()           const { return fTime;           };

		G4VProcess*	GetProcess()        const;

	private:

		G4int		fTrackID;
		G4int 		fParentTrackID;
		G4int		fPDGCode;
		G4int		fProcessType;
		G4int		fProcessSubType;
		G4double	fEnergyDeposit;
		G4ThreeVector	fPosition;
		G4double	fTime;	
};

using RutherfordHitsCollection = G4THitsCollection<RutherfordHit>;

#endif
