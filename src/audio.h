#ifndef AUDIO_H
#define AUDIO_H

#include <AudioToolbox/AudioToolbox.h>
#include <stdbool.h>

#define TWO_PI 6.283185307

struct Player;

bool audio_init(AudioUnit *unit, struct Player *player);
void audio_start(AudioUnit *unit);
void audio_stop(AudioUnit *unit);
void audio_destroy(AudioUnit *unit);

#endif
