#include <stdio.h>
#include <ncurses.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "cursehang.h"

// for positions of elements on screen
struct pos
{
	int y;
	int x;
};

// DO NOT WRITE PAST 23, 79
// TO BE COMPILED WITH -lncurses
int main(void)
{
	// VARIABLE SETTNG
	int maxLength = 20;
	int correct = 0;
	bool win = false;
	struct pos wPos; // positon staring after WORD:
	struct pos gPos; // positon staring after GUESS:
	struct pos hPos; // positon of current hanged man
	struct pos dPos; // DEBUG POS
	dPos.y = 23;
	dPos.x = 0;
	char alreadyGuessed[26] = {// input guessed letters in order when used, skips looping through array
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
	word = "twice"; // 						// TEST: TO DELETE!!
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

	// GAME LOOP
	do
	{
		move(gPos.y, gPos.x);		   // setting pos
		char *guess = turn(maxLength); // user input
		int gLen = strlen(guess);
		int gIndex = guess[0] - 97; // takes guesses in lower case letters, and aligns them to order in alphabet

		clear_entry(gPos, maxLength);
		// if guess is correct word
		if (gLen == wLen && strcmp(word, guess) == 0)
		{
			free(guess);
			break;
		}
		// if guess was an incorrect word
		else if (gLen > 1)
		{
			response(gPos, "incorrect word!");
			clear_entry(gPos, maxLength);
		}
		// if guess was already tried
		else if (*guess == alreadyGuessed[gIndex])
		{
			response(gPos, "already tried!");
			clear_entry(gPos, maxLength);
		}
		// if new single letter guess
		else
		{
			alreadyGuessed[gIndex] = *guess;
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
		guess = NULL;
	} while (win == false);

	clear();
	mvaddstr(0, 0, "You Win!");
	getch();

	endwin();
	return 0;
}

// init ncurses
void initialize(void)
{
	initscr();
	cbreak();
	noecho();
}

// draw gallows for game start
void draw_gallows()
{
	// top bar
	move(2, 25);
	addch(ACS_ULCORNER);
	hline(ACS_HLINE, 20);
	// pillar
	move(3, 25);
	vline(ACS_VLINE, 10);
	// floor
	move(13, 22);
	hline(ACS_HLINE, 3);
	move(13, 25);
	addch(ACS_BTEE);
	hline(ACS_HLINE, 25);
}

// turn input and update loop
char *turn(int wordLength)
{
	// inputs char, if valid add to arr
	char input;
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
		else if (i > 0 && (input == 8 || input == 127))
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

// runs when response word is submitted and clears
void response(struct pos gPos, char *message)
{
	move(gPos.y, gPos.x);
	addstr(message);
	refresh();
	napms(1000);
	// NEED TO HALT INPUT FOR NAP!
}

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

void backspace()
{
	int y, x;
	getyx(stdscr, y, x);
	mvdelch(y, (x - 1));
}

char *word_picker()
{
	// dictionary of words to use
	// im sorry. im so, so, sorry.
	char *dictionary[] = {"a",
						  "able",
						  "about",
						  "account",
						  "acid",
						  "across",
						  "act",
						  "addition",
						  "adjustment",
						  "advertisement",
						  "after",
						  "again",
						  "against",
						  "agreement",
						  "air",
						  "all",
						  "almost",
						  "among",
						  "amount",
						  "amusement",
						  "and",
						  "angle",
						  "angry",
						  "animal",
						  "answer",
						  "ant",
						  "any",
						  "apparatus",
						  "apple",
						  "approval",
						  "arch",
						  "argument",
						  "arm",
						  "army",
						  "art",
						  "as",
						  "at",
						  "attack",
						  "attempt",
						  "attention",
						  "attraction",
						  "authority",
						  "automatic",
						  "awake",
						  "baby",
						  "back",
						  "bad",
						  "bag",
						  "balance",
						  "ball",
						  "band",
						  "base",
						  "basin",
						  "basket",
						  "bath",
						  "be",
						  "beautiful",
						  "because",
						  "bed",
						  "bee",
						  "before",
						  "behavior",
						  "belief",
						  "bell",
						  "bent",
						  "berry",
						  "between",
						  "bird",
						  "birth",
						  "bit",
						  "bite",
						  "bitter",
						  "black",
						  "blade",
						  "blood",
						  "blow",
						  "blue",
						  "board",
						  "boat",
						  "body",
						  "boiling",
						  "bone",
						  "book",
						  "boot",
						  "bottle",
						  "box",
						  "boy",
						  "brain",
						  "brake",
						  "branch",
						  "brass",
						  "bread",
						  "breath",
						  "brick",
						  "bridge",
						  "bright",
						  "broken",
						  "brother",
						  "brown",
						  "brush",
						  "bucket",
						  "building",
						  "bulb",
						  "burn",
						  "burst",
						  "business",
						  "but",
						  "butter",
						  "button",
						  "by",
						  "cake",
						  "camera",
						  "canvas",
						  "card",
						  "care",
						  "carriage",
						  "cart",
						  "cat",
						  "cause",
						  "certain",
						  "chain",
						  "chalk",
						  "chance",
						  "change",
						  "cheap",
						  "cheese",
						  "chemical",
						  "chest",
						  "chief",
						  "chin",
						  "church",
						  "circle",
						  "clean",
						  "clear",
						  "clock",
						  "cloth",
						  "cloud",
						  "coal",
						  "coat",
						  "cold",
						  "collar",
						  "color",
						  "comb",
						  "come",
						  "comfort",
						  "committee",
						  "common",
						  "company",
						  "comparison",
						  "competition",
						  "complete",
						  "complex",
						  "condition",
						  "connection",
						  "conscious",
						  "control",
						  "cook",
						  "copper",
						  "copy",
						  "cord",
						  "cork",
						  "cotton",
						  "cough",
						  "country",
						  "cover",
						  "cow",
						  "crack",
						  "credit",
						  "crime",
						  "cruel",
						  "crush",
						  "cry",
						  "cup",
						  "current",
						  "curtain",
						  "curve",
						  "cushion",
						  "cut",
						  "damage",
						  "danger",
						  "dark",
						  "daughter",
						  "day",
						  "dead",
						  "dear",
						  "death",
						  "debt",
						  "decision",
						  "deep",
						  "degree",
						  "delicate",
						  "dependent",
						  "design",
						  "desire",
						  "destruction",
						  "detail",
						  "development",
						  "different",
						  "digestion",
						  "direction",
						  "dirty",
						  "discovery",
						  "discussion",
						  "disease",
						  "disgust",
						  "distance",
						  "distribution",
						  "division",
						  "do",
						  "dog",
						  "door",
						  "doubt",
						  "down",
						  "drain",
						  "drawer",
						  "dress",
						  "drink",
						  "driving",
						  "drop",
						  "dry",
						  "dust",
						  "ear",
						  "early",
						  "earth",
						  "east",
						  "edge",
						  "education",
						  "effect",
						  "egg",
						  "elastic",
						  "electric",
						  "end",
						  "engine",
						  "enough",
						  "equal",
						  "error",
						  "even",
						  "event",
						  "ever",
						  "every",
						  "example",
						  "exchange",
						  "existence",
						  "expansion",
						  "experience",
						  "expert",
						  "eye",
						  "face",
						  "fact",
						  "fall",
						  "false",
						  "family",
						  "far",
						  "farm",
						  "fat",
						  "father",
						  "fear",
						  "feather",
						  "feeble",
						  "feeling",
						  "female",
						  "fertile",
						  "fiction",
						  "field",
						  "fight",
						  "finger",
						  "fire",
						  "first",
						  "fish",
						  "fixed",
						  "flag",
						  "flame",
						  "flat",
						  "flight",
						  "floor",
						  "flower",
						  "fly",
						  "fold",
						  "food",
						  "foolish",
						  "foot",
						  "for",
						  "force",
						  "fork",
						  "form",
						  "forward",
						  "fowl",
						  "frame",
						  "free",
						  "frequent",
						  "friend",
						  "from",
						  "front",
						  "fruit",
						  "full",
						  "future",
						  "garden",
						  "general",
						  "get",
						  "girl",
						  "give",
						  "glass",
						  "glove",
						  "go",
						  "goat",
						  "gold",
						  "good",
						  "government",
						  "grain",
						  "grass",
						  "gray",
						  "great",
						  "green",
						  "grip",
						  "group",
						  "growth",
						  "guide",
						  "gun",
						  "hair",
						  "hammer",
						  "hand",
						  "hanging",
						  "happy",
						  "harbor",
						  "hard",
						  "harmony",
						  "hat",
						  "hate",
						  "have",
						  "he",
						  "head",
						  "healthy",
						  "hearing",
						  "heart",
						  "heat",
						  "help",
						  "here",
						  "high",
						  "history",
						  "hole",
						  "hollow",
						  "hook",
						  "hope",
						  "horn",
						  "horse",
						  "hospital",
						  "hour",
						  "house",
						  "how",
						  "humor",
						  "I",
						  "ice",
						  "idea",
						  "if",
						  "ill",
						  "important",
						  "impulse",
						  "in",
						  "increase",
						  "industry",
						  "ink",
						  "insect",
						  "instrument",
						  "insurance",
						  "interest",
						  "invention",
						  "iron",
						  "island",
						  "jelly",
						  "jewel",
						  "join",
						  "journey",
						  "judge",
						  "jump",
						  "keep",
						  "kettle",
						  "key",
						  "kick",
						  "kind",
						  "kiss",
						  "knee",
						  "knife",
						  "knot",
						  "knowledge",
						  "land",
						  "language",
						  "last",
						  "late",
						  "laugh",
						  "law",
						  "lead",
						  "leaf",
						  "learning",
						  "leather",
						  "left",
						  "leg",
						  "let",
						  "letter",
						  "level",
						  "library",
						  "lift",
						  "light",
						  "like",
						  "limit",
						  "line",
						  "linen",
						  "lip",
						  "liquid",
						  "list",
						  "little",
						  "living",
						  "lock",
						  "long",
						  "look",
						  "loose",
						  "loss",
						  "loud",
						  "love",
						  "low",
						  "machine",
						  "make",
						  "male",
						  "man",
						  "manager",
						  "map",
						  "mark",
						  "market",
						  "married",
						  "mass",
						  "match",
						  "material",
						  "may",
						  "meal",
						  "measure",
						  "meat",
						  "medical",
						  "meeting",
						  "memory",
						  "metal",
						  "middle",
						  "military",
						  "milk",
						  "mind",
						  "mine",
						  "minute",
						  "mist",
						  "mixed",
						  "money",
						  "monkey",
						  "month",
						  "moon",
						  "morning",
						  "mother",
						  "motion",
						  "mountain",
						  "mouth",
						  "move",
						  "much",
						  "muscle",
						  "music",
						  "nail",
						  "name",
						  "narrow",
						  "nation",
						  "natural",
						  "near",
						  "necessary",
						  "neck",
						  "need",
						  "needle",
						  "nerve",
						  "net",
						  "new",
						  "news",
						  "night",
						  "no",
						  "noise",
						  "normal",
						  "north",
						  "nose",
						  "not",
						  "note",
						  "now",
						  "number",
						  "nut",
						  "observation",
						  "of",
						  "off",
						  "offer",
						  "office",
						  "oil",
						  "old",
						  "on",
						  "only",
						  "open",
						  "operation",
						  "opinion",
						  "opposite",
						  "or",
						  "orange",
						  "order",
						  "organization",
						  "ornament",
						  "other",
						  "out",
						  "oven",
						  "over",
						  "owner",
						  "page",
						  "pain",
						  "paint",
						  "paper",
						  "parallel",
						  "parcel",
						  "part",
						  "past",
						  "paste",
						  "payment",
						  "peace",
						  "pen",
						  "pencil",
						  "person",
						  "physical",
						  "picture",
						  "pig",
						  "pin",
						  "pipe",
						  "place",
						  "plane",
						  "plant",
						  "plate",
						  "play",
						  "please",
						  "pleasure",
						  "plow",
						  "pocket",
						  "point",
						  "poison",
						  "polish",
						  "political",
						  "poor",
						  "porter",
						  "position",
						  "possible",
						  "pot",
						  "potato",
						  "powder",
						  "power",
						  "present",
						  "price",
						  "print",
						  "prison",
						  "private",
						  "probable",
						  "process",
						  "produce",
						  "profit",
						  "property",
						  "prose",
						  "protest",
						  "public",
						  "pull",
						  "pump",
						  "punishment",
						  "purpose",
						  "push",
						  "put",
						  "quality",
						  "question",
						  "quick",
						  "quiet",
						  "quite",
						  "rail",
						  "rain",
						  "range",
						  "rat",
						  "rate",
						  "ray",
						  "reaction",
						  "reading",
						  "ready",
						  "reason",
						  "receipt",
						  "record",
						  "red",
						  "regret",
						  "regular",
						  "relation",
						  "religion",
						  "representative",
						  "request",
						  "respect",
						  "responsible",
						  "rest",
						  "reward",
						  "rhythm",
						  "rice",
						  "right",
						  "ring",
						  "river",
						  "road",
						  "rod",
						  "roll",
						  "roof",
						  "room",
						  "root",
						  "rough",
						  "round",
						  "rub",
						  "rule",
						  "run",
						  "sad",
						  "safe",
						  "sail",
						  "salt",
						  "same",
						  "sand",
						  "say",
						  "scale",
						  "school",
						  "science",
						  "scissors",
						  "screw",
						  "sea",
						  "seat",
						  "second",
						  "secret",
						  "secretary",
						  "see",
						  "seed",
						  "seem",
						  "selection",
						  "self",
						  "send",
						  "sense",
						  "separate",
						  "serious",
						  "servant",
						  "sex",
						  "shade",
						  "shake",
						  "shame",
						  "sharp",
						  "sheep",
						  "shelf",
						  "ship",
						  "shirt",
						  "shock",
						  "shoe",
						  "short",
						  "shut",
						  "side",
						  "sign",
						  "silk",
						  "silver",
						  "simple",
						  "sister",
						  "size",
						  "skin",
						  "skirt",
						  "sky",
						  "sleep",
						  "slip",
						  "slope",
						  "slow",
						  "small",
						  "smash",
						  "smell",
						  "smile",
						  "smoke",
						  "smooth",
						  "snake",
						  "sneeze",
						  "snow",
						  "so",
						  "soap",
						  "society",
						  "sock",
						  "soft",
						  "solid",
						  "some",
						  "son",
						  "song",
						  "sort",
						  "sound",
						  "soup",
						  "south",
						  "space",
						  "spade",
						  "special",
						  "sponge",
						  "spoon",
						  "spring",
						  "square",
						  "stage",
						  "stamp",
						  "star",
						  "start",
						  "statement",
						  "station",
						  "steam",
						  "steel",
						  "stem",
						  "step",
						  "stick",
						  "sticky",
						  "stiff",
						  "still",
						  "stitch",
						  "stocking",
						  "stomach",
						  "stone",
						  "stop",
						  "store",
						  "story",
						  "straight",
						  "strange",
						  "street",
						  "stretch",
						  "strong",
						  "structure",
						  "substance",
						  "such",
						  "sudden",
						  "sugar",
						  "suggestion",
						  "summer",
						  "sun",
						  "support",
						  "surprise",
						  "sweet",
						  "swim",
						  "system",
						  "table",
						  "tail",
						  "take",
						  "talk",
						  "tall",
						  "taste",
						  "tax",
						  "teaching",
						  "tendency",
						  "test",
						  "than",
						  "that",
						  "the",
						  "then",
						  "theory",
						  "there",
						  "thick",
						  "thin",
						  "thing",
						  "this",
						  "though",
						  "thought",
						  "thread",
						  "throat",
						  "through",
						  "thumb",
						  "thunder",
						  "ticket",
						  "tight",
						  "till",
						  "time",
						  "tin",
						  "tired",
						  "to",
						  "toe",
						  "together",
						  "tomorrow",
						  "tongue",
						  "tooth",
						  "top",
						  "touch",
						  "town",
						  "trade",
						  "train",
						  "transport",
						  "tray",
						  "tree",
						  "trick",
						  "trouble",
						  "trousers",
						  "true",
						  "turn",
						  "twist",
						  "umbrella",
						  "under",
						  "unit",
						  "up",
						  "use",
						  "value",
						  "verse",
						  "very",
						  "vessel",
						  "view",
						  "violent",
						  "voice",
						  "waiting",
						  "walk",
						  "wall",
						  "war",
						  "warm",
						  "wash",
						  "waste",
						  "watch",
						  "water",
						  "wave",
						  "wax",
						  "way",
						  "weather",
						  "week",
						  "weight",
						  "well",
						  "west",
						  "wet",
						  "wheel",
						  "when",
						  "where",
						  "while",
						  "whip",
						  "whistle",
						  "white",
						  "who",
						  "why",
						  "wide",
						  "will",
						  "wind",
						  "window",
						  "wine",
						  "wing",
						  "winter",
						  "wire",
						  "wise",
						  "with",
						  "woman",
						  "wood",
						  "wool",
						  "word",
						  "work",
						  "worm",
						  "wound",
						  "writing",
						  "wrong",
						  "year",
						  "yellow",
						  "yes",
						  "yesterday",
						  "you",
						  "young"};

	int dLen = sizeof(dictionary) / sizeof(dictionary[0]);

	srand(time(NULL));
	int rng = rand() % dLen;
	return dictionary[rng];
}