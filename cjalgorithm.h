/*
 *  cjalgorithm.m
 *  Typing
 *
 *  Created by Chris Johnson and Michael Dickens.
 * 
 */

#ifndef __CJALGORITHM_H__
#define __CJALGORITHM_H__

#include <limits.h>
#include "keyboard.h"

#define FILE_READ_NOT_HAPPEN -100
#define IGNORED_ALPHAS "zxjq"
struct ThreadArg {
	Keyboard bestk;
    Keyboard bestKeyboardsThread[MAX_TOP_KEYBOARDS];

	int numRounds;
    double chanceToUsePreviousLayout;
    int numberOfSwaps;
    
	time_t startTime;
	
	/* Indicates that the subroutine should keep creating new threads until 
	 * this reaches 0.
	 */
	int numThreads;
	
	/* Indicates whether the current thread is done running. */
	int isFinished;
};

int64_t prevBestFitness[MAX_TOP_KEYBOARDS];
int64_t trackImprovement[MAX_TOP_KEYBOARDS];
int nextTopKeyboard;
int numPurges;
int cycleNumber;
time_t globalStartTime;
time_t timeLastBestKeyboard;
time_t lastPrintTime;

int isSameLayout(Keyboard *, Keyboard *);

void runAlgorithm();
void * runThreadsRec(void *arg);

void greatToBest(void *arg, int numRounds);
void * greatToBestThreadRec(void *arg);
void greatToBestBruteForce(Keyboard *k);

void tryPermutations(Keyboard *bestk, Keyboard *k, int *origLocs, int *locs,
                    int length, int index);

int64_t anneal(Keyboard *k, int lockins[][2], size_t lockin_length);
int64_t improveLayout(int64_t evaluationToBeat, Keyboard *k, 
	int lockins[][2], size_t lockin_length);
int smartMutate(int swapIndices[][2], Keyboard *k, int numberOfSwaps, int ignoreAlphas);

void initThreadArg(struct ThreadArg *arg);
void copyThreadArg(struct ThreadArg *dest, struct ThreadArg *src);
void saveTopKeyboard(Keyboard *k, Keyboard *someBestKeyboards);
void purgeOutdatedKeyboards();
void selectNextKeyboard(void *arg, Keyboard *k);

#endif