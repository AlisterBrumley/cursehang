// #include <stdio.h>
#include <ncurses.h>
// #include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

char *turn()
{
    int maxLength = 20;
    char temp;
    char *input = malloc(maxLength);

    for (int i = 0; i < maxLength; i++)
    {
        temp = getch();
        if (isalpha(temp) == 0)
        {
            break;
        }
        else if (isupper(temp) != 0)
        {
            temp = temp + 32;
        }
        // else if (temp < 65 || temp > 90 || temp < 97 || temp > 122)
        // {
        //     break;
        // }
        input[i] = temp;
        addch(temp);
    }

    return input;
}

// Checks for correct letters
// void otherfunc()
// {
//     int inLen = strlen(input);
//     for (int i = 0; i < inLen; i++)
//     {
//         for (int j = 0; j < wLen; j++)
//         {
//             if (input[i] == word[j])
//             {
//                 // identifys letters correctly
//             }
//         }
//         // might have to nested loop to search
//         // check cs50 stuff, i think theres a solution there
//     }
// }