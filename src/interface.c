#include "interface.h"

#include <curses.h>

void init_interface(void)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
}
