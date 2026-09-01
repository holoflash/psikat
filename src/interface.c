#include "interface.h"
#include <ncurses.h>

void init_interface(void) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    clear();
    start_color();
    assume_default_colors(COLOR_BLACK, COLOR_MAGENTA);
}
