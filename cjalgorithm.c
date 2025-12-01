/*
 *  cjalgorithm.c
 *  Typing
 * 
 *  Written by Michael Dickens and Chris Johnson.
 *    
 */

#include "cjalgorithm.h"

/*  
 * Runs a simple version of the algorithm without all the bells and whistles.
 * Only uses a single thread, and generally runs significantly slower than 
 * runAlgorithm(). 
 */ 
void runSimpleAlgorithm()
{
    Keyboard bestk, k;
    copyKeyboard(&bestk, &nilKeyboard);
    copyKeyboard(&k, &nilKeyboard);
    
    time_t startTime = time(NULL);
    time_t printTimeInterval = PRINT_TIME_INTERVAL;
    time_t timeOnPrint = startTime + printTimeInterval;
    
    int roundNum;
    for (roundNum = 0; ; ++roundNum) {
        initKeyboard(&k);
        anneal(&k, NULL, 0);
        
        if (k.fitness < bestk.fitness) {
            copyKeyboard(&bestk, &k);
            printPercentages(&bestk);
            printf("%d Rounds\n", roundNum);
            printTime(startTime);
            
            /* If a keyboard was just printed, don't print the time for
             * a while.
             */
            timeOnPrint = time(NULL) + printTimeInterval;
        } else if (time(NULL) >= timeOnPrint) {
            printf("%d Rounds\n", roundNum);
            printTime(startTime);
            timeOnPrint = time(NULL) + printTimeInterval;
            printTimeInterval = 1.5 * printTimeInterval + 1;
        }
    }
}

