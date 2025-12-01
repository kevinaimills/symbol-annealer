/*
 *  charsets.c
 *  Typing 
 *  
 *  Created by Michael Dickens on 8/7/09.
 *  
 */

#include "tools.h"


void copyArray(int dest[], int src[], int length)
{
	memcpy(dest, src, length * sizeof(int));
}

void printTime(time_t start)
{
    time_t finish = time(NULL);
    printf("\nTime elapsed: %ld hours, %ld minutes, %ld seconds\n",
           (finish-start) / 3600, ((finish - start) % 3600) / 60,
           (finish-start) % 60);
}

int initData()
{
	initValues();

	int i, j, k;
	
	srand((unsigned int) time(NULL));

	// for (i = 0; i <= ksize; ++i)
	// 	nilKeyboard.layout[i] = nilKeyboard.shiftedLayout[i] = nilKeyboard.symbolLayer[i] = '\0';
	for (i = 0; i <= ksize * 3; ++i)
		nilKeyboard.swapCandidates[i] = -1;
	// for (i = 0; i < FINGER_COUNT; i++) {
	// 	nilKeyboard.fingerUsage[i] = 0;
	// 	nilKeyboard.fingerTravel[i] = 0;
	// }
	// for (i = 0; i < MAX_AESTHETIC_RULES; i++) {
	// 	nilKeyboard.aestheticPenalties[i] = 0;
	// }

	// nilKeyboard.nextAestheticRule = 0;
	// nilKeyboard.numCans = 0;
	nilKeyboard.fitness = FITNESS_MAX;
	// nilKeyboard.layerChange = 0;
	// nilKeyboard.distance = 0;
	// nilKeyboard.handTravel = 0;
	// nilKeyboard.handImbalance = 0;
	// nilKeyboard.fingerWork = 0;
	// nilKeyboard.fingerTravelWork = 0;
	// nilKeyboard.aesthetics = 0;
	// nilKeyboard.biLayerChange = 0;
	// nilKeyboard.inRoll = 0;
	// nilKeyboard.outRoll = 0;
	// nilKeyboard.sameHand = 0;
	// nilKeyboard.sameFinger = 0;
	// nilKeyboard.sameFingerMax = 0;
	// nilKeyboard.rowChange = 0;
	// nilKeyboard.homeJump = 0;
	// nilKeyboard.ringJump = 0;
	// nilKeyboard.toCenter = 0;
	// nilKeyboard.lateralStretch = 0;
	// nilKeyboard.halfScissor = 0;
	// nilKeyboard.fullScissor = 0;
	// nilKeyboard.biLayerSplit = 0;
	// nilKeyboard.triLayerChange = 0;
	// nilKeyboard.triSplitFinger = 0;
	// nilKeyboard.triInRoll = 0;
	// nilKeyboard.triOutRoll = 0;
	// nilKeyboard.triOneHand = 0;
	// nilKeyboard.triAlt = 0;
	// nilKeyboard.triHomeJump = 0;
	// nilKeyboard.triRedirect = 0;    
	// nilKeyboard.halfScissorTri = 0;
	// nilKeyboard.fullScissorTri = 0;
	// nilKeyboard.lateralStretchTri = 0; 

	// Keyboard blank = {0};
	// // for (i = 0; i <= ksize; ++i)
	// // 	blank.layout[i] = blank.shiftedLayout[i] = blank.symbolLayer[i] = '\0';
	// for (i = 0; i <= ksize * 3; ++i)
	// 	blank.swapCandidates[i] = -1;
	// blank.fitness = FITNESS_MAX;

	// copyKeyboard(&nilKeyboard, &blank);

	// Keyboard bestKeyboards[MAX_TOP_KEYBOARDS];
	for (int i = 0; i < MAX_TOP_KEYBOARDS; i++) {
    	copyKeyboard(&bestKeyboards[i], &nilKeyboard);
		// printf("\n%li", bestKeyboards[i].fitness);
	}
 
	// calcFitness(&nilKeyboard);
	// printPercentages(&nilKeyboard);

    strncpy(qwerty, "qwertyuiopasdfghjkl;zxcvbnm,./", 30);

/*					(i == MIDDLE && j == INDEX) /  
					|| (i == INDEX && j == MIDDLE
 					|| (i == RING && j == INDEX)  
					|| (i == RING && j == MIDDLE)*/ 

	for (i = 0; i < 5; ++i)
		for (j = 0; j < 5; ++j) {
			rowChangeTableDown[i][j] = rowChangeDown;
			rowChangeTableUp[i][j] = rowChangeUp;
			if (i != THUMB && j != THUMB) {
				if (
					(i == INDEX && j == INDEX)
					|| (i == MIDDLE && j == RING)
					) rowChangeTableDown[i][j] += handSmooth;
				else if (abs(i - j) == 1)      rowChangeTableDown[i][j] += handWarp;
				
				if (
					(i == INDEX && j == INDEX)
					|| (i == RING && j == MIDDLE)
					) rowChangeTableUp[i][j] += handSmooth;
				else if (abs(i - j) == 1)      rowChangeTableUp[i][j] += handWarp;
			}
		}

	i = 0;
	j = 0;
	k = 0;
	keysToInclude[90] = '\0';
	// char symbols[90];
	// if (doSymbolLayer) strcpy(symbols, ALL_SYMBOLS);
	// 	else strcpy(symbols, SHORT_SYMBOLS); 
	
	// while (i < 90) {
	// 	if (i < 60 && !islower(textLayout[i % 30]) && ALL_SYMBOLS[j] != '\0') {
	// 		keysToInclude[i] = ALL_SYMBOLS[j];
	// 		j++;
	// 	}
	// 	else if (i < 30) keysToInclude[i] = textLayout[i];
	// 	else if (i < 60) keysToInclude[i] = toupper(textLayout[i - 30]);
	// 	else if (i >= 60 && !doSymbolLayer) keysToInclude[i] = 'X';
	// 	else if (ALL_SYMBOLS[j] != '\0') {
	// 		keysToInclude[i] = ALL_SYMBOLS[j];
	// 		j++;
	// 	}
	// 	else keysToInclude[i] = '0';
	// 	i++;
	// }

	while (i < 90) {
		// if (i < 60 && !islower(textLayout[i % 30]) && ALL_SYMBOLS[j] != '\0') {
		// 	keysToInclude[i] = ALL_SYMBOLS[j];
		// 	j++;
		// }
		if (i < 30 && doSymbolLayer) keysToInclude[i] = textLayout[i];
		else if (i < 30 && !doSymbolLayer) {
			if isalpha(textLayout[i]) keysToInclude[i] = textLayout[i];
			else {
				if (ALL_SYMBOLS[k] != '\0' && k < strlen(ALL_SYMBOLS)) keysToInclude[i] = ALL_SYMBOLS[k];
				else keysToInclude[i] = '0';
				k++;
			}
		}
		else if (i < 60 && isalpha(keysToInclude[i - 30])) keysToInclude[i] = toupper(textLayout[i - 30]);
		else if (i < 60 && strlen(shiftLayout) > 0 && doSymbolLayer) {			
			keysToInclude[i] = shiftLayout[i - 30];
			// j++;
		}
		else if (i < 60 && (strlen(shiftLayout) == 0 && doSymbolLayer)) {			
			while (strchr(textLayout, ALL_SYMBOLS[k]) || strchr(shiftLayout, ALL_SYMBOLS[k]) || (doSymbolLayer && strchr(symbolLayout, ALL_SYMBOLS[k]))) k++;
			if (ALL_SYMBOLS[k] != '\0' && k < strlen(ALL_SYMBOLS)) keysToInclude[i] = ALL_SYMBOLS[k];
			else keysToInclude[i] = '0';
			k++;
		}
		else if (i < 60 && !doSymbolLayer) {			
			if (ALL_SYMBOLS[k] != '\0' && k < strlen(ALL_SYMBOLS)) keysToInclude[i] = ALL_SYMBOLS[k];
			else keysToInclude[i] = '0';
			k++;
		}
		else if (i >= 60 && !doSymbolLayer) keysToInclude[i] = 'X';
		else if (i >= 60 && strlen(symbolLayout) != 0) keysToInclude[i] = symbolLayout[i - 60];
		else if (ALL_SYMBOLS[j] != '\0') {
			while (strchr(textLayout, ALL_SYMBOLS[k]) || strchr(shiftLayout, ALL_SYMBOLS[k]) || strchr(symbolLayout, ALL_SYMBOLS[k])) k++;
			if (ALL_SYMBOLS[k] != '\0' && k < strlen(ALL_SYMBOLS)) keysToInclude[i] = ALL_SYMBOLS[k];
			else keysToInclude[i] = '0';
			k++;
		}
		else keysToInclude[i] = '0';
		i++;
	}

	for (i = 0; i < strlen(ALL_SYMBOLS); i++) {
		int count = 0;
		for (j = 0; j < 90; j++) {
			if (keysToInclude[j] == ALL_SYMBOLS[i]) count++;
		}
		if (count == 2 || (count == 0 && doSymbolLayer)) {
			printf("\n*** Illegal symbol count: some symbols are either duplicated or missing. ***\n%s", keysToInclude);
			exit(1);
		}
		
	}

	for (i = 0; i < strlen(ALL_LETTERS); i++) {
		int count = 0;
		for (j = 0; j < 90; j++) {
			if (keysToInclude[j] == ALL_LETTERS[i]) count++;
		}
		if (count != 1) {
			printf("\n*** Illegal letter count: some letters are either duplicated or missing. ***\n%s", keysToInclude);
			exit(1);
		}
	}

	// if (fullKeyboard == K_NO) strcpy(keysToInclude, DEFAULT_KEYBOARD_30);
	// else if (fullKeyboard == K_STANDARD) strcpy(keysToInclude, DEFAULT_KEYBOARD_STANDARD); 
	// else if (fullKeyboard == K_KINESIS) strcpy(keysToInclude, DEFAULT_KEYBOARD_KINESIS);  
	
	initKeyboardData();
	initTypingData();
	
	return 0;
} // int initData(); 
 
