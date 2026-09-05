#include "constants.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

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
} Project;

typedef enum { STOPPED, PLAYING, PAUSED } PlaybackState;

typedef struct Transport {
    PlaybackState playback_state;
    double        phase;
    double        sample_count;
    float         master_volume;
    int           curr_note_index;
} Transport;

typedef struct Audio {
    SDL_AudioSpec    spec;
    int              sample_frames;
    SDL_AudioStream *stream;
} Audio;

typedef struct Graphics {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    TTF_Font     *font;
} Graphics;

typedef struct App {
    Graphics  graphics;
    Audio     audio;
    Transport transport;
    Project   project;
} App;

static inline int wrap_index(int index, int max) { return ((index % max) + max) % max; }

static void audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
    (void)total_amount;
    App *app = (App *)userdata;

    int   frames_needed = additional_amount / (sizeof(float) * 2);
    float sample_rate   = (float)app->audio.spec.freq;

    float samples[128 * 2];

    while (frames_needed > 0) {
        const int chunk = frames_needed < 128 ? frames_needed : 128;
        double    phase = app->transport.phase;

        Note   current_note        = app->project.pattern[app->transport.curr_note_index];
        double duration_in_samples = (60.0 / app->project.bpm) * sample_rate * (4.0 / current_note.subdivision);

        if (app->transport.sample_count >= duration_in_samples) {
            app->transport.sample_count    = 0;
            app->transport.curr_note_index = (app->transport.curr_note_index + 1) % app->project.pattern_len;

            current_note = app->project.pattern[app->transport.curr_note_index];
        }

        double frequency       = app->project.tuning * pow(2.0, (current_note.midi_value - 69.0) / 12.0);
        double phase_increment = (TWO_PI / sample_rate) * frequency;

        if (current_note.waveform == SINE) {
            for (int frame = 0; frame < chunk; ++frame) {
                float sample = (float)sin(phase);
                // TODO: maybe need to divide gain by 2 first?
                float sample_with_gain = sample * app->transport.master_volume;
                samples[frame * 2]     = sample_with_gain;
                samples[frame * 2 + 1] = sample_with_gain;

                phase += phase_increment;
                if (phase >= TWO_PI) {
                    phase -= TWO_PI;
                }
            }
        } else if (current_note.waveform == SQUARE) {
            for (int frame = 0; frame < chunk; ++frame) {
                float sample           = (phase >= M_PI) ? -1.0f : 1.0f;
                float sample_with_gain = sample * app->transport.master_volume;
                samples[frame * 2]     = sample_with_gain;
                samples[frame * 2 + 1] = sample_with_gain;

                phase += phase_increment;
                if (phase >= TWO_PI) {
                    phase -= TWO_PI;
                }
            }
        }

        app->transport.sample_count += chunk;
        app->transport.phase = phase;

        SDL_PutAudioStreamData(stream, samples, chunk * sizeof(float) * 2);

        frames_needed -= chunk;
    }
}

bool app_init(App *app) {
    app->project = (Project){
        .pattern_len = 16,
        .bpm         = 120,
        .tuning      = 440.0,
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

    app->transport.playback_state  = STOPPED;
    app->transport.curr_note_index = 0;
    app->transport.phase           = 0.0;
    app->transport.sample_count    = 0.0;
    app->transport.master_volume   = 0.1f;

    app->audio.spec.channels = 2;
    app->audio.spec.format   = SDL_AUDIO_F32LE;
    app->audio.spec.freq     = 48000;

    SDL_SetAppMetadata("psikat", "v0.0.1", "com.holoflash.psikat");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    if (!TTF_Init()) {
        fprintf(stderr, "Error initializing TTF: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(
            "psikat", 1280, 800, SDL_WINDOW_HIGH_PIXEL_DENSITY, &app->graphics.window, &app->graphics.renderer)) {
        fprintf(stderr, "Create window and renderer: %s\n", SDL_GetError());
        return false;
    }

    // app->graphics.font = TTF_OpenFont("fonts/jbmono.ttf", 64);
    // if (!app->graphics.font) {
    //     fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
    //     return false;
    // }

    SDL_SetHintWithPriority(SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES, "128", SDL_HINT_NORMAL);

    app->audio.stream =
        SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &app->audio.spec, audio_callback, app);

    SDL_GetAudioDeviceFormat(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &app->audio.spec, &app->audio.sample_frames);

    if (!app->audio.stream) {
        fprintf(stderr, "Error initializing SDL Audio Stream: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void app_destroy(App *app) {
    if (app->audio.stream) {
        SDL_DestroyAudioStream(app->audio.stream);
    }
    // SDL_DestroyTexture(text);
    // if (&app.graphics.font) {
    //     TTF_CloseFont(&app.graphics.font);
    // }
    if (app->graphics.renderer) {
        SDL_DestroyRenderer(app->graphics.renderer);
    }
    if (app->graphics.window) {
        SDL_DestroyWindow(app->graphics.window);
    }
    TTF_Quit();
    SDL_Quit();
}

int main(void) {
    static App app;
    if (!app_init(&app)) {
        app_destroy(&app);
        return EXIT_FAILURE;
    }

    Transport    *transport = &app.transport;
    Project      *project   = &app.project;
    SDL_Renderer *renderer  = app.graphics.renderer;

    int grid_cell_size = 64;
    int grid_cols      = 1; // TODO: Number of tracks...in the future
    int grid_rows      = project->pattern_len;

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
        if (transport->playback_state == PLAYING) {
            SDL_LockAudioStream(app.audio.stream);
            cursor_y = transport->curr_note_index;
            SDL_UnlockAudioStream(app.audio.stream);
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                case SDLK_RETURN:
                    SDL_LockAudioStream(app.audio.stream);
                    transport->curr_note_index = 0;
                    transport->sample_count    = 0;
                    transport->phase           = 0.0;
                    SDL_UnlockAudioStream(app.audio.stream);

                    cursor_y = 0;

                    if (transport->playback_state == STOPPED || transport->playback_state == PAUSED) {
                        transport->playback_state = PLAYING;
                        SDL_ResumeAudioStreamDevice(app.audio.stream);

                    } else {
                        transport->playback_state = STOPPED;
                        SDL_PauseAudioStreamDevice(app.audio.stream);
                    }
                    break;
                case SDLK_SPACE:
                    transport->sample_count = 0;
                    if (transport->playback_state == PLAYING) {
                        transport->playback_state = PAUSED;
                        SDL_PauseAudioStreamDevice(app.audio.stream);
                    } else {
                        transport->playback_state = PLAYING;
                        SDL_ResumeAudioStreamDevice(app.audio.stream);
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
    app_destroy(&app);
    return EXIT_SUCCESS;
}
