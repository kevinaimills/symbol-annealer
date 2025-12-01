/*
 *  values.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/23/09.
 *
 */

#include "values.h"

int initValues()
{
	int i;
	
	initCosts();

/*

			200, 150, 40, 100, 130, 130, 100, 40, 150, 200,
			0,   0,  0,  0,  160, 160,  0,  0,  0,  0,
			180, 150, 50, 30, 190, 190, 30, 50, 150, 180,
*/

	if (fullKeyboard == K_NO) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t fingerTravel[KSIZE_MAX] = {
			12, 7, 3, 4, 4, 4, 4, 3, 7, 12,
			0,  0, 0, 0, 4, 4, 0, 0, 0, 0, 
			12, 8, 4, 2, 5, 5, 2, 4, 8, 12,
		};

		static int64_t handTravel[KSIZE_MAX]= {
			4, 0, 0, 2, 4, 4, 2, 0, 0, 4,
			0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 
			2, 0, 0, 0, 4, 4, 0, 0, 0, 2,
		}; 

		if (useRingForTopPinky) { 
			fingerTravel[0] = fingerTravel[1];
			fingerTravel[9] = fingerTravel[8];
			handTravel[0] = 0;//handTravel[3];
			handTravel[9] = 0;//handTravel[6];
		}

		for (i = 0; i < ksize; ++i) {
			distanceCosts[i] = fingerTravel[i];
			handTravelCosts[i] = handTravel[i];
		}
		
	} else if (fullKeyboard == K_STANDARD) {
		
		// These costs are optimized for a full standard layout. Any cost that 
		// is 999 is not supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  40,  40,  30,  40,  70,  80,  40,  30,  40,  40,  60,  90, 140, 
			999,   0,   0,   0,   0,  30,  30,   0,   0,   0,   0,  50, 999, 999, 
			999,  70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 999, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
			
	} else if (fullKeyboard == K_KINESIS) {
		
		// These costs are optimized for Kinesis. Any cost that is 999 is not 
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			120, 110, 100,  75, 100, 130, 130, 100,  75, 100, 110, 120, 
			 90,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40,  90, 
			 60,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  60, 
			999,  70,  70,  70,  50,  80,  80,  50,  70,  70,  70, 999, 
			999, 140, 140, 999, 999, 999, 999, 999, 999, 140, 140, 999, 	
			  0,  50, 999, 999, 999, 999, 999, 999, 999, 999,  50,   0, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_IPHONE) {
		
		// Thumbs are centered over the QWERTY D and K keys.
		static int64_t costsCopy[KSIZE_MAX] = {
			  45,  30,  20,  10,  20,  20,  10,  20,  30,  40, 
			  20,  10,   0,   0,  10,  10,   0,   0,  10, 999,
			 999,  60,  50,  30,  20,  20,  50,  60, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	}

	// Based on distance from the ctrl key and how much of a stretch it is.
	shortcutCosts[ 0] =  0; shortcutCosts[ 1] =  0; shortcutCosts[ 2] =  1; shortcutCosts[ 3] =  3; shortcutCosts[ 4] =  4; 
	shortcutCosts[ 5] =  8; shortcutCosts[ 6] = 10; shortcutCosts[ 7] = 10; shortcutCosts[ 8] = 10; shortcutCosts[ 9] = 10; 
	shortcutCosts[10] =  0; shortcutCosts[11] =  0; shortcutCosts[12] =  2; shortcutCosts[13] =  3; shortcutCosts[14] =  5; 
	shortcutCosts[15] =  8; shortcutCosts[16] = 10; shortcutCosts[17] = 10; shortcutCosts[18] = 10; shortcutCosts[19] = 10; 
	shortcutCosts[20] =  0; shortcutCosts[21] =  0; shortcutCosts[22] =  0; shortcutCosts[23] =  2; shortcutCosts[24] =  4; 
	shortcutCosts[25] =  8; shortcutCosts[26] = 10; shortcutCosts[27] = 10; shortcutCosts[28] = 10; shortcutCosts[29] = 10; 
	
	// for (int i = 0; i < ksize; i++) {
	// 	textLayout[i] = '\0';
	// 	shiftLayout[i] = '\0';
	// 	shiftLayout[i] = '\0';		
	// }
	return 0;
}