int isSameLayout(Keyboard *k1, Keyboard *k2) {
    
    int isSame = 1;
    int j = 0;

    if (keepAlphas && doSymbolLayer) {
        for (j = 0; j < k1->nextAestheticRule; j++) {
            if (abs(k1->aestheticPenalties[j] - k2->aestheticPenalties[j]) > k1->aestheticPenalties[j] 
            || abs(k1->aestheticPenalties[j] - k2->aestheticPenalties[j]) > k2->aestheticPenalties[j]) {
                isSame = 0;
                break;
            }
        }
    }

    char *layout1;
    char *layout2;

    for (j = 0; j < 3 && isSame == 1; j++) {

        if (j == 0) {
            layout1 = k1->layout;
            layout2 = k2->layout;
        } else if (j == 1) {
            layout1 = k1->shiftedLayout;
            layout2 = k2->shiftedLayout;
        } else if (j == 2) {
            layout1 = k1->symbolLayer;
            layout2 = k2->symbolLayer;
        }

        for (int i = 0; i < ksize && isSame == 1; i++) {
            // printf("\n%c %c", layout1[i], layout2[i]);
            if (layout1[i] != layout2[i] && 
                (
                    (i >= 10 && i < 20 && i != 14 && i != 15 && isalpha(layout1[i]))
                    ||
                    (!doSymbolLayer && !keepAlphas && !keepHomeRowLeft && !keepHomeRowRight &&
                        (
                            layout1[i] == 'e'
                            || layout1[i] == 't'
                            || layout1[i] == 'a'
                            || layout1[i] == 'o'
                            || layout1[i] == 'i'
                            || layout1[i] == 'n'
                            || layout1[i] == 's'
                            || layout1[i] == 'r'
                        )
                    )
                    ||
                    (!doSymbolLayer && !keepAlphas && (keepHomeRowLeft || keepHomeRowRight) && !(keepHomeRowLeft && keepHomeRowRight) &&
                        (
                            layout1[i] == 'e'
                            || layout1[i] == 't'
                            || layout1[i] == 'a'
                            || layout1[i] == 'o'
                            || layout1[i] == 'i'
                            || layout1[i] == 'n'
                            || layout1[i] == 's'
                            || layout1[i] == 'r'
                            || layout1[i] == 'h'
                            || layout1[i] == 'l'
                            || layout1[i] == 'd'
                            || layout1[i] == 'c'
                            || layout1[i] == 'u'
                            || layout1[i] == 'm'                           
                        )
                    )
                    ||
                    (!doSymbolLayer && !keepAlphas && keepHomeRowLeft && keepHomeRowRight &&
                        (
                            isalpha(layout1[i]) 
                            && layout1[i] != 'z'
                            && layout1[i] != 'q'
                            && layout1[i] != 'j'
                            && layout1[i] != 'x'
                        )
                    )
                    ||
                    (doSymbolLayer && !keepAlphas && !(keepHomeRowLeft || keepHomeRowRight) && 
                        (
                            layout1[i] == 'e'
                            || layout1[i] == 't'
                            || layout1[i] == 'a'
                            || layout1[i] == 'o'
                            || layout1[i] == 'i'
                            || layout1[i] == 'n'
                            || layout1[i] == 's'
                            || layout1[i] == 'r'
                            // || layout1[i] == '('
                            // || layout1[i] == '{'
                            // || layout1[i] == '['
                            // || layout1[i] == '<'
                            // || layout1[i] == ','
                            // || layout1[i] == '.'
                            // || layout1[i] == '\''
                            // || layout1[i] == '"'
                            // || layout1[i] == '_'
                            // || layout1[i] == ';'
                            // || layout1[i] == ':'
                            // || layout1[i] == '='                             
                        )
                    )
                    ||
                    (doSymbolLayer && !keepAlphas && (keepHomeRowLeft || keepHomeRowRight) && !(keepHomeRowLeft && keepHomeRowRight) &&
                        (
                            layout1[i] == 'e'
                            || layout1[i] == 't'
                            || layout1[i] == 'a'
                            || layout1[i] == 'o'
                            || layout1[i] == 'i'
                            || layout1[i] == 'n'
                            || layout1[i] == 's'
                            || layout1[i] == 'r'
                            || layout1[i] == 'h'
                            || layout1[i] == 'l'
                            || layout1[i] == 'd'
                            || layout1[i] == 'c'
                            || layout1[i] == 'u'
                            || layout1[i] == 'm'                             
                        )
                    )  
                    ||
                    (doSymbolLayer && keepAlphas && k1->nextAestheticRule != 0 &&
                        (
                            // (isalpha(layout1[i]) && !isalpha(layout2[i])) 
                            // || 
                            // (isalpha(layout1[i]) &&
                            // (layout1[i] != 'z'
                            // && layout1[i] != 'q'
                            // && layout1[i] != 'j'
                            // && layout1[i] != 'x')
                            // )    
                            // ||
                            // (
                                layout1[i] == '('
                                || layout1[i] == '{'
                                || layout1[i] == '['
                                || layout1[i] == '>'
                                || layout1[i] == ','
                                || layout1[i] == '.'
                                || layout1[i] == '\''
                                // || layout1[i] == '&'
                                || layout1[i] == '!'
                                || layout1[i] == '_'
                                // || layout1[i] == ';'
                                // || layout1[i] == ':'
                                // || layout1[i] == '$'                                  
                            // )                        
                        )
                    )
                    ||
                    (doSymbolLayer && keepAlphas && flexibleSymbolLocations && k1->nextAestheticRule == 0 &&
                        (
                            // (isalpha(layout1[i]) && !isalpha(layout2[i])) 
                            // || 
                            (isalpha(layout1[i]) &&
                            (layout1[i] != 'z'
                            && layout1[i] != 'q'
                            && layout1[i] != 'j'
                            && layout1[i] != 'x')
                            )    
                            ||
                            (
                                layout1[i] == '('
                                || layout1[i] == '{'
                                || layout1[i] == '['
                                // || layout1[i] == '>'
                                || layout1[i] == ','
                                || layout1[i] == '.'
                                || layout1[i] == '\''
                                // || layout1[i] == '&'
                                // || layout1[i] == '-'
                                || layout1[i] == '_'
                                // || layout1[i] == ';'
                                // || layout1[i] == ':'
                                // || layout1[i] == '='                                  
                            )                        
                        )
                    )                    
                    ||
                    (doSymbolLayer && keepAlphas && !flexibleSymbolLocations && k1->nextAestheticRule == 0 &&
                        (
                            // (isalpha(layout1[i]) && !isalpha(layout2[i])) 
                            // || 
                            // (isalpha(layout1[i]) &&
                            // (layout1[i] != 'z'
                            // && layout1[i] != 'q'
                            // && layout1[i] != 'j'
                            // && layout1[i] != 'x')
                            // )    
                            // ||
                            (
                                layout1[i] == '('
                                || layout1[i] == '{'
                                || layout1[i] == '['
                                // || layout1[i] == '<'
                                || layout1[i] == ','
                                || layout1[i] == '.'
                                || layout1[i] == '\''
                                // || layout1[i] == '"'
                                // || layout1[i] == '_'
                                // || layout1[i] == ';'
                                // || layout1[i] == ':'
                                // || layout1[i] == '=' 
                                // || layout1[i] == '?'
                                // || layout1[i] == '!'      
                                // || layout1[i] == '&'                            
                            )                        
                        )
                    )                    
                )                   
            ) {
                isSame = 0;
                break;
            }
            // printf(" %d", isSame);
        }
    }
    // if (isSame == 1) printf("\n%s\n%s\n%d", layout1, layout2, isSame);

    return isSame;
}

