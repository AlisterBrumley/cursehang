#include <ncurses.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "turn.h"
#include "backspace.h"

// turn input and update loop
char *turn(int wordLength)
{
	// inputs char, if valid add to arr
	int input;
	int inLength = 0;
	char *inputArr = calloc(wordLength, sizeof(char));
	int i = 0;

	// input loop
	while (inLength < wordLength)
	{
		input = getch();
		if (i > 0 && (input == 13 || input == 10))
		{
			break;
		}
		else if (i > 0 && (input == 8 || input == 127 || input == KEY_BACKSPACE))
		{
			backspace();
			i--;
			inputArr[i] = 0;
			continue;
		}
		else if (isalpha(input) == 0)
		{
			continue;
		}
		else if (isupper(input) != 0)
		{
			// to lower
			input += 32;
		}
		else
		{
			inputArr[i] = input;
			inLength = strlen(inputArr);
			addch(input);
			i++;
		}
	}

	return inputArr;
}