void initKeyboardData()
{
	int i;
	
	if (fullKeyboard == K_NO) {
		static int fingerCopy[KSIZE_MAX * 3] = {
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 

			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 		
		};

		if (useRingForTopPinky) {
			fingerCopy[0] = RING;
			fingerCopy[9] = RING;
			fingerCopy[30] = RING;
			fingerCopy[39] = RING;
			fingerCopy[60] = RING;
			fingerCopy[69] = RING;
		}

		copyArray(finger, fingerCopy, ksize * 3);
		
		static int columnCopy[KSIZE_MAX * 3] = {
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 

			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 

			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
		};
		copyArray(column, columnCopy, ksize * 3);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 

			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 

			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(row, rowCopy, ksize * 3);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX * 3] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 

			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 

			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize * 3);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 

			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 

			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize * 3);
		
		for (i = 0; i < KSIZE_MAX; ++i)
			isOutside[i] = FALSE;
		
		static int printableCopy[KSIZE_MAX * 3] = {
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 

			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 

			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
		};
		copyArray(printable, printableCopy, ksize);
	 
	} else if (fullKeyboard == K_STANDARD) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			THUMB, THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, /* thumb row  */ 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 2;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isOutside, isOutsideCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE, FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE, TRUE,  
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, 
			TRUE,  FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE, FALSE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);
		
	} else if (fullKeyboard == K_KINESIS) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[KSIZE_MAX] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, /* thumb row */
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 2;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);	
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isOutside, isOutsideCopy, ksize);

		static int printableCopy[KSIZE_MAX] = {
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, 
			FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  
		};
		copyArray(printable, printableCopy, ksize);		

	} else if (fullKeyboard == K_IPHONE) {
		static int fingerCopy[KSIZE_MAX] = {
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		for (i = 0; i < KSIZE_MAX; ++i)
			isOutside[i] = FALSE;
		
		static int printableCopy[KSIZE_MAX] = {
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, 
		};
		copyArray(printable, printableCopy, ksize);
	}
	
	for (i = 0; i < ksize; ++i)
		isCenterOrOutside[i] = isCenter[i] || isOutside[i];
    
    /* Find firstNumberIndex. */
    char *ptrToOne = strchr(keysToInclude, '1');
	if (ptrToOne) firstNumberIndex = (int) (ptrToOne - keysToInclude);
	else firstNumberIndex = -1;
    
    /* Adjust firstNumberIndex to fix for non-printable indices. */
    if (firstNumberIndex >= 0) {
        int saved = firstNumberIndex;
        int i;
        for (i = 0; i <= saved; ++i)
            if (!printable[i]) ++firstNumberIndex;
    }

}

