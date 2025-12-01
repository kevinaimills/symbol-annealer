/*
 *  tools.h
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__
 
#include "values.h"

#define streq(str1, str2) (strcmp(str1, str2) == 0)
#define streqn(str1, str2, n) (strncmp(str1, str2, n) == 0)

#define ASCII_SHIFT 14
 
#define DI_LEN_MAX 5000
#define TRI_LEN_MAX 12000
#define MON_LEN_MAX 200

#define ERROR_RATE_PERCENT 2
#define MAX_TOP_KEYBOARDS 25

#define MONOGRAPHFILE "allChars.txt"
#define DIGRAPH_FILE "allDigraphs.txt"
#define TRIGRAPH_FILE "allTrigraphs.txt"
#define DATA_FOLDER "data/"
#define DATA_FOLDER_TEXT_ONLY "data/textOnly/"

/* Global variable declarations */

int64_t totalMon;
int64_t totalDi;
int64_t totalTri;
int monLen, diLen, triLen;

struct Monograph {
    char key;
    int64_t value;
};

struct Digraph {
    char key[2];
    int64_t value;
};

struct Trigraph {
    char key[3];
    int64_t value;
};

struct NGraph {
    char *key;
    int64_t value;
};

struct Monograph monographs[MON_LEN_MAX];
struct Digraph digraphs[DI_LEN_MAX];
struct Trigraph trigraphs[TRI_LEN_MAX];

/* Constant declarations */

#define LEFT 0
#define RIGHT 1

#define PINKY 0
#define RING 1
#define MIDDLE 2
#define INDEX 3
#define THUMB 4

/* Reduces monValues and diValues so as to prevent integer overflow. */
#define DIVISOR 5000

/* These are guaranteed to hold a standard QWERTY layout. */

#define ALL_SYMBOLS ",.;'?!:\"-_/\\|=+`~[]()<>{}@#$%^&*"
#define ALL_LETTERS "abcdefghijklmnopqrstuvwxyz"
// #define ALL_SYMBOLS "?!-_/\\|=+`~[]()<>{}@#$%^&*;:'\",."
// #define DEFAULT_LAYOUT "qwfpbjluy;arstgmneiozxcdvkh,./"
// #define DEFAULT_LAYOUT "qwertyuiopasdfghjkl;zxcvbnm,./"
// #define DEFAULT_LAYOUT "xycpbXwouqnhstgXreiavfmdkjlXXz"
// #define DEFAULT_LAYOUT "qycpbXwoujnhstgXreiavfmdkzlXXx"
// #define DEFAULT_LAYOUT "xympbXwouqnhstgjreiavfcdkzlXXX"
// #define DEFAULT_LAYOUT "xycpbXwouqnhstgjreiavfmdkzlXXX"


#define DEFAULT_KEYBOARD_30 "xympbjwouqnhstg0reiavfcdkzl000XYMPBJWOUQNHSTG0REIAVFCDKZL0?!-_/\\|=+`~[]()<>{}@#$%^&*;:'\",."
// #define DEFAULT_KEYBOARD_30 "xympbjwouqnhstg;reiavfcdkzl',.XYMPBJWOUQNHSTG:REIAVFCDKZL\"?!-_/\\|=+`~[]()<>{}@#$%^&*123456"
// #define DEFAULT_KEYBOARD_30 "xympbjwouqnhstg;reiavfcdkzl',.000000000000000:00000000000\"?!-_/\\|=+`~[]()<>{}@#$%^&*123456"
// #define DEFAULT_KEYBOARD_30 "xympbjwouqnhstg;reiavfcdkzl',.-_/\\|=+`~[]()<>{}@#$%^&*123456XYMPBJWOUQNHSTG:REIAVFCDKZL\"?!"
//#define DEFAULT_KEYBOARD_30 "xympbjwouqnhstg;reiavfcdkzl',.\":-_/?\\|=+`~[]()<>{}!@#$%^&*12XYMPBJWOUQNHSTG3REIAVFCDKZL456"
//#define DEFAULT_KEYBOARD_30 "\\&|^[]()`<>{}~_$%/=*+!@#qwertyuiopasdfghjklzxcvbnmQWERTYUIOP"
//#define DEFAULT_KEYBOARD_30 "\\&|^[]()`<>{}~_$%-/=*+!@#.;,'\"qwertyuiopasdfghjklzxcvbnmQWER"

//qwertyuiopasdfghjklzxcvbnm,.;'QWERTYUIOPASDFGHJKLZXCVBNM?!:\"" 

//#define DEFAULT_KEYBOARD_30 "qwertyuiopasdfghjklzxcvbnm,.;'QWERTYUIOPASDFGHJKLZXCVBNM?!:\""
//#define DEFAULT_KEYBOARD_30 "qwertyuiopasdfghjkl;zxcvbnm,./QWERTYUIOPASDFGHJKL:ZXCVBNM<>?"
#define DEFAULT_KEYBOARD_STANDARD "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?"
#define DEFAULT_KEYBOARD_KINESIS "1234567890-\tqwertyuiop=asdfghjkl;'zxcvbnm,./`\\[]\n !@#$%^&*()_\tQWERTYUIOP+ASDFGHJKL:\"ZXCVBNM<>?~|{}\n "

