#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "arrangement.h"
#include <AudioToolbox/AudioToolbox.h>

#define UNUSED __attribute__((unused))

typedef struct Player Player;

struct Player
{
    AudioUnit    output_unit;
    Arrangement *arrangement;
    double       phase;
    double       sample_count;
    int          curr_note_index;
};

Player *audio_init(Arrangement *arrangement);
void    audio_unit_start(Player *player);
void    audio_unit_stop(Player *player);
void    audio_unit_destroy(Player *player);

#endif
