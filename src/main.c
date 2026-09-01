#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#define COLOR_BG 50, 10, 60, 255

// Adapteded from SDL2 docs https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
void PrintModifiers(SDL_Keymod mod) {
    if (mod == SDL_KMOD_NONE) {
        return;
    }

    printf("Modifiers: ");
    if (mod & SDL_KMOD_NUM)
        printf("NUMLOCK ");
    if (mod & SDL_KMOD_CAPS)
        printf("CAPSLOCK ");
    if (mod & SDL_KMOD_LCTRL)
        printf("LCTRL ");
    if (mod & SDL_KMOD_RCTRL)
        printf("RCTRL ");
    if (mod & SDL_KMOD_RSHIFT)
        printf("RSHIFT ");
    if (mod & SDL_KMOD_LSHIFT)
        printf("LSHIFT ");
    if (mod & SDL_KMOD_RALT)
        printf("RALT ");
    if (mod & SDL_KMOD_LALT)
        printf("LALT ");
    if (mod & SDL_KMOD_CTRL)
        printf("CTRL ");
    if (mod & SDL_KMOD_SHIFT)
        printf("SHIFT ");
    if (mod & SDL_KMOD_ALT)
        printf("ALT ");
    printf("\n");
}

void PrintKeyInfo(SDL_KeyboardEvent *key) {
    if (key->type == SDL_EVENT_KEY_UP)
        printf("Release:- ");
    else
        printf("Press:- ");

    printf("Scancode: 0x%02X", key->scancode);
    printf(", Name: %s", SDL_GetKeyName(key->key));
    if (key->type == SDL_EVENT_KEY_DOWN) {
        printf(", Unicode: ");
        if (key->key < 0x80 && key->key > 0) {
            printf("%c (0x%04X)", (char)key->key, key->key);
        } else {
            printf("? (0x%04X)", key->key);
        }
    }
    printf("\n");
    PrintModifiers(key->mod);
}

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("psikat", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "Couldn't create window\n");
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "Couldn't create renderer\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    bool      running = true;
    SDL_Event event;

    SDL_Log("SDL3 window initialized and program running");

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                // instead of printing the key, we'll read it and handle it
                PrintKeyInfo(&event.key);
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, COLOR_BG);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// NCURSES MAIN FOR REFERENCE
//     Player *p = audio_init(default_arrangement());
//     init_interface();

//     int key_pressed;

//     while ((key_pressed = getch()) != 'q') {
//         clear();
//         if (key_pressed == ENTER) {
//             p->playback_stopped ? audio_unit_start(p) : audio_unit_stop(p);
//             p->playback_stopped = !p->playback_stopped;
//             p->playback_paused  = false;
//         } else if (key_pressed == SPACEBAR) {
//             (p->playback_stopped || p->playback_paused) ? audio_unit_start(p) : audio_unit_pause(p);
//             p->playback_paused  = p->playback_stopped ? false : !p->playback_paused;
//             p->playback_stopped = false;
//         }

//         if (p->playback_stopped) {
//             printw("Hit ENTER or SPACE to play\n\n");
//             printw("       - STOPPED\n\n");

//         } else if (p->playback_paused) {
//             printw("Hit SPACE to resume; ENTER to stop\n\n");
//             printw("       || PAUSED\n\n");
//         } else {
//             printw("Hit SPACE to pause; ENTER to stop\n\n");
//             printw("       > PLAYING\n\n");
//         }

//         mvaddstr(LINES - 1, 0, "Press Q to quit");
//         refresh();