#define CHECK_FILE_FOR_NULL(file, filename) \
	if ((file) == NULL) { \
		fprintf(stderr, "Unable to open file: %s\n", (filename)); \
		return 1; \
	}

char keysToInclude[200];

#define MAX_AESTHETIC_RULES 50

typedef struct ktype {
	char layout[KSIZE_MAX + 1]; /* The one extra character is set to '\0' so
								(layout) can be treated as a string. */ 
	char shiftedLayout[KSIZE_MAX + 1];
	char symbolLayer[KSIZE_MAX + 1];
	int swapCandidates[(KSIZE_MAX + 1) * 3];
	double aestheticPenalties[MAX_AESTHETIC_RULES];
	int nextAestheticRule;
	int numCans;	
	int64_t fingerUsage[FINGER_COUNT];
	int64_t fingerTravel[FINGER_COUNT];
	int64_t fitness;
	int64_t layerChange;
	int64_t distance;
	int64_t handTravel;
	int64_t handImbalance;
	int64_t fingerWork;
	int64_t fingerTravelWork;
	int64_t aesthetics;
	int64_t biLayerChange;
	int64_t inRoll;
	int64_t outRoll;
	int64_t sameHand;
	int64_t sameFinger;
	int64_t sameFingerMax;
	int64_t rowChange;
	int64_t homeJump;
	int64_t ringJump;
	int64_t toCenter;
	int64_t lateralStretch;
	int64_t halfScissor;
	int64_t fullScissor;
	int64_t biLayerSplit;
	int64_t triLayerChange;
	int64_t triSplitFinger;
	int64_t triInRoll;
	int64_t triOutRoll;
	int64_t triOneHand;
	int64_t triAlt;
	int64_t triRedirect;
	int64_t triHomeJump;
	int64_t halfScissorTri;
	int64_t fullScissorTri;
	int64_t lateralStretchTri;	
} Keyboard;


Keyboard nilKeyboard;
Keyboard bestKeyboards[MAX_TOP_KEYBOARDS];
void copyKeyboard(Keyboard *k, Keyboard *original);
void copyArray(int dest[], int src[], int length);
void printTime(time_t start);
void reverseLayout(char* str);

int initData();
void initKeyboardData();
int initTypingData();
int readDataFromFile(char *filePath, int numChars, int scalePercent);
int compileTypingData(char *outfileName, const char *filenames[], 
		int multipliers[], int length, int unit, int max);
int sortTypingData(char **keys, int *values, int left, int right);
int convertEscapeChar(int c);

/* Sort by values from highest to lowest.
 */
int cmpTrigraphsByValue(const void *one, const void *two);
int cmpDigraphsByValue(const void *one, const void *two);
int cmpMonographsByValue(const void *one, const void *two);
int cmpNGraphsByValue(const void *one, const void *two);
int cmpKeyboardsByFitness(const void *one, const void *two);

int sortMonographs(char keys[], int64_t values[], int left, int right);
int layerDiff(int layer0, int layer1);

struct VarInfo {
    const char *name; /* The name of the variable. */
    int *addr; /* A pointer to the variable itself. */
    const char *description;
};

#define VARIABLES_MAX_LEN 100
struct VarInfo variables[VARIABLES_MAX_LEN];
int variablesLength;

void initVariables();
int getValue(const char *name);
int setValue(char *str);

#define isBracket(c) (getMatchingBracket(c) != 0)
char getMatchingBracket(char c);

int keepShiftPair(char c);

char qwerty[30];

/* For each key, indicates which hand (LEFT or RIGHT) is responsible for typing 
 * that key.
 */
int hand[KSIZE_MAX];

/* For each key, indicates which finger (PINKY, RING, MIDDLE or INDEX) is 
 * responsible for typing that key.
 */
int finger[KSIZE_MAX];

/* Where 0 is pinky, -1 is left of pinky, ..., 3 is index, 4 is right of index.
 * Anything greater than 4 is thumb.
 */
int column[KSIZE_MAX];

/* For each key, indicates which row that key lies on. The top row is 0, 
 * the row below it is 1, the row below that is 2, etc.
 */
int row[KSIZE_MAX];

/* Indicates which row is the home row.
 */
int homeRow;

/* Indicates the index of the first number in the layout, assuming 
 * keepNumbers is TRUE.
 */
int firstNumberIndex;

/* For each key, indicates whether that key requires a reach to the center.
 */
int isCenter[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the outside.
 */
int isOutside[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the center OR 
 * a reach to the outside. This one is produced automatically from isCenter[] 
 * and isOutside[].
 */
int isCenterOrOutside[KSIZE_MAX];

/* For each key, indicates whether that key should be printed. Any place-holder 
 * key that does not actually exist on the keyboard should not be printed.
 */
int printable[KSIZE_MAX];

/* Lookup tables for calcRowChange(). Each row and column represents a finger.
 */
int rowChangeTableUp[5][5];
int rowChangeTableDown[5][5];


#endif
