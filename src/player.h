#ifndef PLAYER_H
#define PLAYER_H

#define SAMPLE_RATE 44100.0 // Shouldn't hard-code this
#define DEFAULT_BPM 140.0   // Or this

typedef enum { SINE, SQUARE } Waveform;

typedef struct {
    double   phase_increment;
    double   duration_in_samples;
    Waveform waveform;
} Note;

typedef struct {
    Note pattern[16];
    int  pattern_len;
} Composition;

typedef enum { STOPPED, PLAYING, PAUSED } PlaybackState;

typedef struct Player {
    Composition   composition;
    PlaybackState playback_state;
    int           curr_note_index;
    double        phase;
    double        sample_count;
    double        volume;
} Player;

#endif
