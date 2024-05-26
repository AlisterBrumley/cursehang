#include <ncurses.h>
#include "structs.h"
#include "hanging.h"

void hang(int index, int max)
{
    pos hpos[] = {
        {2, 43}, // rope top
        {4, 41}, // head (left top)
        {6, 43}, // body (bottom of head)
        {7, 38}, // left arm
        {7, 43}, // right arm
        {9, 42}, // left leg
        {9, 43}  // right leg

    };

    WINDOW *head;
    // mvprintw(23, 0, "%i", index);

    switch (index)
    {
    case 0:
        // rope
        move(hpos[index].y, hpos[index].x);
        addch(ACS_TTEE);
        move(hpos[index].y + 1, hpos[index].x);
        vline(ACS_VLINE, 1);
        break;
    case 1:
        // head
        head = newwin(3, 5, hpos[index].y, hpos[index].x); // window for head
        box(head, 0, 0);                                   // head
        move(hpos[index].y, hpos[index].x + 2);            //
        addch(ACS_BTEE);                                   // rope top head
        wrefresh(head);
        break;
    case 2:
        // body
        move(hpos[index].y, hpos[index].x);
        addch(ACS_TTEE);
        move(hpos[index].y + 1, hpos[index].x);
        vline(ACS_VLINE, 3);
        break;
    case 3:
        // left arm
        move(hpos[index].y, hpos[index].x);
        hline(ACS_HLINE, 5);
        move(hpos[index].y, hpos[index].x + 5);
        addch(ACS_RTEE);
        break;
    case 4:
        // right arm
        move(hpos[index].y, hpos[index].x);
        addch(ACS_PLUS);
        hline(ACS_HLINE, 5);
        break;
    case 5:
        // left leg
        move(hpos[index].y, hpos[index].x);
        addch(ACS_ULCORNER);
        addch(ACS_LRCORNER);
        move(hpos[index].y + 1, hpos[index].x);
        vline(ACS_VLINE, 2);
        break;
    case 6:
        // right leg
        move(hpos[index].y, hpos[index].x);
        addch(ACS_BTEE);
        addch(ACS_URCORNER);
        move(hpos[index].y + 1, hpos[index].x + 1);
        vline(ACS_VLINE, 2);
        break;
    }
    refresh();
}