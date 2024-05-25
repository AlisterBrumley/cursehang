#include <ncurses.h>
#include "cursehelpers.h"

// init ncurses
void initialize(void)
{
    initscr();
    cbreak();
    noecho();
}

// draw gallows for game start
void draw_gallows(void)
{
    // top bar
    move(2, 25);
    addch(ACS_ULCORNER);
    hline(ACS_HLINE, 20);
    // pillar
    move(3, 25);
    vline(ACS_VLINE, 10);
    // floor
    move(13, 22);
    hline(ACS_HLINE, 3);
    move(13, 25);
    addch(ACS_BTEE);
    hline(ACS_HLINE, 25);
}