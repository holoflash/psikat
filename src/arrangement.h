#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "notes.h"

#define MAX_NOTES   (256 * 256)
#define SAMPLE_RATE 44100.0
#define DEFAULT_BPM 80.0
#define SINE        0
#define SQUARE      1

typedef struct {
    double phase_increment;
    double duration_in_samples;
    int    instrument;
} Note;

typedef struct {
    Note pattern[MAX_NOTES];
    int  pattern_len;
} Arrangement;

double       division_to_samples(double bpm, double division);
double       freq_to_phase_increment(double frequency);
Arrangement *default_arrangement(void);

#endif
