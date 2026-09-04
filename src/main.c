#include "colors.h"
#include "graphics.h"
#include "notes.h"
#include "player.h"
#include <SDL3/SDL_main.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    Graphics         graphics;
    Player           player;
    SDL_AudioStream *stream;
} App;

#define TWO_PI 6.283185307

static inline int wrap_index(int index, int max) { return ((index % max) + max) % max; }

static void audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
    (void)total_amount;
    Player *player = (Player *)userdata;
    additional_amount /= sizeof(float) * 2;
    float sample_rate = (float)player->audio_device.audio_spec.freq;

    while (additional_amount > 0) {
        float     samples[128];
        const int total = additional_amount < 64 ? additional_amount : 64;
        double    phase = player->phase;

        // "sequencer"
        for (int frame = 0; frame < total; ++frame) {
            Note curr_note = player->composition.pattern[player->curr_note_index];

            double duration_in_samples =
                (60.0 / player->composition.bpm) * sample_rate * (4.0 / curr_note.subdivision);

            if (player->sample_count >= duration_in_samples) {
                player->sample_count    = 0;
                player->curr_note_index = (player->curr_note_index + 1) % player->composition.pattern_len;
            }

            // "Wave generator"
            double phase_increment = (TWO_PI) / sample_rate * N_FREQUENCY[curr_note.midi_value];

            phase += phase_increment;

            if (phase >= TWO_PI) {
                phase -= TWO_PI;
            }

            if (SINE == curr_note.waveform) {
                samples[frame * 2]     = sin(phase);
                samples[frame * 2 + 1] = sin(phase);
            }
            if (SQUARE == curr_note.waveform) {
                // Square wave: flip halway through the wave cycle
                if (phase >= M_PI) {
                    samples[frame * 2]     = -1.0;
                    samples[frame * 2 + 1] = -1.0;
                } else {
                    samples[frame * 2]     = 1.0;
                    samples[frame * 2 + 1] = 1.0;
                }
            }
            player->sample_count++;
        }

        SDL_PutAudioStreamData(stream, samples, total * sizeof(float) * 2);
        player->phase = phase;
        additional_amount -= total;
    }
}

bool app_init(App *app) {
    SDL_SetAppMetadata("psikat", "0.1", "com.holoflash.psikat");
    app->player.composition = (Composition){
        .pattern_len = 16,
        .bpm         = 120,
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

    app->player.playback_state  = STOPPED;
    app->player.curr_note_index = 0;
    app->player.phase           = 0.0;
    app->player.sample_count    = 0.0;

    if (!graphics_init(&app->graphics)) {
        return false;
    }
    SDL_SetHintWithPriority(SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES, "128", SDL_HINT_NORMAL);

    app->player.audio_device.audio_spec.channels = 2;
    app->player.audio_device.audio_spec.format   = SDL_AUDIO_F32LE;
    app->player.audio_device.audio_spec.freq     = 48000;

    app->stream = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &app->player.audio_device.audio_spec, audio_callback, &app->player);

    SDL_GetAudioDeviceFormat(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                             &app->player.audio_device.audio_spec,
                             &app->player.audio_device.sample_frames);

    printf("Running with audio device format: %s, channels: %d, freq: %d, sample_frames: %d\n",
           SDL_GetAudioFormatName(app->player.audio_device.audio_spec.format),
           app->player.audio_device.audio_spec.channels,
           app->player.audio_device.audio_spec.freq,
           app->player.audio_device.sample_frames);

    if (!app->stream) {
        fprintf(stderr, "Error initializing SDL Audio Stream: %s\n", SDL_GetError());
        graphics_destroy(&app->graphics);
        return false;
    }

    return true;
}

void app_destroy(App *app) {
    SDL_DestroyAudioStream(app->stream);
    graphics_destroy(&app->graphics);
}

int main(void) {
    static App app;
    if (!app_init(&app)) {
        return EXIT_FAILURE;
    }

    Player       *player   = &app.player;
    SDL_Renderer *renderer = app.graphics.renderer;

    int grid_cell_size = 64;
    int grid_cols      = 1; // TODO: Number of tracks...in the future
    int grid_rows      = player->composition.pattern_len;

    float grid_pixel_w = (float)(grid_cols * grid_cell_size);
    float grid_pixel_h = (float)(grid_rows * grid_cell_size);

    int cursor_x = 0;
    int cursor_y = 0;

    // There must be a way to skip this extra step
    // SDL_Surface *surf = TTF_RenderText_Blended(app.graphics.font, "C4", 0, (SDL_Color){COLOR_WHITE});
    // SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    // SDL_SetTextureScaleMode(text, SDL_SCALEMODE_NEAREST);
    // // we don't need the surface anymore
    // SDL_DestroySurface(surf);

    bool running = true;

    while (running) {
        SDL_Event event;
        if (player->playback_state == PLAYING) {
            cursor_y = player->curr_note_index;
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                case SDLK_RETURN:
                    player->curr_note_index = 0;
                    player->sample_count    = 0;
                    cursor_y                = 0;

                    if (player->playback_state == STOPPED || player->playback_state == PAUSED) {
                        player->playback_state = PLAYING;
                        SDL_ResumeAudioStreamDevice(app.stream);

                    } else {
                        player->playback_state = STOPPED;
                        SDL_PauseAudioStreamDevice(app.stream);
                    }
                    break;
                case SDLK_SPACE:
                    player->sample_count = 0;
                    if (player->playback_state == PLAYING) {
                        player->playback_state = PAUSED;
                        SDL_PauseAudioStreamDevice(app.stream);
                    } else {
                        player->playback_state = PLAYING;
                        SDL_ResumeAudioStreamDevice(app.stream);
                    }
                    break;
                case SDLK_UP:
                    cursor_y = wrap_index(cursor_y - 1, grid_rows);
                    break;
                case SDLK_DOWN:
                    cursor_y = wrap_index(cursor_y + 1, grid_rows);
                    break;
                case SDLK_LEFT:
                    cursor_x = wrap_index(cursor_x - 1, grid_cols);
                    break;
                case SDLK_RIGHT:
                    cursor_x = wrap_index(cursor_x + 1, grid_cols);
                    break;
                }
                break;
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, COLOR_BG);
        SDL_RenderClear(renderer);

        // Text drawing!
        // SDL_FRect text_box = {
        //     .x = 0.0,
        //     .y = 0.0,
        //     .w = (float)grid_cell_size,
        //     .h = (float)grid_cell_size,
        // };

        // SDL_RenderTexture(renderer, text, NULL, &text_box);

        SDL_SetRenderDrawColor(renderer, COLOR_CURSOR);

        SDL_FRect cursor_rect = {.x = (float)(cursor_x * grid_cell_size),
                                 .y = (float)(cursor_y * grid_cell_size),
                                 .w = (float)grid_cell_size,
                                 .h = (float)grid_cell_size};

        SDL_RenderFillRect(renderer, &cursor_rect);

        SDL_SetRenderDrawColor(renderer, COLOR_WHITE);
        for (int c = 0; c <= grid_cols; c++) {
            float x = (float)(c * grid_cell_size);
            SDL_RenderLine(renderer, x, 0.0f, x, grid_pixel_h);
        }

        for (int row = 0; row <= grid_rows; row++) {
            float y = (float)(row * grid_cell_size);
            SDL_RenderLine(renderer, 0.0f, y, grid_pixel_w, y);
        }

        SDL_RenderPresent(renderer);
    }

    // SDL_DestroyTexture(text);
    app_destroy(&app);

    return EXIT_SUCCESS;
}
