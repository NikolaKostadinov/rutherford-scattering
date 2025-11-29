#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <G4SystemOfUnits.hh>

// PROGRAM
#define RUTHERFORD_NAME				"Rutherford Scattering"
#define RUTHERFORD_PROGRAM			"rutherford-scattering"
#define RUTHERFORD_VERSION			"v1.1.0-beta"

// DEFAULT CLI
#define VERSION_FLAG				"--version"
#define HELP_LONG_FLAG				"--help"
#define HELP_SHORT_FLAG				"-h"
#define TAB_SIZE				8
#define MARGIN_SIZE				2
#define BAR_SIZE				40
#define EVENTS_PER_BAR_GLYPH			10

// DEFAULT UNITS
#define UNIT_LIST				\
	X(HIGH_ENERGY_UNIT,	MeV)		\
	X(LOW_ENERGY_UNIT,	keV)		\
	X(SHORT_LENGTH_UNIT,	um)		\
	X(MID_LENGTH_UNIT,	mm)		\
	X(LONG_LENGTH_UNIT,	cm)		\
	X(ANGLE_UNIT,		deg)		\
	X(TEMPERATURE_UNIT,	kelvin)		\
	X(NUMBER_DENSITY_UNIT,	1/cm3)

#define X(unitName, unitValue)						\
	static constexpr const char*  unitName ## _STR = #unitValue;	\
	static constexpr const double unitName ## _VAL =  unitValue;
	
	UNIT_LIST
#undef X


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
#define DETECTOR_SENSITIVE_LAYER_NAME		"Ruthertector"
#define DETECTOR_DEAD_LAYER_NAME		"Rutherdead"
#define DEFAULT_WORLD_RADIUS			1.0 *  m
#define DEFAULT_DETECTOR_RADIUS			1.0 * cm
#define DEFAULT_DETECTOR_THICKNESS		0.5 * mm
#define DEFAULT_DETECTOR_DEAD_LAYER		0.5 * um

// DEFAULT PRIMARY GENERATOR
#define DEFAULT_PRIMARY_GENERATOR_TYPE		0x01
#define DEFAULT_PRIMARY_PARTICLE		"alpha"
#define DEFAULT_PRIMARY_ION_ATOMIC_NUMBER	84
#define DEFAULT_PRIMARY_ION_MASS_NUMBER		210
#define DEFAULT_PRIMARY_ENERGY			5.0 * MeV
#define DEFAULT_PRIMARY_DISTANCE		1.0 * cm

// DEFAULT ANALYSIS PARAMETERS
#define DEFAULT_FILE_OUT			"output.root"
#define HITS_COLLECTION_NAME			"RutherfordHitsCollection"
#define HITS_NTUPLE_NAME			"Hits"
#define HITS_NTUPLE_TITLE			"Hits"
#define DEFAULT_MIN_ENERGY_DEPOSIT		0.0 * eV

// DEFAULT RUN
#define DEFAULT_NUMBER_OF_THREADS		1
#define DEFAULT_NUMBER_OF_EVENTS		1

#endif
