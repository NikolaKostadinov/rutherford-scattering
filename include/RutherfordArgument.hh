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
		~RutherfordArgument();

		G4String	GetLongFlag()                   const;
		G4String	GetShortFlag()                  const;
		G4String	GetType()                       const;
		void		SetValue(G4String);
		void		PrintDescription(int, int, int) const;
		void		Execute(G4UImanager*)           const;

	private:

		G4String	fLongFlag;	// --flag
		G4String	fShortFlag;	// -f
		G4String	fCommand;	// /command
		G4String	fValue;
		G4String	fType;		// [value]
		G4String	fDescription;	// ...
};

#endif
