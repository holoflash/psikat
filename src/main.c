#include "audio_engine.h"
#include "interface.h"
#include <curses.h>

int main(void)
{
    Player *player = launch();
    init_interface();
    printw("Hello there!\n");

    audio_unit_start(player);
    mvaddstr(LINES - 1, 0, "Press any key to quit");

    getch();
    endwin();

    audio_unit_destroy(player);
    return 0;
}