void purgeOutdatedKeyboards() {
    int newBestKeyboards = 0;
    Keyboard tempKeyboardStorage[MAX_TOP_KEYBOARDS];

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        if (bestKeyboards[i].fitness != prevBestFitness[i]) {
            newBestKeyboards = 1;
            timeLastBestKeyboard = time(NULL);
            break;
        }
    }

    int64_t bestFitness = FITNESS_MAX;
    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        if (bestKeyboards[i].fitness > 0 && bestKeyboards[i].fitness < bestFitness) bestFitness = bestKeyboards[i].fitness;
    }

    int64_t maxToKeep = FITNESS_MAX;
    if (bestFitness < FITNESS_MAX / 22) {
        if (doSymbolLayer && numPurges <= 4) maxToKeep = bestFitness * 22 / 20;
        else maxToKeep = bestFitness * 21 / 20;
    }

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
         if (bestKeyboards[i].fitness > maxToKeep) {
             copyKeyboard(&(bestKeyboards[i]), &nilKeyboard);
         }
    }

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        copyKeyboard(&(tempKeyboardStorage[i]), &(bestKeyboards[i]));
        copyKeyboard(&(bestKeyboards[i]), &nilKeyboard);
    }

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        saveTopKeyboard(&(tempKeyboardStorage[i]), &bestKeyboards);
    }

    if (newBestKeyboards) {
        // for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) bestKeyboards[i].fitness -= bestKeyboards[i].aesthetics;
        qsort(bestKeyboards, MAX_TOP_KEYBOARDS, sizeof(bestKeyboards[0]), &cmpKeyboardsByFitness);
        // for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) bestKeyboards[i].fitness += bestKeyboards[i].aesthetics;

        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            // if (trackImprovement[i] == prevBestFitness[i]) printf("%d", i);
            trackImprovement[i] = prevBestFitness[i];
            prevBestFitness[i] = bestKeyboards[i].fitness;
        }

        for (int i = 0, j = MAX_TOP_KEYBOARDS; i < MAX_TOP_KEYBOARDS; i++, j--) {
            // calcFitness(&bestKeyboards[i], 0);
            if (bestKeyboards[i].layout[0] != '\0') {  
                printf("Rank #%d (fitness: %d)", j, bestKeyboards[i].fitness);
                printPercentages(&(bestKeyboards[i])); 
            }
        }

        if (maxToKeep > 0) {
            printf("Purging all top keyboard entries with fitness scores higher than %d.\n", maxToKeep);
            printf("Current best keyboards are listed above.\n"); 
            printTime(globalStartTime);
        }

        // for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        //     if (1 || trackImprovement[i] == prevBestFitness[i]) printf("%d: %d %d\n", i, trackImprovement[i], prevBestFitness[i]);
        // }
    } else {
        time_t finish = time(NULL);
        if (finish - lastPrintTime > 60) {
            lastPrintTime = time(NULL);
            printTime(globalStartTime);
            printf("New best keyboards last found %ld hours, %ld minutes, %ld seconds ago.\n",
                (finish-timeLastBestKeyboard) / 3600, ((finish - timeLastBestKeyboard) % 3600) / 60,
                (finish-timeLastBestKeyboard) % 60);
        }
        if (((finish - timeLastBestKeyboard) % 3600) / 60 >= 10) {
            for (int i = 0, j = MAX_TOP_KEYBOARDS; i < MAX_TOP_KEYBOARDS; i++, j--) {
                if (bestKeyboards[i].layout[0] != '\0') {  
                    printf("Rank #%d ", j);
                    printPercentages(&(bestKeyboards[i])); 
                }
            }
            printf("\nAlgorithm complete. Best keyboards are printed above.\nProgram will now terminate.\nGoodbye.\n");
            exit(0);
        }
    }
        
    numPurges++;
}

