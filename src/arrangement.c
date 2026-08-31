#include "arrangement.h"
#include <math.h>

double division_to_samples(double bpm, double division) { return (60.0 / bpm) * SAMPLE_RATE * (4.0 / division); }
double freq_to_phase_increment(double frequency) { return (2.0 * M_PI) / SAMPLE_RATE * frequency; }

static Arrangement arrangement;

Arrangement *default_arrangement(void) {
    arrangement = (Arrangement){
        .pattern_len = 6,
        .pattern     = {
                        {freq_to_phase_increment(N_FREQUENCY[60]), division_to_samples(DEFAULT_BPM, 16.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[62]), division_to_samples(DEFAULT_BPM, 16.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[63]), division_to_samples(DEFAULT_BPM, 16.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[65]), division_to_samples(120.0, 16.0), SINE},
                        {freq_to_phase_increment(N_FREQUENCY[67]), division_to_samples(130.0, 16.0), SINE},
                        {freq_to_phase_increment(N_FREQUENCY[68]), division_to_samples(140.0, 16.0), SQUARE},
                        }
    };

    return &arrangement;
}
