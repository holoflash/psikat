#include "arrangement.h"
#include "audio_engine.h"
#include "interface.h"
#include <curses.h>

// TODO: how come do my keys correspond to these codes?
#define ENTER    10
#define SPACEBAR 32

int main(void) {
    Player *p = audio_init(default_arrangement());
    init_interface();

    int key_pressed;

    while ((key_pressed = getch()) != 'q') {
        clear();
        if (key_pressed == ENTER) {
            p->playback_stopped ? audio_unit_start(p) : audio_unit_stop(p);
            p->playback_stopped = !p->playback_stopped;
            p->playback_paused  = false;
        } else if (key_pressed == SPACEBAR) {
            (p->playback_stopped || p->playback_paused) ? audio_unit_start(p) : audio_unit_pause(p);
            p->playback_paused  = p->playback_stopped ? false : !p->playback_paused;
            p->playback_stopped = false;
        }

        if (p->playback_stopped) {
            printw("Hit ENTER or SPACE to play\n\n");
            printw("       - STOPPED\n\n");

        } else if (p->playback_paused) {
            printw("Hit SPACE to resume; ENTER to stop\n\n");
            printw("       || PAUSED\n\n");
        } else {
            printw("Hit SPACE to pause; ENTER to stop\n\n");
            printw("       > PLAYING\n\n");
        }

        mvaddstr(LINES - 1, 0, "Press Q to quit");
        refresh();
    }

    audio_unit_destroy(p);
    endwin();
    return 0;
}
