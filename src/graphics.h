#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    TTF_Font     *font;
} Graphics;

bool graphics_init(Graphics *graphics);
void graphics_destroy(Graphics *graphics);

#endif