void initCosts()
{
	detailedOutput = 0;
	textLayout = LAYOUT_QWERTY;
	shiftLayout = "";
	symbolLayout = "";
	keepAlphas = 0;
	noHomeRowC = 0;
	keepHomeRowLeft = 0;
	keepHomeRowRight = 0;		  
	doSymbolLayer = 0;
	forceBracketsHomeRow = 0; 
	treatAnglesAsBrackets = 0;
	flexibleSymbolLocations = 0;
	includeSymbolRolls = 0;
	forceMirrorOrSameHand = 0;
	forceBracketMirrors = 0;
	useRingForTopPinky = 0;
	triInRoll =         -1;
	triRedirect =       2;//handWarp;
	triOneHand =        -1;//-handWarp / 4;//-handWarp;//handWarp / 4;
	inRoll =		 -1;  // see commented fn in fitness.c
	outRoll =	     -1;// -handWarp; // actually consecutive fingers bonus 

    /* If you do not wish to use multithreading, set numThreads to 1. */
	numThreads = 8;
	
	keepZXCV = FALSE;
	keepQWERTY = FALSE;
	keepNumbers = 0;
	keepBrackets = TRUE;
	keepShiftPairs = 0;
	keepTab = FALSE;  
	keepConsonantsLeft = 1;
	keepNumbersShifted = FALSE;

	zCost = 10;
	xCost =  6;
	cCost = 12;
	vCost = 14;
	qwertyPosCost = 14;
	qwertyFingerCost = 4;
	qwertyHandCost = 20;
	numbersShiftedCost = -1000000;






	overallScale = 		80;

	handWarp =			1;
	handMove =			overallScale / 2;
	distance =		  	overallScale / 8; // 8
	sameFingerI =     	overallScale * 8;
	sameFingerMax =		1.4;
	sfbAboveMaxPenalty = 5; // percentage of overall fitness applied as penalty per % over sfb max 
	travelCost = 		overallScale * 1;	
	                    //0111222333444 
	bracketsCost        = 150000 * overallScale / 8;
	similarSymbolsMath  = 50000 * overallScale / 8;
	similarSymbolsLogic = 50000 * overallScale / 8;
	adHoc               = 50000 * overallScale / 8;
	aestheticsMinor		= 0.01;
	aestheticsMajor		= 0.05;
	aestheticDifferenceThreshold = 100;


	textLayout = LAYOUT_NYMPH;
	// textLayout = "xympbjwouqnhtsg'reiavfdckzl\",."; // nhts
	// textLayout = "xfcpkjwouqnhstg.reiabymdvzl',\"";
	textLayout = "qfcpkjwou;nhstgxreiabymdvzl',.";
	// textLayout = "bympkjwouqnhstg'reiaxfcdvzl\",.";
	// textLayout = "qpcfkjwou;nhstgxreiabydmvzl',.";
	// textLayout = "qympbjwouznhstg'reiavfcdkxl\",.";

	// textLayout = "qylmvbpou~irnsfgtea`jwhcxkd'z^";
	// shiftLayout = "QYLMVBPOU0IRNSFGTEA0JWHCXKD+Z0";
	// symbolLayout = "%*:/#|-$?0,\".=\\!{}_0<>()&@;[]0";

	
	// symbolLayout = "0*/\\~`|&^0;=_:<>!+?-$[{(#%)}]@";
	// symbolLayout = "0*/\\~0|&00;=_:<>!+?-^[{(#%)}]`";
	// textLayout = LAYOUT_QWERTY;
	// textLayout = LAYOUT_COLEMAK;
	// textLayout = LAYOUT_CANARY;
	// textLayout = LAYOUT_MTGAP;	
	// strcpy(doNotMove, "~`^");
	// strcpy(doNotMove, "my");
	
	// strcpy(doNotMove, "0+{}@^&|!0;\"()$`_-<>~*/=00:[]%");
	keepAlphas = 1;
	// noHomeRowC = 1;
	// keepHomeRowLeft = 1;
	// keepHomeRowRight = 1;		  
	doSymbolLayer = 1;
	// forceBracketsHomeRow = 1; 
	// treatAnglesAsBrackets = 1;
	flexibleSymbolLocations = 1;
	ignoreWorkForRareSymbols = 1;
	// forceMirrorOrSameHand = 1;
	// forceBracketMirrors = 1;
	// useRingForTopPinky = 1;

	pinkyOverload =   overallScale; 
	ringOverload =    overallScale;
	indexCorner =     0;
	toCenter =		  0;
	ringJump =        overallScale; // actually hand imbalance penalty 
	handSmooth =	  0; // actually hand imbalance threshold beyond which an exponential penalty is applied; set to >=50 to disable but still report data

	sameFingerM =	 sameFingerI;
	sameFingerR =	 sameFingerI * 5 / 4;
 	sameFingerP =    sameFingerI * 6 / 2;
	sameFingerT =	 sameFingerI;	

 
	halfScissor =    overallScale * 2;
	fullScissor =    halfScissor;
	rowChangeDown =  distance;
	lateralStretch = halfScissor;

	inRoll =		 -overallScale / 4;  // see commented fn in fitness.c
	outRoll =	     -overallScale / 4;// -overallScale; // actually consecutive fingers bonus 
	// includeSymbolRolls = 1;
	homeJump =	     handMove / 2;

	triSplitFinger    = 1; // 1 enables; bigram split finger values are used in calculations
	halfScissorTri    = halfScissor / 3;
	fullScissorTri    = halfScissor * 3 / 2;//overallScale / 8;
	lateralStretchTri = halfScissorTri;//overallScale / 8;
	triOneHand =        3;//  divisor for one hand scissors
	triOutRoll =        1;// same row tri; set to 0 to disable.

	sameHand =          0;//-overallScale * 2; //overallScale;
 	triAlt =            -1; // indeed tri alt for now, commented code exists for alternating rolls // actually divisor for split rolls; can be set to 0 to disable
	triInRoll =         -overallScale / 8;
	triRedirect =       halfScissor / 2;
	triHomeJump =		homeJump / 2;

	shiftCostMono =		overallScale * 4;
	symbolCostMono = 	shiftCostMono;
	shiftCost =	 		overallScale; // these have misleading names. they are penalties for bigrams with 1 on base and 1 off base layer
	symbolCost =     	overallScale;  //  
	doubleShiftCost = 	0; // penalties *or refunds (if negative)* for bigrams on the same (non-base) layer
	doubleSymbolCost = 	-symbolCostMono * 3 / 4; // 
	biLayerSplit =	  	symbolCostMono / 2; // penalty for symbol bigrams on opposite hands
	layerDiffBi =     	1; // overall multiplier for bigrams across different layers (multipiying shiftCost or symbolCost, as it were)
	mixedLayersCost = 	overallScale; // penalty for bigrams across different shifted layers

	if (fullKeyboard == K_KINESIS) {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  8.5;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 11.5;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 22.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 22.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;	
	} else {
		// fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] = 8.75;
		// fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 10.0; 
		// fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 19.75;
		// fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 19.75;
		// fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;	

		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] = 8.75;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 10.0; 
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 19.25;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 19.25;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;
	}

	// percent of key presses allowed to be off the home row (or in the center column) before a penalty is applied; 100 disables
	fingerTravelMaxPercent[0] = fingerTravelMaxPercent[FINGER_COUNT - 1] = 13;//13
	fingerTravelMaxPercent[1] = fingerTravelMaxPercent[FINGER_COUNT - 2] = 33;//33
	fingerTravelMaxPercent[2] = fingerTravelMaxPercent[FINGER_COUNT - 3] = 50;
	fingerTravelMaxPercent[3] = fingerTravelMaxPercent[FINGER_COUNT - 4] = 50;
	fingerTravelMaxPercent[4] = fingerTravelMaxPercent[FINGER_COUNT - 5] = 50;
	


	int baseCost = overallScale;
	fingerWorkCosts[0] = fingerWorkCosts[FINGER_COUNT - 1] = baseCost * 1;
	fingerWorkCosts[1] = fingerWorkCosts[FINGER_COUNT - 2] = baseCost * 1;
	fingerWorkCosts[2] = fingerWorkCosts[FINGER_COUNT - 3] = baseCost * 1;
	fingerWorkCosts[3] = fingerWorkCosts[FINGER_COUNT - 4] = baseCost * 1;
	fingerWorkCosts[4] = fingerWorkCosts[FINGER_COUNT - 5] = baseCost * 1;


	//
	// UNUSED VARIABLES
	//
 
	preferAlternation = 1;
	preferTrigramRolls = 1;
	homeJumpIndex = 0;
	doubleJump =	2; /* Does not compound with homeJump.  */

	rowChangeUp =    0;//overallScale * 2;
}