void saveTopKeyboard(Keyboard *k, Keyboard *someBestKeyboards) {
    // if (MAX_TOP_KEYBOARDS == 1) return;

    if (k->fitness == FITNESS_MAX) return;
    int versionExists = -1;
    int isSaved = -1;

    if (!keepAlphas && !keepHomeRowLeft && !keepHomeRowRight && hand[locWithShifted(k, 'e')] == LEFT) {
		reverseLayout(k->shiftedLayout);
		reverseLayout(k->layout);
		reverseLayout(k->symbolLayer);
	}

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        if (someBestKeyboards[i].fitness == k->fitness) return;
        if (isSameLayout(k, &someBestKeyboards[i])) {
            versionExists = i;
            // printf("s");
            break;
        }
    }
// printf("a");
    if (versionExists != -1 && k->fitness < someBestKeyboards[versionExists].fitness) {
    	copyKeyboard(&someBestKeyboards[versionExists], k);
        isSaved = versionExists;
    } else if (versionExists == -1) {
        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            if (someBestKeyboards[i].layout[0] == '\0') {
            	copyKeyboard(&someBestKeyboards[i], k);
                // printf("%d", i);
                // printPercentages(k);
                // for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) printLayoutOnly(&((*someBestKeyboards)[i]));
                isSaved = i;
                // printf("%d", i);
                break;
            }
        }

        if (isSaved == -1) {
            int curWorst = 0;
            for (int i = 1; i < MAX_TOP_KEYBOARDS; i++) {
                 if (someBestKeyboards[i].fitness > someBestKeyboards[curWorst].fitness) {
                    curWorst = i;
                }
            }
            if (k->fitness < someBestKeyboards[curWorst].fitness) {
                copyKeyboard(&someBestKeyboards[curWorst], k);
                isSaved = curWorst;
            }
        }
    }

    if (isSaved != -1 && someBestKeyboards == &bestKeyboards) {
        // printf("*");
        fflush(stdout);
        qsort(bestKeyboards, MAX_TOP_KEYBOARDS, sizeof(bestKeyboards[0]), &cmpKeyboardsByFitness);
    }
}

/*
 * Search for an optimal keyboard layout. Equipped to use multithreading.
 */
