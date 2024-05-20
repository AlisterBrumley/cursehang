#include <stdio.h>
#include <ncurses.h>
#include <strings.h>
#include <stdbool.h>
#include "cursehang.h"

// DO NOT WRITE PAST 23, 79
// TO BE COMPILED WITH -lncurses

int main(void)
{
	// TODO FIND DICTIONARY, PULL RANDOM WORD FROM DICT AND SET
	char word[] = "twice";
	int wLen = strlen(word);
	bool win = false;

	// INIT WINDOW
	initscr();
	cbreak();
	noecho();

	// TODO; FUNCTION THIS
	// DRAW GALLOWS
	move(2, 25);
	addch(ACS_ULCORNER);
	hline(ACS_HLINE, 20);
	mvvline(3, 25, ACS_VLINE, 10);
	move(13, 22);
	hline(ACS_HLINE, 3);
	mvaddch(13, 25, ACS_BTEE);
	hline(ACS_HLINE, 25);

	// DISPLAY WORD LENGTH HINT
	move(15, 20);
	addstr("WORD:\t");
	for (int i = 0; i < wLen; i++)
	{
		// addch(95);
		// addch(32);
		addstr("_ ");
	}

	// SETTING POS FOR ANSWER
	int yPos, xPos;
	move(16, 20);
	addstr("GUESS:\t");
	getyx(stdscr, yPos, xPos);

	do
	{
		move(yPos, xPos);
		char* answer = turn();
		int ansLen = strlen(answer);

		// mvprintw(23, 79, "%d", ansLen); PRINTS LENGTH OF ANSWER, TO DELETE
		// getch();
		if (ansLen == wLen && strcmp(word, answer) == 0)
		{
			win = true;
			break;
		}
		else if (ansLen > 1)
		{
			move(yPos, xPos);
			addstr("wrong!              ");
			getch();
			move(yPos, xPos);
			for (int i = 0; i < 20; i++)
			{
				delch();
			}
			continue;
		} else {
			// lette check function goes here!
		}
		move(yPos, xPos);
		addstr("shouldnt be here!");
	} while (win == false);

	clear();
	mvaddstr(0, 0, "You Win!");
	getch();

	// clear();
	// mvaddstr(0, 0, "exiting");
	// getch();

	endwin();
	return 0;
}
