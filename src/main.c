#include "psikat.h"
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#define COLOR_WHITE  255, 255, 255, 255
#define COLOR_BLACK  0, 0, 0, 255
#define COLOR_BG     18, 12, 26, 255
#define COLOR_CURSOR 255, 195, 75, 200

static inline int wrap_index(int index, int max) { return ((index % max) + max) % max; }

int main(void) {
    static Psikat psikat;
    if (!psikat_init(&psikat)) {
        return EXIT_FAILURE;
    }

    Player       *player   = &psikat.player;
    SDL_Renderer *renderer = psikat.graphics.renderer;

    int grid_cell_size = 64;
    int grid_cols      = 1; // TODO: Number of tracks...in the future
    int grid_rows      = player->composition.pattern_len;

    float grid_pixel_w = (float)(grid_cols * grid_cell_size);
    float grid_pixel_h = (float)(grid_rows * grid_cell_size);

    int cursor_x = 0;
    int cursor_y = 0;

    // There must be a way to skip this extra step
    // SDL_Surface *surf = TTF_RenderText_Blended(psikat.graphics.font, "C4", 0, (SDL_Color){COLOR_WHITE});
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
                        audio_start(&psikat.output_unit);
                    } else {
                        player->playback_state = STOPPED;
                        audio_stop(&psikat.output_unit);
                    }
                    break;
                case SDLK_SPACE:
                    player->sample_count = 0;
                    if (player->playback_state == PLAYING) {
                        player->playback_state = PAUSED;
                        audio_stop(&psikat.output_unit);
                    } else {
                        player->playback_state = PLAYING;
                        audio_start(&psikat.output_unit);
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

    psikat_destroy(&psikat);

    return EXIT_SUCCESS;
}
