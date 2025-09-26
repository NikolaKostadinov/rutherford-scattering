#ifndef ARGUMENT_PARSER_HH
#define ARGUMENT_PARSER_HH

#include <vector>

#include <G4UImanager.hh>

#include "RutherfordArgument.hh"

void RutherfordArgumentParser(
	int argc, char** argv,
	std::vector<RutherfordArgument>,
	G4UImanager*
);

#endif