void runAlgorithm()
{	
    numPurges = 0;
    cycleNumber = 0;

	struct ThreadArg arg;
	copyKeyboard(&arg.bestk, &nilKeyboard);
    globalStartTime = time(NULL);
    timeLastBestKeyboard = time(NULL);
    lastPrintTime = time(NULL);
    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        copyKeyboard(&(arg.bestKeyboardsThread[i]), &nilKeyboard);
        prevBestFitness[i] = FITNESS_MAX;
    }
    arg.numRounds = ALGORITHM_ROUNDS;
	arg.startTime = globalStartTime;
	arg.numThreads = numThreads;
    arg.chanceToUsePreviousLayout = CHANCE_TO_USE_PREVIOUS_LAYOUT;
    arg.numberOfSwaps = NUM_SWAPS_BETWEEN_ROUNDS;
	arg.isFinished = FALSE;
    
    int runsBeforeChanceInc = RUNS_BEFORE_CHANCE_INC;
    int runsBeforeSwapsInc = RUNS_BEFORE_SWAPS_INC;
    int gtbRounds = GTB_ROUNDS;
    time_t printTimeInterval = PRINT_TIME_INTERVAL;
    time_t timeOnPrint = arg.startTime + printTimeInterval;
    
    int64_t prevBestFitness = FITNESS_MAX; // masks an array of the same name. Currently harmless but should be fixed
	// printf("\nBeginning search for optimal layout. Current leaderboard will be printed each time it changes.\n");
    int runNum;
	for (runNum = 0; runNum < MAX_RUNS; ++runNum) {
        if (runNum % runsBeforeChanceInc == 0) {
            arg.chanceToUsePreviousLayout = pow(arg.chanceToUsePreviousLayout, CHANCE_EXPONENTIATOR);
			runsBeforeChanceInc = (int) (runsBeforeChanceInc * 1.2) + 1;
			if (detailedOutput)
                printf("Chance to use previous layout is now %f.\n",
                       arg.chanceToUsePreviousLayout);
        }
        
        if (runNum % runsBeforeSwapsInc == 0) {
            ++arg.numberOfSwaps;
			runsBeforeSwapsInc = (int) (runsBeforeSwapsInc * 1.2) + 1;
			if (detailedOutput)
                printf("Number of swaps between rounds is now %d.\n",
                       arg.numberOfSwaps);
        }
        
        if (runNum % RUNS_BEFORE_GTB_ROUNDS_INC == 0) {
            gtbRounds *= 2;
            if (detailedOutput)
                printf("Number of rounds in greatToBest() is now %d.\n",
                       gtbRounds);
        }

        if (runNum % RUNS_BEFORE_PURGE == 0) {
            purgeOutdatedKeyboards();
        }

        if (runNum % (1 + 15 * cycleNumber) == 0) {
            cycleNumber++;
            // printf("\n*** Beginning a new cycle (%d) ***\n", cycleNumber);
            arg.numRounds = ALGORITHM_ROUNDS;
            // arg.chanceToUsePreviousLayout = CHANCE_TO_USE_PREVIOUS_LAYOUT;
            arg.numberOfSwaps = NUM_SWAPS_BETWEEN_ROUNDS;
            runsBeforeChanceInc = RUNS_BEFORE_CHANCE_INC;
            runsBeforeSwapsInc = RUNS_BEFORE_SWAPS_INC;
            gtbRounds = GTB_ROUNDS;
        }

		runThreadsRec((void *) (&arg));

        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            // calcFitness(&(arg.bestKeyboardsThread[i]), 0);
            saveTopKeyboard(&(arg.bestKeyboardsThread[i]), &bestKeyboards); 
        }

        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            copyKeyboard(&(arg.bestKeyboardsThread[i]), &(bestKeyboards[i]));
        }

        // int64_t bestBeforeGTB = arg.bestk.fitness;
        greatToBest((void *) (&arg), gtbRounds);

        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            // calcFitness(&(arg.bestKeyboardsThread[i]), 0);
            saveTopKeyboard(&(arg.bestKeyboardsThread[i]), &bestKeyboards); 
        }

        for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
            copyKeyboard(&(arg.bestKeyboardsThread[i]), &(bestKeyboards[i]));
        }

        // printf("-");       
	}
}

void selectNextKeyboard(void *arg, Keyboard *k) {
    struct ThreadArg *threadArg = (struct ThreadArg *) arg;

    int nextKeyboard;
    int nullCounter = 0;
    int numImproved = 0;
    int notNull[MAX_TOP_KEYBOARDS];
    int improvedLastRound[MAX_TOP_KEYBOARDS];

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        if (threadArg->bestKeyboardsThread[i].layout[0] != '\0') {
            notNull[nullCounter] = i;
            nullCounter++;
        }
        
        int didNotImprove = 0;
        for (int j = 0; j < MAX_TOP_KEYBOARDS; j++) {
            if (threadArg->bestKeyboardsThread[i].fitness == trackImprovement[j] 
            || threadArg->bestKeyboardsThread[i].fitness == FITNESS_MAX) 
                didNotImprove = 1;
        }

        if (didNotImprove == 0) {
            improvedLastRound[numImproved] = i;
            numImproved++;
        }
    }

    if (nullCounter == 0) {
        initKeyboard(k);
    } else {
        if (rand() % (2 + cycleNumber) == 0 || numImproved == 0) {
            nextKeyboard = notNull[rand() % nullCounter];
            // while (threadArg->bestKeyboardsThread[nextKeyboard].layout[0] == '\0') nextKeyboard = notNull[rand() % nullCounter];
        } else {
            nextKeyboard = improvedLastRound[rand() % numImproved];
            // while (threadArg->bestKeyboardsThread[nextKeyboard].layout[0] == '\0') nextKeyboard = improvedLastRound[rand() % numImproved];
        }
        copyKeyboard(k, &(threadArg->bestKeyboardsThread[nextKeyboard]));
    }
}

