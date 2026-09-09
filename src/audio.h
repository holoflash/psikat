#ifndef AUDIO_H
#define AUDIO_H

#include "app.h"
#include <AudioToolbox/AudioToolbox.h>

bool audio_init(AudioUnit *unit, struct App *app);
void audio_start(AudioUnit *unit);
void audio_stop(AudioUnit *unit);
void audio_destroy(AudioUnit *unit);

#endif