/* Reads typing data from allChars.txt and allDigraphs.txt.
 *  
 * Produces monographs and digraphs involving backspace by assuming that all 
 * characters are equally mistyped.
 */
int initTypingData()
{ 
	initVariables();
	totalTri = 0;
	triLen = 0;
	totalDi = 0;
	diLen = 0;
	totalMon = 0;
	monLen = 0;
	int i = 0;

	// for (i = 0; i < MON_LEN_MAX; i++) monographs[i].key = '\0';
	// for (i = 0; i < DI_LEN_MAX; i++) digraphs[i].key[0] = '\0'; 
	// for (i = 0; i < TRI_LEN_MAX; i++) trigraphs[i].key[0] = '\0'; 
	
	readDataFromFile(MONOGRAPHFILE, 1, 100);
	readDataFromFile(DIGRAPH_FILE, 2, 100);
	readDataFromFile(TRIGRAPH_FILE, 3, 100);

	// for (int i = 0; i < 50; i++) printf("%d - ", trigraphs[i].value);
	/* If necessary, add the stats for backspace.*/
	if (strchr(keysToInclude, '\b')) {
		/* Add backpace to the digraph list. */
		for (int i = 0; i < monLen; ++i) {
			int64_t errorRate = monographs[i].value * ERROR_RATE_PERCENT / 100;
			digraphs[diLen].key[0] = '\b';
			digraphs[diLen].key[1] = monographs[i].key;
			digraphs[diLen].value = errorRate;
			++diLen;
			
			digraphs[diLen].key[0] = monographs[i].key;
			digraphs[diLen].key[1] = '\b';
			digraphs[diLen].value = errorRate;
			++diLen;
		}
	 
		/* Add backspace to the monograph list. */
		monographs[monLen].key = '\b';
		monographs[monLen].value = totalMon * ERROR_RATE_PERCENT / 100;
		++monLen;
	}
    
    qsort(monographs, monLen, sizeof(struct Monograph), &cmpMonographsByValue);
    qsort(digraphs, diLen, sizeof(struct Digraph), &cmpDigraphsByValue);
    qsort(trigraphs, triLen, sizeof(struct Trigraph), &cmpTrigraphsByValue);
	
	return 0;
}

