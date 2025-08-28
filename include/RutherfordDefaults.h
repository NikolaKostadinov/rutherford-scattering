#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <G4SystemOfUnits.hh>

#define RUTHERFORD			"Rutherford Scattering"
#define RUTHERFORD_VERSION		"v0.2"

// DEFAULT VACUUM
#define VACUUM				"Vacuum"
#define HYDROGEN			1
#define VACUUM_NUMBER_DENSITY		0.06 * 1/cm3

// DEFAULT DETECTOR MATERIAL
#define DETECTOR_MATERIAL		"Detectorium"
#define DEFAULT_DETECTOR_ATOMIC_NUMBER	79
#define DEFAULT_DETECTOR_NUMBER_DENSITY 5.91e+22 * 1/cm3

// DEFAULT DETECTOR GEOMETRY
#define WORLD_NAME			"Manchester"
#define DETECTOR_NAME			"Rutherfoil"
#define DEFAULT_WORLD_RADIUS		1.0 *  m
#define DEFAULT_DETECTOR_RADIUS		1.0 * cm
#define DEFAULT_DETECTOR_THICKNESS	1.0 * um

// DEFAULT GENERATED PARTICLE
#define PARTICLE_NAME			"alpha"
#define DEFAULT_ENERGY			5.0 * MeV
#define DEFAULT_DISTANCE		1.0 * cm

// DEFAULT ROOT HISTOGRAMS
#define DEFAULT_FILE_OUT		"output.root"
//
// ENERGY SPECTRUM
#define DEFAULT_ENERGY_TITLE		"Energy Spectrum d\\sigma/dE [counts per bin]"
#define DEFAULT_ENERGY_BINS		100
#define DEFAULT_ENERGY_MIN		4.0 * MeV
#define DEFAULT_ENERGY_MAX		5.0 * MeV
//
// DIFFERENTIAL CROSS SECTION
#define DEFAULT_THETA_TITLE		"Differential Cross Section d\\sigma/d\\Omega [counts per bin]"
#define DEFAULT_THETA_BINS		1000
#define DEFAULT_THETA_MIN		0.0   * deg
#define DEFAULT_THETA_MAX		180.0 * deg

// RUN
#define DEFAULT_NUMBER_OF_EVENTS	1

#endif
