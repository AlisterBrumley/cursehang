#include <stdio.h>
#include <ncurses.h>
#include <strings.h>

int main(void) {
	char word[] = "twice";
	int wLen = strlen(word);
	// int lineInt = 196;
	// int wLen = strlen(word);
	// DO NOT WRITE PAST 23, 79
	initscr();
	cbreak();
	noecho();

	// printw("lmao");
	move(2, 25);
	addch(ACS_ULCORNER);
	hline(ACS_HLINE, 20);
	mvvline(3, 25, ACS_VLINE, 10);
	move(13, 22);
	hline(ACS_HLINE, 3);
	mvaddch(13, 25, ACS_BTEE);
	hline(ACS_HLINE, 25);

	move(15, 20);
	for(int i = 0; i < wLen; i++) {
		addch(95);
		addch(32);
	}

	getch();
	clear();
	mvaddstr(0, 0, "exiting");
	getch();
	
	endwin();
	return 0;
}