int readDataFromFile(char *filePath, int numChars, int scalePercent)
{

	char dataFile[100];

	if (doSymbolLayer) strcpy(dataFile, DATA_FOLDER);
	else strcpy(dataFile, DATA_FOLDER_TEXT_ONLY);

	strcat(dataFile, filePath);

	char *keys[3];
    int64_t *value;
	int64_t *totalData;
	int *dataLen;
	int lenMax;

	if (numChars == 1) {
		totalData = &totalMon;
		dataLen = &monLen;
		lenMax = MON_LEN_MAX;
	}
	else if (numChars == 2) {
		totalData = &totalDi;
		dataLen = &diLen;
		lenMax = DI_LEN_MAX;
	}
	else if (numChars == 3) {
		totalData = &totalTri;
		dataLen = &triLen;
		lenMax = TRI_LEN_MAX;
	}
	else return -1;

	int i, j;	
	FILE *file = fopen(dataFile, "r");
	CHECK_FILE_FOR_NULL(file, dataFile);

	int c = '\0';
	
	for (i = 0; i < lenMax; i++) {

		if (numChars == 1) {
			keys[0] = &(monographs[i].key);
			value = &(monographs[i].value);
		}
		else if (numChars == 2) {
			keys[0] = &(digraphs[i].key[0]);
			keys[1] = &(digraphs[i].key[1]);
			value = &(digraphs[i].value);
		}
		else if (numChars == 3) {
			keys[0] = &(trigraphs[i].key[0]);
			keys[1] = &(trigraphs[i].key[1]);
			keys[2] = &(trigraphs[i].key[2]);
			value = &(trigraphs[i].value);
		}

		int shouldInclude = 1;

		for (int j = 0; j < numChars; j++) {

			/* Skip any extra newlines.  */
			while ((c = getc(file)) == '\n')
				;
			if (c == EOF) break;

			if (c == '\\') c = convertEscapeChar(getc(file));
			if (c == 0) {
				fprintf(stderr, "Error: In file %s, unknown escape character \\%c.\n",
						filePath, c);
				fclose(file);
				return 1;
			}
			*(keys[j]) = c;
			if (!strchr(keysToInclude, c)) shouldInclude = 0; 
		}

		c = getc(file); /* Skip the space between the digraph and the value. */ 

		if (shouldInclude) {
			*value = 0;
			while ((c = getc(file)) != EOF && c >= '0' && c <= '9') {
				*value *= 10;
				*value += c - '0';
			}
			
			*value = *value / DIVISOR;
			// printf("%d", *value);

//			trigraphs[i].value /= 10;
//			printf("%d - ", trigraphs[i].value);

			if (*value == 0)
				break;

			*totalData += *value;
		}
	// for (int i = 0; i < 50; i++) printf("%d - ", trigraphs[i].value);

		/* Skip all extra characters. */
		while (c != EOF && c != '\n')
			c = getc(file);
	}
	
	*dataLen = i;
	fclose(file);

	return 0; 
}

