#ifndef PSIKAT_H
#define PSIKAT_H

#include "audio.h"
#include "graphics.h"
#include "player.h"

#include <stdbool.h>

typedef struct {
    Graphics  graphics;
    AudioUnit output_unit;
    Player    player;
} Psikat;

bool psikat_init(Psikat *psikat);
void psikat_destroy(Psikat *psikat);

// Subdivision to Number of Samples
double d2s(double bpm, double division);

// Frequency to Phase Increment
double f2p(double frequency);

#endif
