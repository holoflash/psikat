#include "app.h"
#include "audio.h"
#include "constants.h"
#include "helpers.h"
#include "wav.h"
#include <AudioToolbox/AudioToolbox.h>
#include <math.h>
#include <stdlib.h>

//    ▄███████▄    ▄████████  ▄█     ▄█   ▄█▄    ▄████████     ███
//   ███    ███   ███    ███ ███    ███ ▄███▀   ███    ███ ▀█████████▄
//   ███    ███   ███    █▀  ███▌   ███▐██▀     ███    ███    ▀███▀▀██
//   ███    ███   ███        ███▌  ▄█████▀      ███    ███     ███   ▀
// ▀█████████▀  ▀███████████ ███▌ ▀▀█████▄    ▀███████████     ███
//   ███                 ███ ███    ███▐██▄     ███    ███     ███
//   ███           ▄█    ███ ███    ███ ▀███▄   ███    ███     ███
//  ▄████▀       ▄████████▀  █▀     ███   ▀█▀   ███    █▀     ▄████▀
//                                  ▀

int main(void) {
    // TODO: here while debugging
    // wav_hello_world();
    // return 0;
    //___________________________
    static App app;
    app.project = (Project){
        .pattern_len = 16,
        .bpm         = 100,
        .tuning      = 440.0,
        .duration    = 0.0,
        .pattern =
            {
                      {57, 16.0, SQUARE},
                      {60, 16.0, SQUARE},
                      {64, 16.0, SQUARE},
                      {68, 16.0, SQUARE},
                      {69, 16.0, SQUARE},
                      {72, 16.0, SQUARE},
                      {76, 16.0, SQUARE},
                      {80, 16.0, SQUARE},
                      {81, 16.0, SQUARE},
                      {80, 16.0, SQUARE},
                      {76, 16.0, SQUARE},
                      {72, 16.0, SQUARE},
                      {69, 16.0, SQUARE},
                      {68, 16.0, SQUARE},
                      {64, 16.0, SQUARE},
                      {60, 16.0, SQUARE},
                      },
    };

    app.transport.playback_state  = STOPPED;
    app.transport.curr_note_index = 0;
    app.transport.phase           = 0.0;
    app.transport.sample_count    = 0.0;
    app.transport.master_volume   = 0.1;

    app.audio.sample_rate = 48000.0;

    audio_init(&app.audio.output_unit, &app);
    audio_start(&app.audio.output_unit);

    getchar();
    audio_stop(&app.audio.output_unit);
    audio_destroy(&app.audio.output_unit);
    return EXIT_SUCCESS;
}
