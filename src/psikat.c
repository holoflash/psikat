#include "psikat.h"
#include "notes.h"

#include <math.h>

double d2s(double bpm, double division) { return (60.0 / bpm) * SAMPLE_RATE * (4.0 / division); }
double f2p(double frequency) { return (TWO_PI) / SAMPLE_RATE * frequency; }

bool psikat_init(Psikat *psikat) {
    psikat->player.composition = (Composition){
        .pattern_len = 16,
        .pattern =
            {
                      {f2p(N_FREQUENCY[57]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[60]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[64]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[68]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[69]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[72]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[76]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[80]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[81]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[80]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[76]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[72]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[69]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[68]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[64]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      {f2p(N_FREQUENCY[60]), d2s(DEFAULT_BPM, 55.0), SQUARE},
                      },
    };

    psikat->player.playback_state  = STOPPED;
    psikat->player.curr_note_index = 0;
    psikat->player.phase           = 0.0;
    psikat->player.sample_count    = 0.0;

    if (!graphics_init(&psikat->graphics)) {
        return false;
    }

    if (!audio_init(&psikat->output_unit, &psikat->player)) {
        graphics_destroy(&psikat->graphics);
        return false;
    }

    return true;
}

void psikat_destroy(Psikat *psikat) {
    audio_destroy(&psikat->output_unit);
    graphics_destroy(&psikat->graphics);
}
