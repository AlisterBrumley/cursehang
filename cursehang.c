#include <stdio.h>
#include <ncurses.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "cursehang.h"

// DO NOT WRITE PAST 23, 79
// TO BE COMPILED WITH -lncurses

int main(void)
{
	// TODO FIND DICTIONARY, PULL RANDOM WORD FROM DICT AND SET

	// VARIABLE SETTNG
	int maxLength = 20;
	char word[] = "twicet";
	int wLen = strlen(word);
	int correct = 0;
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
	int wordYpos, wordXpos;
	getyx(stdscr, wordYpos, wordXpos);
	for (int i = 0; i < wLen; i++)
	{
		addstr("_ ");
	}

	// SETTING POS FOR ANSWER
	int guessYpos, guessXpos;
	move(16, 20);
	addstr("GUESS:\t");
	getyx(stdscr, guessYpos, guessXpos);

	// game loop
	do
	{
		move(guessYpos, guessXpos);
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
			wrong_word(guessYpos, guessXpos);
			clear_entry(guessYpos, guessXpos, maxLength);
		}
		else
		{
			correct += letter_check(wordYpos, wordXpos, guess, word, wLen);
			clear_entry(guessYpos, guessXpos, maxLength);

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
void wrong_word(guessYpos, guessXpos)
{
	char wrong[] = "wrong!              ";

	move(guessYpos, guessXpos);
	addstr(wrong);
	refresh();
	napms(5000);
	// NEED TO HALT INPUT FOR NAP!
}

// TO DO'ING
// checks letters
int letter_check(int wordYpos, int wordXpos, char *guess, char *word, int wordLen)
{
	int letterMatch = 0;
	for (int j = 0; j < wordLen; j++)
	{
		// figures position of letter in hint
		int letterXpos = wordXpos + j * 2;

		// adds letter in hint
		if (*guess == word[j])
		{
			move(wordYpos, letterXpos);
			addch(*guess);
			letterMatch++;
		}
	}

	return letterMatch;
}

// clears entry space
void clear_entry(guessYpos, guessXpos, maximumLength)
{
	move(guessYpos, guessXpos);
	for (int i = 0; i < maximumLength; i++)
	{
		delch();
	}
}