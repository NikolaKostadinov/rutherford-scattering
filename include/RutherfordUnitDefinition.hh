#ifndef UNIT_DEFINITION_HH
#define UNIT_DEFINITION_HH

#include <G4UnitsTable.hh>
#include <G4SystemOfUnits.hh>

void RutherfordUnitDefinition()
{
	new G4UnitDefinition("per cm3", "1/cm3", "NumberDensity", 1/cm3);
	new G4UnitDefinition("per m3",  "1/m3",  "NumberDensity", 1/m3);
}

#endif
