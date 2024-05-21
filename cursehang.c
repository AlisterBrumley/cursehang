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

	// game loop
	do
	{
		move(yPos, xPos);
		char *guess = turn(maxLength);
		int guessLen = strlen(guess);

		// mvprintw(23, 79, "%d", guessLen); PRINTS LENGTH OF ANSWER, TO DELETE
		// getch();
		if (guessLen == wLen && strcmp(word, guess) == 0)
		{
			win = true;
			free(guess);
			break;
		}
		else if (guessLen > 1)
		{
			wrong_word(yPos, xPos);
			free(guess);
			clear_entry(yPos, xPos, maxLength);
			continue;
		}
		else
		{
			letter_check(yPos, xPos, guess, word, wLen);
			free(guess);
			clear_entry(yPos, xPos, maxLength);
			continue;
		}
		// free(guess);
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

// turn input and update loop
char *turn(wordLength)
{
	// inputs char, if valid add to arr
	char input;
	char *inputArr = malloc(wordLength);

	for (int i = 0; i < wordLength; i++)
	{
		input = getch();
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
		// else if (input < 65 || input > 90 || input < 97 || input > 122)
		// {
		//     break;
		// }
		inputArr[i] = input;
		addch(input);
	}

	return inputArr;
}

// runs when incorrect word is submitted and clears
void wrong_word(yPos, xPos)
{
	char wrong[] = "wrong!              ";

	move(yPos, xPos);
	addstr(wrong);
	getch();
}

// TO DO'ING
// checks letters
void letter_check(int yPos, int xPos, char *guess, char *word, int wordLen)
{
	int inLen = strlen(guess);
	for (int i = 0; i < inLen; i++)
	{
		for (int j = 0; j < wordLen; j++)
		{
			if (guess[i] == word[j])
			{
				// identifys letters correctly
				move(yPos, (xPos + 2));
				addstr("matches");
				getch();
			}
			else
			{
				move(yPos, (xPos + 2));
				addstr("no match");
				getch();
			}
		}
		// might have to nested loop to search
		// check cs50 stuff, i think theres a solution there
	}
}

void clear_entry(yPos, xPos, maximumLength)
{
	move(yPos, xPos);
	for (int i = 0; i < maximumLength; i++)
	{
		delch();
	}
}