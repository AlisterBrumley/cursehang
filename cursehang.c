#include <stdio.h>
#include <ncurses.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "cursehang.h"

// DO NOT WRITE PAST 23, 79
// TO BE COMPILED WITH -lncurses

struct pos
{
	int y;
	int x;
};

int main(void)
{
	// TODO FIND DICTIONARY, PULL RANDOM WORD FROM DICT AND SET

	// VARIABLE SETTNG
	int maxLength = 20;
	char word[] = "twicet";
	int wLen = strlen(word);
	int correct = 0;
	bool win = false;

	// draw base game setup
	initialize();
	draw_gallows();

	// DISPLAY WORD LENGTH HINT
	move(15, 20);
	addstr("WORD:\t");
	struct pos wPos;
	getyx(stdscr, wPos.y, wPos.x);
	for (int i = 0; i < wLen; i++)
	{
		addstr("_ ");
	}

	// SETTING POS FOR ANSWER
	// int gPos.y, gPos.x;
	move(16, 20);
	addstr("GUESS:\t");
	struct pos gPos;
	getyx(stdscr, gPos.y, gPos.x);

	// game loop
	do
	{
		move(gPos.y, gPos.x);
		char *guess = turn(maxLength);
		int guessLen = strlen(guess);

		// mvprintw(23, 79, "%d", guessLen); PRINTS LENGTH OF ANSWER, TO DELETE
		// getch();
		if (guessLen == wLen && strcmp(word, guess) == 0)
		{
			win = true;
		}
		else if (guessLen > 1)
		{
			wrong_word(gPos);
			clear_entry(gPos, maxLength);
		}
		else
		{
			correct += letter_check(wPos, guess, word, wLen);
			clear_entry(gPos, maxLength);

			// TODO
			// FUNCTION THIS
			if (correct == wLen)
			{
				win = true;
			}
		}

		free(guess);
	} while (win == false);

	clear();
	mvaddstr(0, 0, "You Win!");
	getch();

	endwin();
	return 0;
}

// turn input and update loop
char *turn(wordLength)
{
	// inputs char, if valid add to arr
	char input;
	char *inputArr = malloc(wordLength);

	for (int i = 0; i < wordLength; i++)
	{
		input = getch();
		// TODO
		// NEED TO ADD BACKSPACES
		if (isalpha(input) == 0)
		{
			// if non-letter, break to submit input
			break;
		}
		else if (isupper(input) != 0)
		{
			// to lower
			input = input + 32;
		}
		inputArr[i] = input;
		addch(input);
	}

	return inputArr;
}

// runs when incorrect word is submitted and clears
void wrong_word(struct pos gPos)
{
	char wrong[] = "wrong!              ";

	move(gPos.y, gPos.x);
	addstr(wrong);
	refresh();
	napms(1000);
	// NEED TO HALT INPUT FOR NAP!
}

// TO DO'ING
// checks letters
int letter_check(struct pos wPos, char *guess, char *word, int wordLen)
{
	int letterMatch = 0;
	for (int j = 0; j < wordLen; j++)
	{
		// figures position of letter in hint
		int letterXpos = wPos.x + j * 2;

		// adds letter in hint
		if (*guess == word[j])
		{
			move(wPos.y, letterXpos);
			addch(*guess);
			letterMatch++;
		}
	}

	return letterMatch;
}

// clears entry space
void clear_entry(struct pos gPos, int maximumLength)
{
	move(gPos.y, gPos.x);
	for (int i = 0; i < maximumLength; i++)
	{
		delch();
	}
}

void initialize(void)
{
	initscr();
	cbreak();
	noecho();
}

void draw_gallows()
{
	move(2, 25);
	addch(ACS_ULCORNER);
	hline(ACS_HLINE, 20);
	mvvline(3, 25, ACS_VLINE, 10);
	move(13, 22);
	hline(ACS_HLINE, 3);
	mvaddch(13, 25, ACS_BTEE);
	hline(ACS_HLINE, 25);
}