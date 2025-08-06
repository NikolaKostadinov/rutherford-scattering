#ifndef DEFAULTS_H
#define DEFAULTS_H

// DEFAULT GEOMETRY
#define DEFAULT_WORLD_RADIUS	1.0 * m
#define DEFAULT_FOIL_RADIUS	1.0 * cm
#define DEFAULT_FOIL_THICKNESS	1.0 * um

// DEFAULT GENERATED PARTICLE
#define ALPHA_PARICLE		"alpha"
#define DEFAULT_ENERGY		5.0 * MeV
#define DEFAULT_DISTANCE	1.0 * cm

// DEFAULT ROOT HISTOGRAMS
//
// ENERGY SPECTRUM
#define DEFAULT_ENERGY_TITLE	"Energy Spectrum; E [MeV]; d\\sigma/dE [counts per bin]"
#define DEFAULT_ENERGY_BINS	100
#define DEFAULT_ENERGY_MIN	4.0 * MeV
#define DEFAULT_ENERGY_MAX	5.0 * MeV
//
// DIFFERENTIAL CROSS SECTION
#define DEFAULT_THETA_TITLE	"Differential Cross Section; \\theta [deg]; d\\sigma/d\\Omega [counts per bin]"
#define DEFAULT_THETA_BINS	100
#define DEFAULT_THETA_MIN	0.0 * deg
#define DEFAULT_THETA_MAX	10.0 * deg

#endif
