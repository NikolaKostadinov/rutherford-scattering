#ifndef PRINT_HH
#define PRINT_HH

#include <iomanip>

#include "RutherfordArgument.hh"
#include "RutherfordDefaults.h"

#define DASH		'-'
#define WHITE_SPACE	' '
#define G4WhiteSpace(n)	G4String(n, WHITE_SPACE)
#define G4TabSpace	G4WhiteSpace(TAB_SIZE)

void RutherfordPrintNoArguments();

void RutherfordPrintVersion();

void RutherfordPrintArgumentDescription(
	int longSize, int shortSize, int typeSize,
	const RutherfordArgument& argument
);
void RutherfordPrintVersionArgumentDescription(int longSize, int shortSize, int typeSize);
void RutherfordPrintHelpArgumentDescription(int longSize, int shortSize, int typeSize);
void RutherfordPrintHelp(
	int longSize, int shortSize, int typeSize,
	G4Vector<RutherfordArgument> arguments
);
void RutherfordPrintHelp(G4Vector<RutherfordArgument> arguments);
void RutherfordPrintUnknownFlag(G4String flag);

void RutherfordPrintRunProgressBar(G4int eventNumber, G4int numberOfEvents, G4double elapsedTime);

#endif