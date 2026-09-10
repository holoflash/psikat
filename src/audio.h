#ifndef AUDIO_H
#define AUDIO_H

#include <AudioToolbox/AudioToolbox.h>

typedef struct App App;

bool audio_init(AudioUnit *unit, App *app);
void audio_start(AudioUnit *unit);
void audio_stop(AudioUnit *unit);
void audio_destroy(AudioUnit *unit);

#endif
