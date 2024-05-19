#include <stdio.h>
#include <ncurses.h>
#include <strings.h>

int main(void) {
	char line = '-';
	int lineInt = 196;
	//int wLen = strlen(word);
	// DO NOT WRITE PAST 23, 79
	initscr();
	cbreak();
	noecho();

	printw("lmao");
	move(5, 5);
	//hline(line, 30);
	WINDOW *win = newwin(10,10,1,1);
	box(win, '*', '*');
    touchwin(win);
    wrefresh(win);
	getch();

	clear();
	mvaddstr(0, 0, "exiting");
	getch();
	
	endwin();
}