/* 
 * This is the core function called by runAlgorithm(). It uses the 
 * following process to avoid as much downtime as possible.
 * 
 *  1. If numThreads <= 1, run anneal() numRounds times.
 *  2. Otherwise, recursively call this function with a decremented numThreads.
 *  3. Until the inner call of this function returns, keep running anneal().
 *  4. If the inner call found a bestk better than the current call, set the 
 *     current bestk to the inner bestk.
 * 
 * The core of this algorithm is step 3. In the worst case, this function will 
 * just be starting a new call to anneal() as the inner function returns, so 
 * the most possible time that can be wasted is the length of one anneal() call 
 * multiplied by the depth of the recursive call tree. The greatest proportion 
 * of time that can be wasted is (numThreads / numRounds), so for sufficiently 
 * large values of numRounds (perhaps 16 and above), the wasted time is trivial.
 */
void * runThreadsRec(void *arg)
{
	struct ThreadArg *threadArg = (struct ThreadArg *) arg;
		
	struct ThreadArg innerArg;
	copyThreadArg(&innerArg, threadArg);
	innerArg.numThreads = threadArg->numThreads - 1;
	innerArg.isFinished = FALSE;
	
    if (threadArg->numThreads > 1) {
        pthread_t thread;
        int ret = pthread_create(&thread, NULL, &runThreadsRec, 
                                 (void *) (&innerArg));
        if (ret) {
            threadArg->isFinished = TRUE;
            return (void *) (size_t) ret;
        }
    }
	
	Keyboard k;
    if (rand() / RAND_MAX < threadArg->chanceToUsePreviousLayout) selectNextKeyboard(arg, &k); 
    else initKeyboard(&k);

    int i;
	for (i = 0; threadArg->numThreads <= 1 ? i < threadArg->numRounds : !innerArg.isFinished; ++i) {
        smartMutate(NULL, &k, threadArg->numberOfSwaps, 0);
        anneal(&k, NULL, 0);
        saveTopKeyboard(&k, &(threadArg->bestKeyboardsThread));
    }

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        saveTopKeyboard(&(innerArg.bestKeyboardsThread[i]), &(threadArg->bestKeyboardsThread)); 
    }
	
	threadArg->isFinished = TRUE;
	return NULL;
}

/* Take a great keyboard and make it the best keyboard. Uses an optimization 
 * heuristic that works best for nearly-optimal keyboards.
 */
void greatToBest(void *outerArg, int numRounds)
{
    struct ThreadArg *masterArg = (struct ThreadArg *) outerArg;
	struct ThreadArg arg;
    initThreadArg(&arg);
    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++)
        copyKeyboard(&(arg.bestKeyboardsThread[i]), &(bestKeyboards[i]));
	// copyKeyboard(&arg.bestk, k);
	arg.numRounds = numRounds;
	arg.numThreads = numThreads;
	arg.isFinished = FALSE;
	
	greatToBestThreadRec((void *) (&arg));

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        saveTopKeyboard(&(arg.bestKeyboardsThread[i]), &(masterArg->bestKeyboardsThread)); 
    }
}

