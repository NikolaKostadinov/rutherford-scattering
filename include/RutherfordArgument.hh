#ifndef ARGUMENT_HH
#define ARGUMENT_HH

#include <G4UImanager.hh>

class RutherfordArgument
{
	public:
		
		RutherfordArgument(
			G4String longFlag,	// --flag
			G4String shortFlag,	// -f
			G4String command,	// /command
			G4String type,		// [value]
			G4String description	// ...
		);
		~RutherfordArgument() = default;

		G4String	GetLongFlag()		const { return fLongFlag;    };
		G4String	GetShortFlag()		const { return fShortFlag;   };
		G4String	GetCommand()		const { return fCommand;     };
		G4String	GetValue()		const { return fValue;       };
		G4String	GetType()		const { return fType;        };
		G4String	GetDescription()	const { return fDescription; };

		void		SetValue(G4String value)      { fValue = value;      };
		
		void		Execute(G4UImanager*)	const;

	private:

		G4String	fLongFlag;	// --flag
		G4String	fShortFlag;	// -f
		G4String	fCommand;	// /command
		G4String	fValue;
		G4String	fType;		// [value]
		G4String	fDescription;	// ...
};

#endif