/* 
 * Compile the typing data from each of the given files into a single file.
 * 
 * outfileName: The file to which the new typing data will be written.
 * filenames: The names of each file to be read.
 * multipliers: The multipliers corresponding with the filenames.
 * length: Length of filenames and multipliers. 
 * unit: The unit size of the strings to be read (characters=1, digraphs=2, etc).
 * max: The maximum number of strings that can be put into the file.
 * 
 * Return Codes
 * 1: Null file.
 * 2: Allocation failure.
 * 
 * TODO: Refactor this to use monograph and digraph structs instead of two 
 *   parallel arrays of keys and values.
 */
int compileTypingData(char *outfileName, const char *filenames[], 
		int multipliers[], int length, int unit, int max)
{
	return -1;

	size_t size = 5000;
	/* Number of elements in keys and values. */
	int dataLen = 0;

	const int lineLen = 100;
	char line[lineLen];
	
	FILE *outfile = fopen(outfileName, "w");
	CHECK_FILE_FOR_NULL(outfile, outfileName);
	if (outfile == NULL) {
		fprintf(stderr, "Error: null file %s.\n", outfileName);
		return 1;
	}
	
	struct NGraph *ngraphs = malloc(sizeof(struct NGraph) * size);
	if (ngraphs == NULL) {
		fprintf(stderr, "Error: In compileTypingData(), ngraphs is null (malloc failure).\n");
		return 2;
	}
    memset(ngraphs, 0, sizeof(struct NGraph) * size);

	int i, k;
	for (i = 0; i < length; ++i) {
		printf("file %s,  multiplier %d\n", filenames[i], multipliers[i]);
		
		if (multipliers[i] == 0)
			continue;
		
		FILE *file = fopen(filenames[i], "r");
		if (file == NULL) {
			fprintf(stderr, "Error: In compileTypingData(), null file %s.\n", filenames[i]);
			fclose(outfile);
			free(ngraphs);
			return 1;
		}
		
		while (fgets(line, lineLen-1, file)) {
			if (dataLen >= size) {
				size *= 2;
				ngraphs = realloc(ngraphs, sizeof(struct NGraph) * size);
				
				if (ngraphs == NULL) {
					fprintf(stderr, "Error: In compileTypingData(), ngraphs is null (realloc failure).\n");
					return 2;
				}
			}
			
			/* If the n-graph already exists, add to its value. */
			int found = FALSE;
			for (k = 0; k < dataLen; ++k) {
				if (streqn(ngraphs[k].key, line, unit)) {
					found = TRUE;
					ngraphs[k].value += atoi(line + unit + 1) * multipliers[i];
				}
			}
			
			/* If the n-graph does not already exist, add it. */
			if (found == FALSE) {
				ngraphs[dataLen].key = malloc(sizeof(char) * (unit + 1));
				if (ngraphs[dataLen].key == NULL) {
                    /* TODO: free all allocated memory */
					fprintf(stderr, "Error: In compileTypingData(), ngraphs[%d].key is null (malloc failure).\n", dataLen);
					return 2;
				}
				
				strncpy(ngraphs[dataLen].key, line, unit);
				ngraphs[dataLen].key[unit] = '\0';
				ngraphs[k].value = atoi(line + unit + 1) * multipliers[i];
				++dataLen;
			}
			
		}
		
		fclose(file);
	}
	
    qsort(ngraphs, dataLen, sizeof(struct NGraph), cmpNGraphsByValue);
	
	for (i = 0; i < dataLen && i < max; ++i) {
		strncpy(line, ngraphs[i].key, unit);
		sprintf(line + unit, " %lld\n", ngraphs[i].value);
		
		fputs(line, outfile);
		free(ngraphs[i].key);
	}
	
	fclose(outfile);
	free(ngraphs);
	
	return 0;
}

