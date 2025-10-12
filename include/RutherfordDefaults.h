#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <G4SystemOfUnits.hh>

#define RUTHERFORD_NAME				"Rutherford Scattering"
#define RUTHERFORD_PROGRAM			"rutherford-scattering"
#define RUTHERFORD_VERSION			"v1.0.1-beta"

#define VERSION_FLAG				"--version"
#define HELP_LONG_FLAG				"--help"
#define HELP_SHORT_FLAG				"-h"
#define TAB_SIZE				8
#define MARGIN_SIZE				2
#define BAR_SIZE				40
#define EVENTS_PER_BAR_GLYPH			10

// DEFAULT UNITS
#define DEFAULT_HIGH_ENERGY_UNIT		MeV
#define DEFAULT_HIGH_ENERGY_UNIT_STRING		"MeV"
#define DEFAULT_LOW_ENERGY_UNIT			keV
#define DEFAULT_LOW_ENERGY_UNIT_STRING		"keV"
#define DEFAULT_SHORT_LENGTH_UNIT		um
#define DEFAULT_SHORT_LENGTH_UNIT_STRING	"um"
#define DEFAULT_MID_LENGTH_UNIT			mm
#define DEFAULT_MID_LENGTH_UNIT_STRING		"mm"
#define DEFAULT_LONG_LENGTH_UNIT		cm
#define DEFAULT_LONG_LENGTH_UNIT_STRING		"cm"
#define DEFAULT_ANGLE_UNIT			deg
#define DEFAULT_ANGLE_UNIT_STRING		"deg"
#define DEFAULT_NUMBER_DENSITY_UNIT		1/cm3
#define DEFAULT_NUMBER_DENSITY_UNIT_STRING	"1/cm3"
#define DEFAULT_TEMPERATURE_UNIT		kelvin
#define DEFAULT_TEMPERATURE_UNIT_STRING		"kelvin"

// DEFAULT WORLD MATERIAL (VACUUM)
#define VACUUM					"Rutherford_Vacuum"
#define VACUUM_ATOMIC_NUMBER			1
#define VACUUM_NUMBER_DENSITY			0.06 * 1/cm3

// DEFAULT DETECTOR MATERIAL
#define DETECTOR_MATERIAL			"Rutherford_Detectorium"
#define DEFAULT_DETECTOR_ATOMIC_NUMBER		14
#define DEFAULT_DETECTOR_NUMBER_DENSITY 	6.0e+22 * 1/cm3
#define DEFAULT_DETECTOR_TEMPERATURE		295.0 * kelvin

// DEFAULT DETECTOR GEOMETRY
#define WORLD_NAME				"Manchester"
#define DETECTOR_NAME				"Ruthertector"
#define DEFAULT_WORLD_RADIUS			1.0 *  m
#define DEFAULT_DETECTOR_RADIUS			1.0 * cm
#define DEFAULT_DETECTOR_THICKNESS		1.0 * um

// DEFAULT GENERATED PARTICLE
#define DEFAULT_PRIMARY_PARTICLE		"alpha"
#define DEFAULT_PRIMARY_ENERGY			5.0 * MeV
#define DEFAULT_PRIMARY_DISTANCE		1.0 * cm

// DEFAULT ANALYSIS PARAMETERS
#define DEFAULT_FILE_OUT			"output.root"
#define HITS_COLLECTION_NAME			"RutherfordHitsCollection"
#define HITS_NTUPLE_NAME			"Hits"
#define HITS_NTUPLE_TITLE			"Hits"
#define DEFAULT_MIN_ENERGY_DEPOSIT		10.0 * eV

// RUN
#define DEFAULT_NUMBER_OF_EVENTS		1
#define DEFAULT_NUMBER_OF_THREADS		1

// G4
#define G4Vector				std::vector
#define G4IStringStream				std::istringstream
#define G4GetLine				std::getline
#define G4IOFixed				std::ios::fixed

#endif
