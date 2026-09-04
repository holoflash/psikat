#include "graphics.h"

#include <stdio.h>

bool graphics_init(Graphics *graphics) {
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
            "psikat", 1280, 800, SDL_WINDOW_HIGH_PIXEL_DENSITY, &graphics->window, &graphics->renderer)) {
        fprintf(stderr, "Create window and renderer: %s\n", SDL_GetError());
        return false;
    }

    graphics->font = TTF_OpenFont("fonts/jbmono.ttf", 64);
    if (!graphics->font) {
        fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void graphics_destroy(Graphics *graphics) {
    if (graphics->font) {
        TTF_CloseFont(graphics->font);
    }
    if (graphics->renderer) {
        SDL_DestroyRenderer(graphics->renderer);
    }
    if (graphics->window) {
        SDL_DestroyWindow(graphics->window);
    }
    TTF_Quit();
    SDL_Quit();
}