/* 
 * Accepts the following escape sequences: 
 * \n (newline)
 * \t (tab) 
 * \s (shift) 
 * \\ (backslash)
 * \b (backspace)
 *  
 * return 0: Unknown escape character.
 */
int convertEscapeChar(int c)
{
	if (c == 'n') {
		return '\n';
	} else if (c == 't') {
		return '\t';
	} else if (c == 's') {
		return ASCII_SHIFT;
	} else if (c == '\\') {
		return '\\';
	} else if (c == 'b') {
		return '\b'; /* backspace */
	} else return 0;
}

int layerDiff(int layer0, int layer1)
{
	if (layer0 == layer1) return 0;
	else if (layer0 == 0 || layer1 == 0) return 1;
	else return 2;
}

void initVariables()
{
    variablesLength = 0;
    
#define ADD_VAR(varName, desc) \
    variables[variablesLength].name = #varName; \
    variables[variablesLength].addr = &varName; \
    variables[variablesLength].description = desc; \
    ++variablesLength;
    
    ADD_VAR(detailedOutput, "(bool) provide additional information while running the algorithm");
    ADD_VAR(keepZXCV, "(bool) keep keys Z, X, C, and V in place");
    ADD_VAR(keepQWERTY, "(bool) try to keep keys in their QWERTY positions");
    ADD_VAR(keepNumbers, "(bool) keep numbers in place");
    ADD_VAR(keepBrackets, "(bool) keep brackets symmetrical");
    ADD_VAR(keepShiftPairs, "(bool) shifted/unshifted pairs of non-alphabetic characters stay together");
    ADD_VAR(keepTab, "(bool) keep Tab in place");
    ADD_VAR(keepNumbersShifted, "(bool) numbers do not move between shifted and unshifted");
    ADD_VAR(numThreads, "number of threads to create\n");
    ADD_VAR(distance, NULL);
    ADD_VAR(inRoll, NULL);
    ADD_VAR(outRoll, NULL);
    ADD_VAR(sameHand, NULL);
    ADD_VAR(sameFingerP, NULL);
    ADD_VAR(sameFingerR, NULL);
    ADD_VAR(sameFingerM, NULL);
    ADD_VAR(sameFingerI, NULL);
    ADD_VAR(rowChangeUp, NULL);
    ADD_VAR(rowChangeDown, NULL);
    ADD_VAR(handWarp, NULL);
    ADD_VAR(handSmooth, NULL);
    ADD_VAR(homeJump, NULL);
    ADD_VAR(homeJumpIndex, NULL);
    ADD_VAR(doubleJump, NULL);
    ADD_VAR(toCenter, NULL);
    ADD_VAR(biLayerSplit, NULL);
    ADD_VAR(lateralStretch, NULL);
    ADD_VAR(halfScissor, NULL);
    ADD_VAR(fullScissor, NULL);
    ADD_VAR(pinkyOverload, NULL);
	ADD_VAR(ringOverload, NULL);
	ADD_VAR(indexCorner, NULL);
    ADD_VAR(triSplitFinger, NULL);
	ADD_VAR(triInRoll, NULL);
	ADD_VAR(triOutRoll, NULL);
	ADD_VAR(triOneHand, NULL);
	ADD_VAR(triAlt, NULL);
	ADD_VAR(triRedirect, NULL);
	ADD_VAR(triHomeJump, NULL);
	ADD_VAR(halfScissorTri, NULL);
	ADD_VAR(fullScissorTri, NULL);
	ADD_VAR(lateralStretchTri, NULL);
#undef ADD_VAR
}

