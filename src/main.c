#include <curses.h>

#include "arrangement.h"
#include "audio_engine.h"
#include "interface.h"

// TODO: how come do my keys correspond to these codes?
#define P_ENTER_KEY 10
#define P_SPACE_KEY 32

int main(void) {
    // TODO: this should probably live somewhere else
    bool stopped     = true;
    bool paused      = false;
    bool app_running = true;

    Arrangement *arrangement = default_arrangement();
    Player      *player      = audio_init(arrangement);
    init_interface();

    while (app_running) {
        clear();

        printw(stopped  ? "Hit ENTER or SPACE to play\n"
               : paused ? "Hit SPACE to resume; ENTER to stop\n"
                        : "Hit SPACE to pause; ENTER to stop\n");

        if (!stopped && !paused) {
            attron(A_BOLD);
            printw("\nPLAYING\n");
            attroff(A_BOLD);
        }

        mvaddstr(LINES - 1, 0, "Press any other key to quit");
        refresh();

        switch (getch()) {
        case P_ENTER_KEY:
            stopped ? audio_unit_start(player) : audio_unit_stop(player);
            stopped = !stopped;
            paused  = false;
            break;

        case P_SPACE_KEY:
            (stopped || paused) ? audio_unit_start(player) : audio_unit_pause(player);
            paused  = stopped ? false : !paused;
            stopped = false;
            break;

        default:
            app_running = false;
            break;
        }
    }

    audio_unit_destroy(player);
    endwin();
    return 0;
}
