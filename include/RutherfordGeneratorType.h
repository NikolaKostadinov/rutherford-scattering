#ifndef GENERATOR_TYPE_H
#define GENERATOR_TYPE_H

#define NULL_TYPE_ID		0x00

#define PARTICLE_GUN_ID		0x01
#define PARTICLE_GUN_STR	"gun"

#define ISOTROPIC_SOURCE_ID	0x02
#define ISOTROPIC_SOURCE_SRC	"iso"

#define DECAY_SOURCE_ID		0x03
#define DECAY_SOURCE_STR	"decay"

inline G4int TYPE_ID(G4String value)
{
	if      (value == PARTICLE_GUN_STR)     return PARTICLE_GUN_ID;
	else if (value == ISOTROPIC_SOURCE_SRC) return ISOTROPIC_SOURCE_ID;
	else if (value == DECAY_SOURCE_STR)     return DECAY_SOURCE_ID;
	else                                    return NULL_TYPE_ID;
}

#endif