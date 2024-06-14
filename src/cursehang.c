#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "cursehang.h"
#include "cursehelpers.h"
#include "gamehelpers.h"
#include "picker.h"
#include "structs.h"
#include "turn.h"
#include "hanging.h"

// DO NOT WRITE PAST 23, 79
// TO BE COMPILED WITH -lncurses
int main(void)
{
	// VARIABLE SETTNG
	int gCorrect = 0;
	int gIncorrect = 0;
	pos wPos;			 // positon staring after WORD:
	pos gPos;			 // positon staring after GUESS:
	pos mPos;			 // positon under guess for messages
	pos hPos;			 // positon of current hanged man // MOVED TO HANGING.C
	pos dPos;			 // DEBUG POS
	dPos.y = 23;		 // last row on standard terminal
	dPos.x = 0;			 // first column on standard terminal
	char gAlready[26] = {// input guessed letters in order when used, skips looping through array
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0};

	// DRAW BASIC SETUP
	initialize();
	draw_gallows();

	// SET WORD
	char *word = word_picker();
	// word = "twice"; // 						// TEST: TO DELETE!!
	int wLen = strlen(word);

	// DISPLAY WORD LENGTH HINT
	move(15, 20);
	addstr("WORD:\t");
	getyx(stdscr, wPos.y, wPos.x);
	for (int i = 0; i < wLen; i++)
	{
		addstr("_ ");
	}

	// DISPLAY GUESS TEXT ENTRY
	move(16, 20);
	addstr("GUESS:\t");
	getyx(stdscr, gPos.y, gPos.x);
	mPos.y = gPos.y + 1;
	mPos.x = gPos.x;

	// GAME LOOP
	do
	{
		move(gPos.y, gPos.x);		   // setting pos
		int oldCorrect = gCorrect;	   // for checks
		curs_set(1);				   // unhide cursor
		char *guess = turn(maxLength); // user input
		int gLen = strlen(guess);
		int aIndex = guess[0] - alphaShift; // takes guesses in lower case letters, and aligns them to order in alphabet

		clear_entry(gPos, maxLength);
		// if guess is gCorrect word
		if (gLen == wLen && strcmp(word, guess) == 0)
		{
			gCorrect = wLen;
		}
		// if guess was an incorrect word
		else if (gLen > 1)
		{
			response(mPos, "incorrect word!");
		}
		// if letter was already tried
		else if (*guess == gAlready[aIndex])
		{
			response(mPos, "already tried!");
		}
		// if single letter guess
		else
		{
			gAlready[aIndex] = *guess;
			int result = letter_check(wPos, guess, word, wLen);
			if (result == 0)
			{
				response(mPos, "incorrect letter!");
			}
			else
			{
				gCorrect += result;
			}
		}

		if (oldCorrect == gCorrect)
		{
			// DRAW HANGED MAN
			curs_set(0); //hide cursor
			hang(gIncorrect);
			napms(1000);
			gIncorrect++;
		}

		free(guess);
		guess = NULL;
		clear_entry(mPos, maxLength);
		move(gPos.y, gPos.x);
	} while (gCorrect != wLen && gIncorrect < maxWrong);

	curs_set(0);
	if (gCorrect == wLen)
	{
		clear();
		mvaddstr(0, 0, "You Win!");
		mvaddstr(1, 0, "Press any key to exit!");
	}
	else if (gIncorrect == maxWrong)
	{
		napms(1000); // extra delay as game ends after this
		clear();
		mvaddstr(0, 0, "You Lose!");
		mvprintw(1, 0, "The correct answer was '%s'", word);
		mvaddstr(2, 0, "Press any key to exit!");
	}
	else
	{
		clear();
		mvaddstr(0, 0, "Uh Oh! You shouldn't be here!");
		mvaddstr(1, 0, "The game broke, please report what happened as a bug!");
		mvprintw(2, 0, "The correct answer was '%s'", word);
		mvaddstr(3, 0, "Press any key to exit!");
	}

	getch();
	endwin();
	return 0;
}
