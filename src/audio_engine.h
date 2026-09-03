#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "arrangement.h"
#include <AudioToolbox/AudioToolbox.h>

#define UNUSED __attribute__((unused))

typedef struct Player Player;
typedef enum { STOPPED, PLAYING, PAUSED } PlaybackState;

struct Player {
    AudioUnit     output_unit;
    Arrangement  *arrangement;
    double        phase;
    double        sample_count;
    int           curr_note_index;
    PlaybackState playback_state;
};

Player *audio_init(Arrangement *a);
void    audio_unit_start(Player *p);
void    audio_unit_stop(Player *p);
void    audio_unit_pause(Player *p);
void    audio_unit_destroy(Player *p);

#endif