void * greatToBestThreadRec(void *arg)
{
    struct ThreadArg *threadArg = (struct ThreadArg *) arg;
    
	Keyboard k;
	struct ThreadArg innerArg;
	copyThreadArg(&innerArg, threadArg);
	innerArg.numThreads = threadArg->numThreads - 1;
	innerArg.isFinished = FALSE;
	
    if (threadArg->numThreads > 1) {
        pthread_t thread;
        int ret = pthread_create(&thread, NULL, &greatToBestThreadRec, 
                                 (void *) (&innerArg));
        if (ret) {
            threadArg->isFinished = TRUE;
            return (void *) (size_t) ret;
        }
    }
    
    int numberOfSwaps = GTB_NUMBER_OF_SWAPS;
    
    int i;
    for (i = 0; threadArg->numThreads <= 1 ? i < threadArg->numRounds : !innerArg.isFinished; ++i) {
        if (i % GTB_ROUNDS_BEFORE_SWAP_INC == GTB_ROUNDS_BEFORE_SWAP_INC - 1) {
            ++numberOfSwaps;
        }

        selectNextKeyboard(arg, &k);
        
        /* Any swaps made by smartMutate() are "locked in" and may not be
         * undone by anneal().
         */
        int lockins[numberOfSwaps][2];
        int shouldIgnoreAlphas = doSymbolLayer ? rand() % (0 + cycleNumber) : 0;
        smartMutate(lockins, &k, numberOfSwaps, shouldIgnoreAlphas);
        
        /* Use lockins only half the time. */
        if (i % 2 == 0) anneal(&k, lockins, numberOfSwaps);
        else anneal(&k, NULL, 0);
        
        calcFitness(&k, 0);
        saveTopKeyboard(&k, &(threadArg->bestKeyboardsThread)); 
    }	

    for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
        saveTopKeyboard(&(innerArg.bestKeyboardsThread[i]), &(threadArg->bestKeyboardsThread)); 
    }

    threadArg->isFinished = TRUE;
	return NULL;
}

/* 
 * Simulated annealing algorithm based on an implementation by Chris Johnson.
 */
int64_t anneal(Keyboard *k, int lockins[][2], size_t lockin_length)
{
	int64_t lastEvaluation, evaluation;
	int64_t lastImprovement = 0;
	int64_t evaluationToBeat = FITNESS_MAX;
		
	/* Do the "zeroth" iteration */
	calcFitness(k, 0);
	lastEvaluation = evaluation = k->fitness;
        
    /* TODO: Test the three versions of this to see which works best. (See 
     * email "source code" for details.)
     */
	/* Keep doing iterations while the layout is still improving */
	do {
		if (evaluation < lastEvaluation) {
			lastImprovement = lastEvaluation - evaluation;
		} else {
			lastImprovement = 0;
		}
		
		lastEvaluation = evaluation;
		evaluationToBeat = lastEvaluation + lastImprovement;
		evaluation = improveLayout(evaluationToBeat, k, lockins, lockin_length);
	} while (evaluation < evaluationToBeat);

	return evaluation;
}

/* 
 * Modified from a version written by Chris Johnson. 
 */
int64_t improveLayout(int64_t evaluationToBeat, Keyboard *k, 
	int lockins[][2], size_t lockin_length)
{
	int64_t evaluation;
	int i, j, inx;

    // int numCans = sizeof k->swapCandidates / sizeof k->swapCandidates[0];
    // printf("%d ", k->numCans);

	/* Create a list of indices and shuffle it. */
	int indices[k->numCans];

    for (i = 0; k->swapCandidates[i] >= 0; ++i) {
		indices[i] = k->swapCandidates[i];
	}

	buildShuffledIndices(k, indices, k->numCans);

	/* try swaps until we beat evaluationToBeat... */
	for (i = 0; i < k->numCans; ++i) {
		for (j = i + 1; j < k->numCans; ++j) {
			
			if (!isLegalSwap(k, indices[i], indices[j])) { // || (lockin_length >= 6 && (isalpha(charAt(k, i)) || isalpha(charAt(k, j))))) {
			// if (!isLegalSwap(k, indices[i], indices[j]) || (rand() % 2 == 0 && (isalpha(charAt(k, i)) || isalpha(charAt(k, j))))) {
				continue;
			}
			
			/* TODO: This is slow. I don't think it will be a significant 
			 * bottleneck, but I should profile it just in case.
			 */
			int skipRound = FALSE;
			for (inx = 0; inx < lockin_length; ++inx) {
				if (lockins[inx][0] == indices[i] || 
						lockins[inx][0] == indices[j] || 
						lockins[inx][1] == indices[i] || 
						lockins[inx][1] == indices[j]) {
					skipRound = TRUE;
					break;
				}
			}
			if (skipRound) {
				continue;
			}
			
            // Keyboard backupKeykoard;
            // copyKeyboard(&backupKeykoard, &k);

			swap(k, indices[i], indices[j]); 
			
			calcFitness(k, 0);
			evaluation = k->fitness;

			if (evaluation < evaluationToBeat) {
				/* good swap--keep it */
				return evaluation;
			} else {
				/* bad swap--undo it */
				swap(k, indices[i], indices[j]);
                // calcFitness(k, 0);
			}
		}
	}

	/* ...or not */
    calcFitness(k, 0);
	return evaluationToBeat;
}

