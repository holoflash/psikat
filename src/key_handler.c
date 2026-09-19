#include "key_handler.h"
#include "audio.h"
#include "constants.h"

void handle_key_down(App *app, int key_code) {
    switch (key_code) {
    case KEY_ENTER:
        app->transport.curr_note_index = 0;
        app->transport.sample_count    = 0;
        app->transport.phase           = 0.0;

        if (app->transport.playback_state == STOPPED || app->transport.playback_state == PAUSED) {
            app->transport.playback_state = PLAYING;
            audio_start(&app->audio.output_unit);
        } else {
            app->transport.playback_state = STOPPED;
            audio_stop(&app->audio.output_unit);
        }
        break;

    case KEY_SPACE:
        app->transport.sample_count = 0;
        if (app->transport.playback_state == PLAYING) {
            app->transport.playback_state = PAUSED;
            audio_stop(&app->audio.output_unit);
        } else {
            app->transport.playback_state = PLAYING;
            audio_start(&app->audio.output_unit);
        }
        break;
    }
}
