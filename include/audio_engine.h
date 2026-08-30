#ifndef AUDIO_UNIT_H
#define AUDIO_UNIT_H

typedef struct Player Player;

Player *launch(void);
void    audio_unit_start(Player *player);
void    audio_unit_stop(Player *player);
void    audio_unit_destroy(Player *player);

#endif
