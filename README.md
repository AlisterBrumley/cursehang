# ncurses hangman

### Hangman, made with ncurses

A simple game, that picks a word, and you can geuss what it is!<br>
You have 7 geusses before it completes the hangman.<br>
<br>
I used Charles Kay Ogden's BASIC English dictionary, which contains 850 words that should be known by most english speakers.

## BUILDING

**You will have to check if you have ncurses before you build!**<br>
To compile on Mac on Linux, simply run `make`<br>
I have not currently tested on Windows, but the makefile is simple and easily modifiable<br>
Otherwise for manual compiling, make sure to compile with `-lncurses`!