int getValue(const char *name)
{
    /* This is O(n), but it's a smallish n and speed is not essential. */
    int i;
    for (i = 0; i < variablesLength; ++i) {
        if (streq(name, variables[i].name)) {
            printf("%s = %d\n\n", variables[i].name, *variables[i].addr);
            return 0;
        }
    }
    
    printf("Unknown variable \"%s\". Type \"variables\" for a complete listing of possible variables.\n\n", name);
    return 1;
}

/*
 * Takes a string containing a name and a value. Sets the variable with the 
 * given name to the given value.
 * 
 * If the variable is successfully changed, returns 0. Otherwise, returns 
 * nonzero.
 */
int setValue(char *str)
{
	size_t len = strlen(str);
	
	char *name = str;
	char *valstr = strchr(str, ' ');
    
	if (len == 0 || valstr == NULL) {
		printf("No variable specified. Type \"variables\" for a complete listing of possible variables.\n\n");
		return 2;
	}
    
	*valstr = '\0'; ++valstr;
	
	int value = atoi(valstr);
    
    /* This is O(n), but it's a smallish n and speed is not essential. */
    int i;
    for (i = 0; i < variablesLength; ++i) {
        if (streq(name, variables[i].name)) {
            *variables[i].addr = value;
            /* If the user changes a cost, it is necessary to redo
             * preCalculateFitness().
             */
            if (USE_COST_ARRAY)
                preCalculateFitness();
            
            printf("%s set to %d.\n\n", name, value);
            return 0;
        }
    }
	
    printf("Unknown variable \"%s\". Type \"variables\" for a complete listing of possible variables.\n\n", name);
    return 1;
}

int cmpMonographsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct Monograph *) one)->value;
    int64_t val2 = ((struct Monograph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpDigraphsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct Digraph *) one)->value;
    int64_t val2 = ((struct Digraph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpTrigraphsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct Trigraph *) one)->value;
    int64_t val2 = ((struct Trigraph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpNGraphsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct NGraph *) one)->value;
    int64_t val2 = ((struct NGraph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpKeyboardsByFitness(const void *one, const void *two)
{
    int64_t val1 = ((struct ktype *) one)->fitness;
    int64_t val2 = ((struct ktype *) two)->fitness;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

/* Returns the matching bracket for c. If c is not a bracket, returns 0.
 */
inline char getMatchingBracket(char c)
{
	switch (c) {
	case '(':
		return ')';
	case ')':
		return '(';
	case '[':
		return ']';
	case ']':
		return '[';
	case '{':
		return '}';
	case '}':
		return '{';
	case '<':
		return '>';
	case '>':
		return '<';
	default:
		return 0;
	}
}

/* 
 * If c should be kept in a pair with its shifted or unshifted character, 
 * returns true. Otherwise, returns false. 
 *   
 * Alphabetical characters and whitespace are kept in shifted pairs. Other keys 
 * are not, unless the keepShiftPairs variable is set to TRUE.
 */
inline int keepShiftPair(char c)
{
	if (isalpha(c)) return 1;
	
	// if (!doSymbolLayer) {
	//  	if (c == '.' || c == ',' || c == '\'' || c == ';' || c == '!' || c == '?' || c == '"' || c == ':') return 1;
	// }
	// return isalpha(c);// || isspace(c) || c == '\b'; 
	return 0;
}

void setksize(int type)
{
	fullKeyboard = type;
	
	switch (fullKeyboard) {
	case K_NO:
		ksize = 30;
		trueksize = 30;
		kbdFilename = "layoutStore.txt";
		break;
	case K_STANDARD:
		ksize = 56;
		trueksize = 47;
		kbdFilename = "fullLayoutStore.txt";
		break;
	case K_KINESIS:
		ksize = 72;
		trueksize = 50;
		kbdFilename = "kinesisLayoutStore.txt";
		break;
	case K_IPHONE:
		ksize = 30;
		trueksize = 26;
		kbdFilename = NULL;
		break;
	}

	initData();
	if (USE_COST_ARRAY)
		preCalculateFitness();

}

void reverseLayout(char* str)
{
     if (!str) {
        return;
    }

    int i;
    int j;
 
	for (int l = 0; l < strlen(str) / 10; l++) {
		i = 10 * l;
		j = 10 * l + 9;

		while (i < j) {
			char c = str[i];
			str[i] = str[j];
			str[j] = c;
			i++;
			j--;
		}
	}
}
