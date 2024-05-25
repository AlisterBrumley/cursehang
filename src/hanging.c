#include <ncurses.h>
#include "structs.h"
#include "hanging.h"

void hang(int index, int max)
{
    pos hpos[2] = {
        {2, 43},  // rope top
        {4, 41}}; // head left

    // rope
    move(hpos[0].y, hpos[0].x);
    addch(ACS_TTEE);
    move(hpos[0].y + 1, hpos[0].x);
    vline(ACS_VLINE, 1);

    // head
    WINDOW *head = newwin(3, 5, hpos[1].y, hpos[1].x); // window for head
    box(head, 0, 0); //head
    mvaddch(hpos[1].y, hpos[1].x + 2, ACS_BTEE); // rope top head
    mvaddch(hpos[1].y + 2, hpos[1].x + 2, ACS_TTEE); // rope bottom head
    wrefresh(head);

    // left arm
}