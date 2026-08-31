#include "arrangement.h"
#include <math.h>

double division_to_samples(double bpm, double division) { return (60.0 / bpm) * SAMPLE_RATE * (4.0 / division); }
double freq_to_phase_increment(double frequency) { return (2.0 * M_PI) / SAMPLE_RATE * frequency; }

static Arrangement a;

Arrangement *default_arrangement(void) {
    a = (Arrangement){
        .pattern_len = 16,
        .pattern     = {
                        {freq_to_phase_increment(N_FREQUENCY[57]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[60]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[64]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[68]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[69]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[72]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[76]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[80]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[81]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[80]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[76]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[72]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[69]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[68]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[64]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        {freq_to_phase_increment(N_FREQUENCY[60]), division_to_samples(DEFAULT_BPM, 55.0), SQUARE},
                        }
    };

    return &a;
}
