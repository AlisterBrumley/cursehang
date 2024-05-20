#include <stdio.h>
#include <ncurses.h>
#include <strings.h>

int main(void)
{
	char word[] = "twice";
	char input[15];
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
	for (int i = 0; i < wLen; i++)
	{
		addch(95);
		addch(32);
	}

	getstr(input);
	int inLen = strlen(input);
	if (strcmp(word, input) == 0)
	{
		clear();
		mvaddstr(0, 0, "You Win!");
		getch();
		endwin();
		return 0;
	}

	for (int i = 0; i < inLen; i++)
	{
		for (int j = 0; j < wLen; j++)
		{
			if (input[i] == word[j])
			{
				// identifys letters correctly
			}
		}
		// might have to nested loop to search
		// check cs50 stuff, i think theres a solution there
	}

	clear();
	mvaddstr(0, 0, "exiting");
	getch();

	endwin();
	return 0;
}
