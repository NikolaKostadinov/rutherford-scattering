#include "../include/RutherfordPrint.hh"

#include "G4UnitsTable.hh"

void RutherfordPrintNoArguments()
{
	G4cout << G4endl;
	
	G4cout << "Please provide inline arguments." << G4endl;
	
	G4cout << "For help use the `--help` flag." << G4endl;
	
	G4cout << G4endl;
}

void RutherfordPrintVersion()
{
	G4cout << RUTHERFORD_PROGRAM;
	G4cout << DASH;
	G4cout << RUTHERFORD_VERSION;
	G4cout << G4endl;

	G4cout << G4endl;
}

void RutherfordPrintArgumentDescription(int longSize, int shortSize, int typeSize, const RutherfordArgument& argument)
{
	// --flag / -f [type] description
	G4cout << argument.GetLongFlag();
	G4cout << G4WhiteSpace((longSize + MARGIN_SIZE) - argument.GetLongFlag().size());
	G4cout << "/";
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	G4cout << argument.GetShortFlag();
	G4cout << G4WhiteSpace((shortSize + MARGIN_SIZE) - argument.GetShortFlag().size());
	G4cout << "[" << argument.GetType() << "]";
	G4cout << G4WhiteSpace((typeSize + MARGIN_SIZE) - argument.GetType().size());
	G4cout << argument.GetDescription();
	G4cout << G4endl;
}

void RutherfordPrintVersionArgumentDescription(int longSize, int shortSize, int typeSize)
{
	// --version description
	G4cout << VERSION_FLAG;
	G4cout << G4WhiteSpace((longSize + MARGIN_SIZE + 1 + MARGIN_SIZE + shortSize + MARGIN_SIZE + 1 + typeSize + 1 + MARGIN_SIZE) - (sizeof(VERSION_FLAG) - 1));
	G4cout << "version of `" << RUTHERFORD_PROGRAM << "`";
	G4cout << G4endl;
}

void RutherfordPrintHelpArgumentDescription(int longSize, int shortSize, int typeSize)
{
	// --help / -h description
	G4cout << HELP_LONG_FLAG;
	G4cout << G4WhiteSpace((longSize + MARGIN_SIZE) - (sizeof(HELP_LONG_FLAG) - 1));
	G4cout << "/";
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	G4cout << HELP_SHORT_FLAG;
	G4cout << G4WhiteSpace((shortSize + MARGIN_SIZE + 1 + typeSize + 1 + MARGIN_SIZE) - (sizeof(HELP_SHORT_FLAG) - 1));
	G4cout << "help (this is help)"; // <--- = HELP_DESCRIPTION
	G4cout << G4endl;
}

void RutherfordPrintHelp(int longSize, int shortSize, int typeSize, G4Vector<RutherfordArgument> arguments)
{
	// rutherford-scattering [options]
	G4cout << RUTHERFORD_PROGRAM;
	G4cout << G4String((TAB_SIZE + longSize + MARGIN_SIZE + 1 + MARGIN_SIZE + shortSize + MARGIN_SIZE) - (sizeof(RUTHERFORD_PROGRAM) - 1), ' ');
	G4cout << "[options]";
	G4cout << G4endl;

	G4cout << G4endl;

	// --version
	G4cout << G4TabSpace;
	RutherfordPrintVersionArgumentDescription(longSize, shortSize, typeSize);

	// --help / -h
	G4cout << G4TabSpace;
	RutherfordPrintHelpArgumentDescription(longSize, shortSize, typeSize);

	// --flag / -f [type] description
	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
	{
		G4cout << G4TabSpace;
		RutherfordPrintArgumentDescription(longSize, shortSize, typeSize, *argument);
	}

	G4cout << G4endl;
}

void RutherfordPrintHelp(G4Vector<RutherfordArgument> arguments)
{
	int longSize  = 0;
	int shortSize = 0;
	int typeSize  = 0;
	for (auto argument = arguments.begin(); argument != arguments.end(); ++argument)
	{
		int thisLongSize  = argument->GetLongFlag().size();
		int thisShortSize = argument->GetShortFlag().size();
		int thisTypeSize  = argument->GetType().size();

		if (longSize  < thisLongSize ) longSize  = thisLongSize;
		if (shortSize < thisShortSize) shortSize = thisShortSize;
		if (typeSize  < thisTypeSize ) typeSize  = thisTypeSize;
	}

	RutherfordPrintHelp(longSize, shortSize, typeSize, arguments);
}

void RutherfordPrintUnknownFlag(G4String flag)
{
	G4cout << "[WARNING] UNKNOWN FLAG: " << flag << G4endl;
}

void RutherfordPrintRunProgressBar(G4int eventNumber, G4int numberOfEvents, G4double elapsedTime)
{
	auto progress = (G4double) eventNumber / (G4double) numberOfEvents;

	auto remainingTime = (1.0-progress)/progress * elapsedTime;
	
	auto eventFrequency = eventNumber / elapsedTime;
	
	auto ERTMinuteComponent = int(elapsedTime  /s) / 60;	// ERT = Elapsed Running Time
	auto ERTSecondComponent = int(elapsedTime  /s) % 60;
	auto ETAMinuteComponent = int(remainingTime/s) / 60;	// ETA = Estimated Time of Arrival
	auto ETASecondComponent = int(remainingTime/s) % 60;

	G4cout << '\r';

	G4cout << "[*";
	int position = progress * BAR_SIZE;
	for (int i = 0; i < BAR_SIZE; ++i)
	{
		if      (i <  position) G4cout << '-';
		else if (i == position) G4cout << '>';
		else                    G4cout << ' ';
	}	
	G4cout << "*]";
	G4cout << G4WhiteSpace(MARGIN_SIZE);

	G4cout << eventNumber << "/" << numberOfEvents << " events";
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	
	G4cout << "[ " << int(progress * 100.0) << "%]";
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	
	G4cout << "ERT ";
	G4cout << ERTMinuteComponent;
	G4cout << "min ";
	G4cout << ERTSecondComponent;
	G4cout << "s";
	G4cout << G4WhiteSpace(MARGIN_SIZE);

	G4cout << "ETA ";
	G4cout << ETAMinuteComponent;
	G4cout << "min ";
	G4cout << ETASecondComponent;
	G4cout << "s";
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	
	G4cout.precision(1);
	G4cout.setf(G4IOFixed);
	G4cout << "ER " << G4BestUnit(eventFrequency, "Frequency");
	G4cout << G4WhiteSpace(MARGIN_SIZE);
	
	G4cout.flush();
	
	if (progress >= 1.0)
		G4cout << G4endl;
}