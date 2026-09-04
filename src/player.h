#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL_audio.h>

typedef enum { SINE, SQUARE } Waveform;

typedef struct {
    int      midi_value;
    double   subdivision;
    Waveform waveform;
} Note;

typedef struct {
    Note   pattern[16];
    int    pattern_len;
    double bpm;
} Composition;

typedef struct {
    SDL_AudioSpec audio_spec;
    int           sample_frames;
} AudioDevice;

typedef enum { STOPPED, PLAYING, PAUSED } PlaybackState;

typedef struct Player {
    Composition   composition;
    PlaybackState playback_state;
    int           curr_note_index;
    double        phase;
    double        sample_count;
    double        volume;
    AudioDevice   audio_device;
} Player;

#endif
