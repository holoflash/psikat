#ifndef AUDIO_H
#define AUDIO_H

#include <AudioToolbox/AudioToolbox.h>

typedef enum { SINE, SQUARE } Waveform;

typedef struct Note {
    int      midi_value;
    double   subdivision;
    Waveform waveform;
} Note;

typedef struct Project {
    int    pattern_len;
    double bpm;
    double tuning;
    Note   pattern[16];
    double duration;
} Project;

typedef enum { STOPPED, PLAYING, PAUSED } PlaybackState;

typedef struct Transport {
    PlaybackState playback_state;
    double        phase;
    double        sample_count;
    double        master_volume;
    int           curr_note_index;
    int           sample_frames;
} Transport;

typedef struct Audio {
    AudioUnit output_unit;
    double    sample_rate;
} Audio;

typedef struct App {
    Audio     audio;
    Transport transport;
    Project   project;
} App;

bool audio_init(AudioUnit *unit, App *app);
void audio_start(AudioUnit *unit);
void audio_stop(AudioUnit *unit);
void audio_destroy(AudioUnit *unit);

#endif
