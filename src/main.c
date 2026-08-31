#include "arrangement.h"
#include "audio_engine.h"
#include "interface.h"

#include <curses.h>

// TODO: how come do my keys correspond to these codes?
#define ENTER_KEY 10
#define SPACE_KEY 32

int main(void)
{
    // TODO: this should probably live somewhere else
    bool stopped     = true;
    bool paused      = false;
    bool app_running = true;

    Arrangement *arrangement = default_arrangement();
    Player      *player      = audio_init(arrangement);
    init_interface();

    while (app_running)
    {
        stopped ? printw("Hit ENTER to play\n") : printw("Hit ENTER to stop\n");
        mvaddstr(LINES - 1, 0, "Press any key to quit");

        switch (getch())
        {
        case ENTER_KEY:
            stopped ? audio_unit_start(player) : audio_unit_stop(player);
            stopped = !stopped;
            break;
        case SPACE_KEY:
            paused = !paused;
            break;
        default:
            app_running = false;
            break;
        }
        clear();
    }

    audio_unit_stop(player);
    audio_unit_destroy(player);
    endwin();
    return 0;
}