/* 
 * Goes through the list of characters from least to most common. Selects 
 * characters to swap. Less frequent characters are more likely to be swapped.
 * 
 * For the nth character, the probability that it will be mutated is given by 
 *   P(1) = 1 / q
 *   P(n) = (1 / q) * (1 - (P(1) + P(2) + ... + P(n-1)))
 * where q is a constant.
 * 
 * Alternatively, 
 *   P(n) = (q-1)^(n-1) / q^n
 * (This formula does not necessarily apply for the last element.)
 * 
 * These probabilities are only correct if every swap is legal. If not, legal 
 * swaps are somewhat more probable and illegal swaps are of course completely 
 * impossible.
 *  
 * swapIndices: After the function returns, this contains a list of swaps made. 
 *   It must be able to contain (numberOfSwaps) swaps. If swapIndices is NULL,
 *   this function will execute as normal but will not write anything to 
 *   swapIndices.
 */ 
int smartMutate(int swapIndices[][2], Keyboard *k, int numberOfSwaps, int ignoreAlphas)
{
	int q = monLen / 4;
	
	int swapslen = 2 * numberOfSwaps;	
	char charsToSwap[swapslen];
	
	int i, j;

  	// if (rand() % 2 > 0) forcePlausibleHomeRow(k);

	/* Fills charsToSwap. */
	for (j = 0; j < swapslen; ++j) {
		charsToSwap[j] = monographs[0].key;

		for (i = monLen - 1; i >= 0; --i) {
		// for (i = 0; i < monLen; i++) {
			// if (isSwapCandidate(monographs[i].key) && !isalpha(monographs[i].key) && rand() % q == 0) {
			// if (isSwapCandidate(monographs[i].key) && rand() % q == 0) {
			if (!(ignoreAlphas && isalpha(monographs[i].key)) && isSwapCandidate(monographs[i].key) && rand() % q == 0) {
				charsToSwap[j] = monographs[i].key;
				break;
			}
		}
	}
	
	int lc1, lc2;
	for (i = 0; i < swapslen; i += 2) {
		lc1 = locWithShifted(k, charsToSwap[i]);
		lc2 = locWithShifted(k, charsToSwap[i+1]);
		
		if (swapIndices) {
            swapIndices[i / 2][0] = lc1;
            swapIndices[i / 2][1] = lc2;
        }
		
		if (isLegalSwap(k, lc1, lc2)) {
			swap(k, lc1, lc2);
		}
	}

    // if (rand() % 2 > 0) forcePlausibleHomeRow(k);
    // if (rand() % 2 > 0) {
    //     forcePlausibleHomeRow(k);
    //     Keyboard fhrKeyboard;
    //     copyKeyboard(&fhrKeyboard, &k);
    //     forcePlausibleHomeRow(&fhrKeyboard);
    //     if (k->layout != fhrKeyboard.layout) {
    //         calcFitness(&fhrKeyboard, 0);
    //         calcFitness(k, 0);
    //         if (fhrKeyboard.fitness < k->fitness) {
    //             copyKeyboard(k, &fhrKeyboard);
    //         }
    //     }
    // }
   	// if (rand() % 2 > 0) forcePlausibleHomeRow(k);

	return 0;
}

void initThreadArg(struct ThreadArg *arg)
{
    memset(arg, 0, sizeof(struct ThreadArg));
}

void copyThreadArg(struct ThreadArg *dest, struct ThreadArg *src)
{
    memcpy(dest, src, sizeof(struct ThreadArg));
}
