#include <ncurses.h>
#include "gamehelpers.h"
#include "structs.h"

// gives player responses
void response(pos gPos, char *message)
{
    move(gPos.y, gPos.x);
    addstr(message);
    refresh();
    // NEED TO HALT INPUT FOR NAP!
}

int letter_check(pos wPos, char *guess, char *word, int wordLen)
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

void clear_entry(pos gPos, int maximumLength)
{
    move(gPos.y, gPos.x);
    for (int i = 0; i < maximumLength; i++)
    {
        delch();
    }
}