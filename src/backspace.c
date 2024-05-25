#include <ncurses.h>
#include "backspace.h"

void backspace()
{
    int y, x;
    getyx(stdscr, y, x);
    mvdelch(y, (x - 1));
}
