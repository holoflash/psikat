#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "arrangement.h"

typedef struct Player Player;

Player *audio_init(Arrangement *arrangement);
void    audio_unit_start(Player *player);
void    audio_unit_stop(Player *player);
void    audio_unit_destroy(Player *player);

#endif
