#include "audio_engine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#define COLOR_WHITE  255, 255, 255, 255
#define COLOR_BLACK  0, 0, 0, 255
#define COLOR_BG     18, 12, 26, 255
#define COLOR_CURSOR 255, 195, 75, 200

static inline int wrap_index(int index, int max) { return ((index % max) + max) % max; }

int main(void) {
    Player *p = audio_init(default_arrangement());

    int grid_cell_size = 64;
    int grid_cols      = 1; // TODO: Number of tracks...in the future
    int grid_rows      = p->arrangement->pattern_len;

    float grid_pixel_w = (float)(grid_cols * grid_cell_size);
    float grid_pixel_h = (float)(grid_rows * grid_cell_size);

    int cursor_x = 0;
    int cursor_y = 0;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(0, "Error initializing SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_LogError(0, "Error initializing TTF: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window   *window;
    SDL_Renderer *renderer;
    if (!SDL_CreateWindowAndRenderer("psikat", 1280, 800, SDL_WINDOW_HIGH_PIXEL_DENSITY, &window, &renderer)) {
        SDL_LogError(0, "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    TTF_Font *font = TTF_OpenFont("fonts/jbmono.ttf", 64);
    if (!font) {
        SDL_LogError(0, "Failed to load font: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // There must be a way to skip this extra step
    SDL_Surface *surf = TTF_RenderText_Blended(font, "C4", 0, (SDL_Color){COLOR_WHITE});
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureScaleMode(text, SDL_SCALEMODE_NEAREST);
    // we don't need the surface anymore
    SDL_DestroySurface(surf);

    bool quit = false;

    while (!quit) {
        SDL_Event event;
        if (!p->playback_stopped && !p->playback_paused) {
            cursor_y = p->curr_note_index;
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                case SDLK_RETURN:
                    p->playback_stopped ? audio_unit_start(p) : audio_unit_stop(p);
                    p->playback_stopped = !p->playback_stopped;
                    p->playback_paused  = false;
                    break;
                case SDLK_SPACE:
                    (p->playback_stopped || p->playback_paused) ? audio_unit_start(p) : audio_unit_pause(p);
                    p->playback_paused  = p->playback_stopped ? false : !p->playback_paused;
                    p->playback_stopped = false;
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
                quit = true;
                break;
            }
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, COLOR_BG);
        SDL_RenderClear(renderer);

        // Text drawing!
        SDL_FRect text_box = {
            .x = 0.0,
            .y = 0.0,
            .w = (float)grid_cell_size,
            .h = (float)grid_cell_size,
        };

        SDL_RenderTexture(renderer, text, NULL, &text_box);

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

        for (int r = 0; r <= grid_rows; r++) {
            float y = (float)(r * grid_cell_size);
            SDL_RenderLine(renderer, 0.0f, y, grid_pixel_w, y);
        }

        SDL_RenderPresent(renderer);
    }

    audio_unit_destroy(p);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(text);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
