# ncurses hangman

### Hangman, made with ncurses

A simple game, that picks a word, and you can guess what it is!<br>
You have 7 guesses before it completes the hangman.<br>
<br>
The words are picked from the BASIC English dictionary, which contains 850 words that should be known by most english speakers.

## BUILDING

**You will have to check if you have `ncurses` before you build!**<br>
To compile on Mac on Linux, simply run `make`<br>
Windows with mingw64/gcc should also just work with `make`<br>
Otherwise for manual compiling, make sure to compile with `-lncurses`!
