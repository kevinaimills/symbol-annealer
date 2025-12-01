/*
 *  fitness.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/10/09.
 *
 *  
 *
 *  Contains functions to calculate the fitness of a keyboard.
 */


#include "keyboard.h"

/*
 * Calculates fitness without score multipliers. Useful for producing 
 * human-readable output.
 */ 
int calcFitnessDirect(Keyboard *k)
{
	if (k->layout[0] == '\0') return 0;

	// calcFitness(k, 1); // Otherwise, k->fitness, k->fingerUsage, and k->fingerWork 
	                // would not get assigned properly.  

	int i;
	k->biLayerChange = 0;
	k->biLayerSplit  = 0;
	k->inRoll     = 0;
	k->outRoll    = 0;
	k->sameHand   = 0;
	k->sameFinger = 0;
	k->rowChange  = 0;
	k->homeJump   = 0;
	k->ringJump   = 0;
	k->toCenter   = 0;
	k->lateralStretch   = 0;
	k->halfScissor   = 0;
	k->fullScissor   = 0;
	k->triSplitFinger = 0;
	k->triLayerChange = 0;
	k->triInRoll = 0;
	k->triOutRoll = 0;
	k->triOneHand = 0;
	k->triAlt = 0;
	k->triHomeJump = 0;
	k->triRedirect = 0;
	k->halfScissorTri = 0;
	k->fullScissorTri = 0;
	k->lateralStretchTri = 0;
	
	for (i = 0; i < diLen; ++i) scoreDigraphDirect(k, digraphs[i].key,
                                                   digraphs[i].value);

	for (i = 0; i < triLen; ++i) scoreTrigraphDirect(k, trigraphs[i].key,
                                                	trigraphs[i].value);

	return 0;
}
 
inline int scoreDigraphDirect(Keyboard *k, char digraph[], int64_t multiplier)
{
	int locs[2];
	int layers[2];
	for (int i = 0; i < 2; ++i) locs[i] = locWithShifted(k, digraph[i]);
	
	layers[0] = locs[0] / ksize;
	layers[1] = locs[1] / ksize;

	locs[0] = locs[0] % ksize;
	locs[1] = locs[1] % ksize;

		if (calcBiLayerChange (locs[0], locs[1], layers[0], layers[1]) != 0) k->biLayerChange	 += multiplier;
		if (calcBiLayerHands (locs[0], locs[1], layers[0], layers[1]) != 0) k->biLayerSplit	 += multiplier;

	if (hand[locs[0]] == hand[locs[1]]) {
		if (calcInRoll    (locs[0], locs[1], layers[0], layers[1]) != 0) k->inRoll     += multiplier;
		if (calcOutRoll   (locs[0], locs[1], layers[0], layers[1]) != 0) k->outRoll    += multiplier;
												   k->sameHand   += multiplier;
		if (calcSameFinger(locs[0], locs[1], layers[0], layers[1]) != 0) k->sameFinger += multiplier;
		if (calcHomeJump  (locs[0], locs[1], layers[0], layers[1]) != 0) k->homeJump   += multiplier; 
		if (calcRingJump  (locs[0], locs[1], layers[0], layers[1]) != 0) k->ringJump   += multiplier;
		if (calcToCenter  (locs[0], locs[1], layers[0], layers[1]) != 0) k->toCenter   += multiplier;
		if (calcRowChange (locs[0], locs[1], layers[0], layers[1]) != 0) k->rowChange  += multiplier;
		if (calcHalfScissor (locs[0], locs[1], layers[0], layers[1]) != 0) k->halfScissor	 += multiplier;
		if (calcFullScissor (locs[0], locs[1], layers[0], layers[1]) != 0) k->fullScissor	 += multiplier;
		if (calcLateralStretch (locs[0], locs[1], layers[0], layers[1]) != 0) k->lateralStretch	 += multiplier;
	}
	
	return 0;
}

inline int scoreTrigraphDirect(Keyboard *k, char trigraph[], int64_t multiplier)
{
	int locs[3];
	int layers[3];
 	for (int i = 0; i < 3; ++i) locs[i] = locWithShifted(k, trigraph[i]);

	layers[0] = locs[0] / ksize;
	layers[1] = locs[1] / ksize;
	layers[2] = locs[2] / ksize;

	locs[0] = locs[0] % ksize;
	locs[1] = locs[1] % ksize;
	locs[2] = locs[2] % ksize;

	if (calcTriSplitFinger (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triSplitFinger     += multiplier;
	if (calcTriInRoll (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triInRoll     += multiplier;
	if (calcTriOutRoll (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triOutRoll     += multiplier;
	if (calcTriOneHand (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triOneHand     += multiplier;
	if (calcTriAlt (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triAlt     += multiplier;
	if (calcTriHomeJump (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triHomeJump     += multiplier;
	if (calcTriRedirect (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->triRedirect     += multiplier;
	if (calcHalfScissorTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->halfScissorTri     += multiplier;
	if (calcFullScissorTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->fullScissorTri     += multiplier;
	if (calcLateralStretchTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]) != 0) k->lateralStretchTri     += multiplier;

	return 0;
}

int preCalculateFitness()
{
	int i, j, k;
	int locs[3];
	int layers[3];

	memset(allDigraphCosts, 0, sizeof(allDigraphsInRoll)); // fine to use sizeof any of them because they're all the same size and type 
	memset(allDigraphsLayerChange, 0, sizeof(allDigraphsInRoll)); 
	memset(allDigraphsHomeJump, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsSameHand, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsSameFinger, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsInRoll, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsOutRoll, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsRowChange, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsRingJump, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsToCenter, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsLayerSplit, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsHalfScissor, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsFullScissor, 0, sizeof(allDigraphsInRoll));
	memset(allDigraphsLateralStretch, 0, sizeof(allDigraphsInRoll));
	
	for (i = 0; i < 3 * ksize; ++i) {
		for (j = 0; j < 3 * ksize; ++j) {

			locs[0] = i % ksize;
            locs[1] = j % ksize;
			layers[0] = i / ksize;
			layers[1] = j / ksize;
			
					allDigraphsLayerChange[i][j] += calcBiLayerChange(locs[0], locs[1], layers[0], layers[1]);
					allDigraphsLayerSplit[i][j] += calcBiLayerHands(locs[0], locs[1], layers[0], layers[1]);

			if (hand[locs[0]] == hand[locs[1]]) {
				allDigraphsSameHand[i][j] += sameHand;
				allDigraphsSameFinger[i][j] += calcSameFinger(locs[0], locs[1], layers[0], layers[1]);

				if (finger[i] != THUMB && finger[j] != THUMB) {
 
					allDigraphsInRoll[i][j] += calcInRoll   (locs[0], locs[1], layers[0], layers[1]);
					allDigraphsOutRoll[i][j] += calcOutRoll  (locs[0], locs[1], layers[0], layers[1]);	
 					allDigraphsRowChange[i][j] += calcRowChange(locs[0], locs[1], layers[0], layers[1]);
					allDigraphsHomeJump[i][j] += calcHomeJump (locs[0], locs[1], layers[0], layers[1]);
					allDigraphsRingJump[i][j] += calcRingJump (locs[0], locs[1], layers[0], layers[1]);
					allDigraphsToCenter[i][j] += calcToCenter (locs[0], locs[1], layers[0], layers[1]);
					allDigraphsHalfScissor[i][j] += calcHalfScissor(locs[0], locs[1], layers[0], layers[1]);
					allDigraphsFullScissor[i][j] += calcFullScissor(locs[0], locs[1], layers[0], layers[1]);
					allDigraphsLateralStretch[i][j] += calcLateralStretch(locs[0], locs[1], layers[0], layers[1]);


				}
			}
		
			allDigraphCosts[i][j] += 
				allDigraphsLayerChange[i][j]
				+ allDigraphsSameHand[i][j]
				+ allDigraphsSameFinger[i][j]
				+ allDigraphsInRoll[i][j]
				+ allDigraphsOutRoll[i][j]
				+ allDigraphsRowChange[i][j]
				+ allDigraphsHomeJump[i][j]
				+ allDigraphsRingJump[i][j]
				+ allDigraphsToCenter[i][j]
				+ allDigraphsLayerSplit[i][j]
				+ allDigraphsHalfScissor[i][j]
				+ allDigraphsFullScissor[i][j]
				+ allDigraphsLateralStretch[i][j]
				;
		}
	}
		
    memset(allTrigraphCosts, 0, sizeof(allTrigraphsLayerChange));  // fine to use sizeof any of them because they're all the same size and type
	memset(allTrigraphsLayerChange, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsInRoll, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsOutRoll, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsSplitFinger, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsOneHand, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsAlt, 0, sizeof(allTrigraphsLayerChange));
	memset(allTrigraphsHomeJump, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsRedirect, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsHalfScissor, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsFullScissor, 0, sizeof(allTrigraphsLayerChange));
    memset(allTrigraphsLateralStretch, 0, sizeof(allTrigraphsLayerChange));
	
	for (i = 0; i < 3 * ksize; ++i) {
			for (j = 0; j < 3 * ksize; ++j) {
				for (k = 0; k < 3 * ksize; ++k) {

				locs[0] = i % ksize;
            	locs[1] = j % ksize;
				locs[2] = k % ksize;
				layers[0] = i / ksize; 
				layers[1] = j / ksize;
				layers[2] = k / ksize;

				if (layers[0] == 2 && layers[1] == 2 && layers[2] == 2) {
					allTrigraphsLayerChange[i][j][k] += doubleSymbolCost;
				} else if (layers[0] == 1 && layers[1] == 1 && layers[2] == 1) {
					allTrigraphsLayerChange[i][j][k] += doubleShiftCost;
				} else if (layers[0] == 0 && layers[1] == 0 && layers[2] == 0) {
					;
				} else {
					if (layers[0] == 1) allTrigraphsLayerChange[i][j][k] += shiftCost;
					else if (layers[0] == 2) allTrigraphsLayerChange[i][j][k] += symbolCost;
					if (layers[1] == 1) allTrigraphsLayerChange[i][j][k] += shiftCost;
					else if (layers[1] == 2) allTrigraphsLayerChange[i][j][k] += symbolCost;
					if (layers[2] == 1) allTrigraphsLayerChange[i][j][k] += shiftCost;
					else if (layers[2] == 2) allTrigraphsLayerChange[i][j][k] += symbolCost;
					
					if (layers[0] == 1 && layers[0] == layers[1]) allTrigraphsLayerChange[i][j][k] -= shiftCost;
					else if (layers[0] == 2 && layers[0] == layers[1]) allTrigraphsLayerChange[i][j][k] -= symbolCost;
					else if (layers[1] == 1 && layers[1] == layers[2]) allTrigraphsLayerChange[i][j][k] -= shiftCost;
					else if (layers[1] == 2 && layers[1] == layers[2]) allTrigraphsLayerChange[i][j][k] -= symbolCost;
				}

				allTrigraphsInRoll[i][j][k] += calcTriInRoll (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsOutRoll[i][j][k] += calcTriOutRoll (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsSplitFinger[i][j][k] += calcTriSplitFinger (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsOneHand[i][j][k] += calcTriOneHand (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsAlt[i][j][k] += calcTriAlt (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsHomeJump[i][j][k] += calcTriHomeJump (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsRedirect[i][j][k] += calcTriRedirect (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsHalfScissor[i][j][k] += calcHalfScissorTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsFullScissor[i][j][k] += calcFullScissorTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);
				allTrigraphsLateralStretch[i][j][k] += calcLateralStretchTri (locs[0], locs[1], locs[2], layers[0], layers[1], layers[2]);

				allTrigraphCosts[i][j][k] +=
					allTrigraphsLayerChange[i][j][k]
					+ allTrigraphsInRoll[i][j][k]
					+ allTrigraphsOutRoll[i][j][k]
					+ allTrigraphsSplitFinger[i][j][k]
					+ allTrigraphsOneHand[i][j][k]
					+ allTrigraphsAlt[i][j][k]
					+ allTrigraphsHomeJump[i][j][k]
					+ allTrigraphsRedirect[i][j][k]
					+ allTrigraphsHalfScissor[i][j][k]
					+ allTrigraphsFullScissor[i][j][k]
					+ allTrigraphsLateralStretch[i][j][k]
					;
			}
		}
	}
		
	return 0;
}

/* 
 * Not guaranteed to set any variables in k other than k->fitness. For 
 * generating detailed output, use calcFitnessDirect().
 */
int calcFitness(Keyboard *k, int generateDetailedOutput)
{
	int i;
	// generateDetailedOutput = 1;
	
	for (i = 0; i < FINGER_COUNT; ++i) {
        k->fingerUsage[i] = 0;
		k->fingerTravel[i] = 0;
	}

	for (i = 0; i < MAX_AESTHETIC_RULES; i++)
		k->aestheticPenalties[i] = 0;
 
	k->fitness    = 0;
	k->layerChange = 0;
	k->distance   = 0;
	k->handTravel = 0;
	k->handImbalance = 0;
	k->fingerWork = 0;
	k->fingerTravelWork = 0;
	k->aesthetics = 0;
	k->biLayerChange = 0;
	k->inRoll     = 0;
	k->outRoll    = 0;
	k->sameHand   = 0;
	k->sameFinger = 0;
	k->sameFingerMax = 0;
	k->rowChange  = 0;
	k->homeJump   = 0;
	k->ringJump   = 0;
	k->toCenter   = 0;
	k->lateralStretch   = 0;
	k->halfScissor   = 0;
	k->fullScissor   = 0;
	k->biLayerSplit  = 0;
	k->triLayerChange = 0;
	k->triSplitFinger = 0;
	k->triInRoll = 0;
	k->triOutRoll = 0;
	k->triOneHand = 0;
	k->triAlt = 0;
	k->triHomeJump = 0;
	k->triRedirect = 0;
	k->halfScissorTri = 0;
	k->fullScissorTri = 0;
	k->lateralStretchTri = 0;

	if (k->layout[0] == '\0') {
		k->fitness = FITNESS_MAX;
		return 0;
	}

	int locs[128];
	for (i = 0; i < 128; ++i) locs[i] = -1;

	/* Calculate all the locations beforehand. This saves a lot of time. */
	for (i = 0; i < ksize; ++i)
		if (printable[i]) {
			locs[(int) k->layout[i]] = i;
			locs[(int) k->shiftedLayout[i]] = ksize + i;
			locs[(int) k->symbolLayer[i]] = ksize * 2 + i;
		}

	for (i = 0; i < monLen; ++i) {
		scoreMonograph(k, monographs[i].key, monographs[i].value, locs, generateDetailedOutput);
	}

	if (generateDetailedOutput) { 
		int loc0;
		int loc1;
		int loc2;
		int64_t multiplier;

		for (i = 0; i < diLen; ++i) {

			loc0 = locs[(int) digraphs[i].key[0]];
			loc1 = locs[(int) digraphs[i].key[1]];
			multiplier = digraphs[i].value;

			k->biLayerChange += allDigraphsLayerChange[loc0][loc1] * multiplier;
			k->homeJump += allDigraphsHomeJump[loc0][loc1] * multiplier;
			k->sameHand += allDigraphsSameHand[loc0][loc1] * multiplier;
			k->sameFinger += allDigraphsSameFinger[loc0][loc1] * multiplier;
			k->inRoll += allDigraphsInRoll[loc0][loc1] * multiplier;
			k->outRoll += allDigraphsOutRoll[loc0][loc1] * multiplier;
			k->rowChange += allDigraphsRowChange[loc0][loc1] * multiplier;
			k->ringJump += allDigraphsRingJump[loc0][loc1] * multiplier;
			k->toCenter += allDigraphsToCenter[loc0][loc1] * multiplier;
			k->biLayerSplit += allDigraphsLayerSplit[loc0][loc1] * multiplier;
			k->halfScissor += allDigraphsHalfScissor[loc0][loc1] * multiplier;
			k->fullScissor += allDigraphsFullScissor[loc0][loc1] * multiplier;
			k->lateralStretch += allDigraphsLateralStretch[loc0][loc1] * multiplier;
			if (hand[loc0] == hand[loc1] && finger[loc0] == finger[loc1] && loc0 != loc1) k->sameFingerMax += multiplier;			
		}
	
		for (i = 0; i < triLen; ++i) {

			loc0 = locs[(int) trigraphs[i].key[0]];
			loc1 = locs[(int) trigraphs[i].key[1]];
			loc2 = locs[(int) trigraphs[i].key[2]];
			multiplier = trigraphs[i].value;

			k->triLayerChange += allTrigraphsLayerChange[loc0][loc1][loc2] * multiplier;
			k->triInRoll += allTrigraphsInRoll[loc0][loc1][loc2] * multiplier;
			k->triOutRoll += allTrigraphsOutRoll[loc0][loc1][loc2] * multiplier;
			k->triSplitFinger += allTrigraphsSplitFinger[loc0][loc1][loc2] * multiplier;
			k->triOneHand += allTrigraphsOneHand[loc0][loc1][loc2] * multiplier;
			k->triAlt += allTrigraphsAlt[loc0][loc1][loc2] * multiplier;
			k->triHomeJump += allTrigraphsHomeJump[loc0][loc1][loc2] * multiplier;
			k->triRedirect += allTrigraphsRedirect[loc0][loc1][loc2] * multiplier;
			k->halfScissorTri += allTrigraphsHalfScissor[loc0][loc1][loc2] * multiplier;
			k->fullScissorTri += allTrigraphsFullScissor[loc0][loc1][loc2] * multiplier;
			k->lateralStretchTri += allTrigraphsLateralStretch[loc0][loc1][loc2] * multiplier;
		}

	} else if (sameFingerMax > 0 && sameFingerMax < 100) {
		int loc0;
		int loc1;
		int64_t multiplier;

		for (i = 0; i < diLen; ++i) {

			loc0 = locs[(int) digraphs[i].key[0]];
			loc1 = locs[(int) digraphs[i].key[1]];
			multiplier = digraphs[i].value;

			k->fitness += allDigraphCosts[loc0][loc1] * multiplier;
			if (hand[loc0] == hand[loc1] && finger[loc0] == finger[loc1] && loc0 != loc1) k->sameFingerMax += multiplier;
		}

		for (i = 0; i < triLen; ++i) {
			k->fitness += allTrigraphCosts[locs[(int) trigraphs[i].key[0]]][locs[(int) trigraphs[i].key[1]]][locs[(int) trigraphs[i].key[2]]] * trigraphs[i].value;
		}
	} else {
		for (i = 0; i < diLen; ++i) {
			k->fitness += allDigraphCosts[locs[(int) digraphs[i].key[0]]][locs[(int) digraphs[i].key[1]]] * digraphs[i].value;
 		}

		for (i = 0; i < triLen; ++i) {
			k->fitness += allTrigraphCosts[locs[(int) trigraphs[i].key[0]]][locs[(int) trigraphs[i].key[1]]][locs[(int) trigraphs[i].key[2]]] * trigraphs[i].value;
		}		
	}
		
	calcFingerWork(k);
	
//  penalty += adHocPenalty(k);
	
 	// for (i = 0; i < 6; ++i)
    //     printf("%d\n", k->pinkyBalance[i]); 
	// k->fitness += (int64_t)k->homeJump;

	k->fitness += k->distance + k->fingerWork + k->layerChange + k->handTravel + k->fingerTravelWork;// + k->aesthetics;
	if (handSmooth < 50) k->fitness += k->handImbalance;
	     
	if (generateDetailedOutput)	k->fitness +=		
		+ k->biLayerChange 
		+ k->sameHand   
		+ k->sameFinger 
		+ k->inRoll     
		+ k->outRoll 
		+ k->rowChange  
		+ k->ringJump
		+ k->homeJump   
		+ k->toCenter   
		+ k->biLayerSplit  
		+ k->lateralStretch   
		+ k->halfScissor   
		+ k->fullScissor   
		+ k->triLayerChange 
		+ k->triSplitFinger 
		+ k->triInRoll 
		+ k->triOutRoll 
		+ k->triOneHand 
		+ k->triAlt 
		+ k->triHomeJump
		+ k->triRedirect 
		+ k->halfScissorTri 
		+ k->fullScissorTri 
		+ k->lateralStretchTri 
		;

	if (sameFingerMax > 0 && sameFingerMax < 100 && (double) ((k->sameFingerMax / (double) totalDi) * 100) > sameFingerMax) {
		k->sameFingerMax = (int64_t) (k->fitness * (double) (((k->sameFingerMax / (double) totalDi) * 100) - sameFingerMax) * sfbAboveMaxPenalty / 100);
		k->fitness += k->sameFingerMax;
	} else {
		k->sameFingerMax = 0;
	}

	if (keepZXCV) k->fitness += calcShortcuts(k);
	if (keepQWERTY) k->fitness += calcQWERTY(k);
	if (keepBrackets) k->fitness += calcBrackets(k);
	if (keepNumbersShifted) k->fitness += calcNumbersShifted(k);
	if (doSymbolLayer) calcAesthetics(k); // MUST be done last, because applies penalties as a percent of total fitness

	return 0;
}

inline int scoreMonograph(Keyboard *k, char monograph, int64_t multiplier,
                        int allLocs[], int generateDetailedOutput)
{
	if (multiplier == 0) return 0;
	int layerCost = 0; 
	int layer = allLocs[(int) monograph] / ksize;
	if (layer == 1) layerCost = shiftCostMono;
	else if (layer == 2) layerCost = symbolCostMono;

	int lc = allLocs[(int) monograph] % ksize;
	if (lc >= 0) {
		k->distance += distanceCosts[lc] * multiplier * distance;
		k->handTravel += handTravelCosts[lc] * multiplier * handMove;
		k->layerChange += multiplier * layerCost;
	}
	
	if (!ignoreWorkForRareSymbols || isalpha(monograph) || monographs[13].value / multiplier <= 50) {
		if (hand[lc] == LEFT) {
			k->fingerUsage[finger[lc]] += multiplier;
		} else {
			k->fingerUsage[FINGER_COUNT - 1 - finger[lc]] += multiplier;
		}

		if (row[lc] != 1 || isCenter[lc]) {
			if (hand[lc] == LEFT) {
				k->fingerTravel[finger[lc]] += multiplier;
			} else {
				k->fingerTravel[FINGER_COUNT - 1 - finger[lc]] += multiplier;
			}
		}
	}

	if (noHomeRowC && row[lc] == 1 && monograph == 'c') k->distance += multiplier * 10000;

	return 0;
}
 
inline int scoreTrigraph(Keyboard *k, char trigraph[], int64_t multiplier,
                        int allLocs[], int generateDetailedOutput)
{
	int loc0 = allLocs[(int) trigraph[0]];
	int loc1 = allLocs[(int) trigraph[1]];
	int loc2 = allLocs[(int) trigraph[2]];

	k->triLayerChange += allTrigraphsLayerChange[loc0][loc1][loc2] * multiplier;
	k->triInRoll += allTrigraphsInRoll[loc0][loc1][loc2] * multiplier;
	k->triOutRoll += allTrigraphsOutRoll[loc0][loc1][loc2] * multiplier;
	k->triSplitFinger += allTrigraphsSplitFinger[loc0][loc1][loc2] * multiplier;
	k->triOneHand += allTrigraphsOneHand[loc0][loc1][loc2] * multiplier;
	k->triAlt += allTrigraphsAlt[loc0][loc1][loc2] * multiplier;
	k->triHomeJump += allTrigraphsHomeJump[loc0][loc1][loc2] * multiplier;
	k->triRedirect += allTrigraphsRedirect[loc0][loc1][loc2] * multiplier;
	k->halfScissorTri += allTrigraphsHalfScissor[loc0][loc1][loc2] * multiplier;
	k->fullScissorTri += allTrigraphsFullScissor[loc0][loc1][loc2] * multiplier;
	k->lateralStretchTri += allTrigraphsLateralStretch[loc0][loc1][loc2] * multiplier;
 
    return 0;
}

inline int scoreDigraph(Keyboard *k, char digraph[], int64_t multiplier,
                        int allLocs[], int generateDetailedOutput)
{
	int loc0 = allLocs[(int) digraph[0]];
	int loc1 = allLocs[(int) digraph[1]];

	k->biLayerChange += allDigraphsLayerChange[loc0][loc1] * multiplier;
	k->homeJump += allDigraphsHomeJump[loc0][loc1] * multiplier;
	k->sameHand += allDigraphsSameHand[loc0][loc1] * multiplier;
	k->sameFinger += allDigraphsSameFinger[loc0][loc1] * multiplier;
	k->inRoll += allDigraphsInRoll[loc0][loc1] * multiplier;
	k->outRoll += allDigraphsOutRoll[loc0][loc1] * multiplier;
	k->rowChange += allDigraphsRowChange[loc0][loc1] * multiplier;
	k->ringJump += allDigraphsRingJump[loc0][loc1] * multiplier;
	k->toCenter += allDigraphsToCenter[loc0][loc1] * multiplier;
	k->biLayerSplit += allDigraphsLayerSplit[loc0][loc1] * multiplier;
	k->halfScissor += allDigraphsHalfScissor[loc0][loc1] * multiplier;
	k->fullScissor += allDigraphsFullScissor[loc0][loc1] * multiplier;
	k->lateralStretch += allDigraphsLateralStretch[loc0][loc1] * multiplier;
 
    return 0;
}

/* Requires that k->fingerUsage has been calculated. */
inline int calcFingerWork(Keyboard *k)
{
	int64_t total = 0;
	int i;
	double usage, percentMax, difference, usageLeft, usageRight, exponentialPenalty, actualPenalty;
	
	for (i = 0; i < FINGER_COUNT; ++i)
		total += k->fingerUsage[i];

	k->fingerWork = 0;
	k->fingerTravelWork = 0;
	
	for (i = 0; i < FINGER_COUNT; ++i) {
		usage = k->fingerUsage[i];
		percentMax = fingerPercentMaxes[i];
		
		if (100*usage/total > percentMax) {
			difference = (100*usage/total - percentMax);// * total / 100;
			exponentialPenalty = ((pow(difference * 5, 2) / 16));
			actualPenalty = difference > exponentialPenalty ? difference : exponentialPenalty;
			k->fingerWork += (int64_t) (fingerWorkCosts[i] * actualPenalty * total / 100);
		}
	}
	
	usageLeft = (100 * (k->fingerUsage[0] + k->fingerUsage[1] + k->fingerUsage[2] + k->fingerUsage[3] + k->fingerUsage[4]) / (double) total);
	usageRight = (100 * (k->fingerUsage[5] + k->fingerUsage[6] + k->fingerUsage[7] + k->fingerUsage[8] + k->fingerUsage[9]) / (double) total);

	if (fabs(usageLeft - usageRight) > handSmooth || handSmooth >= 50) {
		difference = fabs(usageLeft - usageRight);
		exponentialPenalty = difference > 2 ? pow(difference / 2, 2) : difference / 2;
		k->handImbalance += (int64_t) (exponentialPenalty * ringJump * total / 500);
	}
	
	int64_t allowedFingerTravel[FINGER_COUNT];

	for (i = 0; i < FINGER_COUNT; i++) {
		allowedFingerTravel[i] = (int64_t) (fingerPercentMaxes[i] * fingerTravelMaxPercent[i] * total / 10000);
		if (k->fingerTravel[i] > allowedFingerTravel[i]) {
			k->fingerTravelWork += (k->fingerTravel[i] - allowedFingerTravel[i]) * travelCost;
		}
	}

	return 0;
}

inline int64_t calcShortcuts(Keyboard *k)
{
	int64_t result;
	result = 
	      shortcutCosts[locIgnoreShifted(k, 'z')] * (int64_t) zCost
		+ shortcutCosts[locIgnoreShifted(k, 'x')] * (int64_t) xCost
		+ shortcutCosts[locIgnoreShifted(k, 'c')] * (int64_t) cCost
		+ shortcutCosts[locIgnoreShifted(k, 'v')] * (int64_t) vCost;
		
	return result * (totalMon / monLen);
}

inline int64_t calcQWERTY(Keyboard *k)
{
	NOT_WORK_WITH_FULL_KEYBOARD("calcQWERTY")
	int64_t result = 0;
	int64_t averageMon = totalMon / 30;

	int i, pos;
	for (i = 0; i < 30; ++i) {
		if ((pos = locIgnoreShifted(k, qwerty[i])) != i) result += qwertyPosCost * averageMon;
		if (finger[pos] != finger[i]) result += qwertyFingerCost * averageMon;
		if (hand[pos] != hand[i]) result += qwertyHandCost * averageMon;
	}
	
	return result;
}

inline int64_t calcBrackets(Keyboard *k)
{
	return 0;
}

void calcAesthetics(Keyboard *k) {

	k->nextAestheticRule = 0;
	
	// additionalSFBPenalty(k, '$', '_', aestheticsMajor); 
	// additionalSFBPenalty(k, ')', ':', aestheticsMajor);
	// additionalSFBPenalty(k, '(', '{', aestheticsMajor);

	clusterPairs(k, (char[]){'+', '-', '*', '/'}, 4, aestheticsMajor);
	alignPairs(k, (char[]){'(', ')', '{', '}', '[', ']', '<', '>'}, 8, aestheticsMajor);
	sameRelation(k, (char[]){'(', ')', '{', '}', '[', ']', '<', '>'}, 8, aestheticsMajor * 2);
	cluster(k, (char[]){'&', '|', '!', '^'}, 4, aestheticsMajor);
	cluster(k, (char[]){'(', ')'}, 2, aestheticsMajor);
	cluster(k, (char[]){'[', ']'}, 2, aestheticsMajor);
	cluster(k, (char[]){'{', '}'}, 2, aestheticsMajor);
	cluster(k, (char[]){'<', '>'}, 2, aestheticsMajor);
	applyAdHocPenalties(k, aestheticsMajor);

	for (int i = 0; i < k->nextAestheticRule; i++) {
		k->aesthetics += (int64_t) (k->fitness * k->aestheticPenalties[i] / 100);
		if (k->aestheticPenalties[i] == aestheticsMinor) k->aestheticPenalties[i] = 0;	
	}

	k->fitness += k->aesthetics;

}  

void applyAdHocPenalties(Keyboard *k, double cost)
{
	int penalty = 0;

	int loc0 = locWithShifted(k, '/');
	int loc1 = locWithShifted(k, 'm');
	int loc3 = locWithShifted(k, '_');
	int loc38 = locWithShifted(k, '$');

	if (loc38 / ksize == 0) penalty += 1;
	if (loc3 / ksize == 0) penalty += 1;
	if (hand[loc0] == hand[loc1] && finger[loc0] == finger[loc1] && row[loc0] != row[loc1]) penalty += 1;

	saveAestheticPenalty(k, penalty * cost);
}

void saveAestheticPenalty(Keyboard *k, double penalty) {
	k->aestheticPenalties[k->nextAestheticRule] = penalty;
	k->nextAestheticRule++;
}

void sameRelation(Keyboard *k, char chars[], int size, double cost) {
	
	if (size % 2 != 0 || size < 4) {
		printf("Invalid same-relation request.");
		exit(-1);
	}

	float differentRelation = 0;
	int rowStag[size / 2];
	int colStag[size / 2];
	int sameHand[size / 2];
	int sameLayer[size / 2];

	for (int i = 0; i < size; i=i+2) {
		int loc1 = locWithShifted(k, chars[i]); 
		int loc2 = locWithShifted(k, chars[i+1]);
		rowStag[i/2] = (hand[loc1] == LEFT) ? row[loc1] - row[loc2] : row[loc2] - row[loc1];
		colStag[i/2] = (hand[loc1] == LEFT) ? column[loc1] - column[loc2] : column[loc2] - column[loc1];
		sameHand[i/2] = hand[loc1] - hand[loc2];
		sameLayer[i/2] = loc1 / ksize == loc2 / ksize;
	}

	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size / 2; j++) {
			if (i == j) continue;
 			if (rowStag[i] != rowStag[j]) differentRelation++;
		 	if (colStag[i] != colStag[j]) differentRelation++;
			if (sameHand[i] != sameHand[j]) differentRelation++;
			if (sameLayer[i] != sameLayer[j]) differentRelation++;
		}
	}

	/* 
		Why the division and multiplication?

		1. We initially want a number between 0 and 1, to represent the extent to which the rule is satisfied. Since there are 4 potential 
		differences, we have a number between 0 and 4. So divide by 4.

		2. Because of how we loop, the relation between each pair gets calculated twice. So divide by 2.

		3. Differences are calculated between each pair and each other pair. So again, to get a number between 0 and 1, divide by
		the number of pairs minus 1.

		4. But the difficulty of satisfying the rule increases as the number of pairs increases. So, to give the rule a realistic
		chance of being satisfied that allows for a penalty score roughly in line with the other penalty scores (used for the other
		aesthetic functions), we multiply the cost by the number of pairs.
	*/

	saveAestheticPenalty(k, differentRelation / (8 * (size / 2 - 1)) * (size / 2) * cost);
}

void alignPairs(Keyboard *k, char chars[], int size, double cost) {
	
	if (size % 2 != 0) {
		printf("Invalid alignment request.");
		exit(-1);
	}

	int notAligned = 0;

	for (int i = 0; i < size; i=i+2) {
		int loc1 = locWithShifted(k, chars[i]); 
		int loc2 = locWithShifted(k, chars[i+1]);
		if (hand[loc1] != hand[loc2]) continue;
		else if (hand[loc1] == LEFT && column[loc1] > column[loc2]) notAligned += 1;
		else if (hand[loc1] == RIGHT && column[loc1] < column[loc2]) notAligned += 1;
	}

	saveAestheticPenalty(k, notAligned * cost);
}

int areMirrors(Keyboard *k, char char1, char char2) {
	//  return 0;
	int loc1 = locWithShifted(k, char1); 
	int loc2 = locWithShifted(k, char2);
	// return 0;
	// printf(" %c %c ", char1, char2);
	if (column[loc1] == column[loc2] && row[loc1] == row[loc2] && loc1 / ksize == loc2 / ksize) return 1;
	else return 0;
}

int areMirrorsPairs(Keyboard *k, char char1, char char2, char char3, char char4) {

	if (
		(areMirrors(k, char1, char3) && areMirrors(k, char2, char4))
		||
		(areMirrors(k, char2, char3) && areMirrors(k, char1, char4))
	) return 1;
	else return 0;
}


void allMirrors(Keyboard *k, char chars[], int size, double cost)
{
	if (size < 2 || size % 2 != 0) return;

	int notMirrors = 0;

	for (int i = 0; i < size; i=i+2)
		if (areMirrors(k, chars[i], chars[i+1]) == 0)
			notMirrors = 1;

	saveAestheticPenalty(k, notMirrors * cost);
}	

void cluster(Keyboard *k, char chars[], int size, double cost) {
	
	float separation = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			separation += calcClustering(k, chars[i], chars[j]) / 2;
		}		
	}

	saveAestheticPenalty(k, separation / size * cost);
}

void clusterPairs(Keyboard *k, char chars[], int size, double cost) {
	
	if (size % 2 != 0) {
		printf("Invalid clustering request.");
		exit(-1);
	}

	float separation = 0;

	for (int i = 0; i < size; i=i+2)
		separation += calcClustering(k, chars[i], chars[i+1]);

	for (int i = 0; i < size; i=i+2) {
		for (int j = 0; j < size; j=j+2) {
			if (i == j) continue;
			separation += calcClusteringPairs(k, chars[i], chars[i+1], chars[j], chars[j+1]) / 2;
		}		
	}

	saveAestheticPenalty(k, separation / size * cost);
}

float calcClustering(Keyboard *k, char char1, char char2) {
	if (areMirrors(k, char1, char2)) return 0;

	float separation = 0;
	int loc1 = locWithShifted(k, char1); 
	int loc2 = locWithShifted(k, char2);
	
	if (hand[loc1] != hand[loc2] || loc1 / ksize != loc2 / ksize) separation = 4;
	else {
		separation += (row[loc1] != row[loc2] && column[loc1] != column[loc2]);
		separation += (row[loc1] != row[loc2] || abs(column[loc1] - column[loc2]) != 1 || isCenter[loc1] || isCenter[loc2] 
			|| (finger[loc1] == PINKY && row[loc1] != 1) || (finger[loc2] == PINKY && row[loc2] != 1));
	}
 	
	return separation / 4;
}

float calcClusteringPairs(Keyboard *k, char char1, char char2, char char3, char char4) {
	float clusteringToEach[4];
	float separation = 0;

	clusteringToEach[0] = calcClustering(k, char1, char3);
	clusteringToEach[1] = calcClustering(k, char1, char4);
	clusteringToEach[2] = calcClustering(k, char2, char3);
	clusteringToEach[3] = calcClustering(k, char2, char4);

	separation += (clusteringToEach[0] < clusteringToEach[1] ? clusteringToEach[0] : clusteringToEach[1]);
	separation += (clusteringToEach[2] < clusteringToEach[3] ? clusteringToEach[2] : clusteringToEach[3]);
	return separation / 2;
}

int calcSeparation(Keyboard *k, char char1, char char2) {
	int separation = 0;
	int loc1 = locWithShifted(k, char1); 
	int loc2 = locWithShifted(k, char2);

	separation += abs(loc1 / ksize - loc2 / ksize) * 5;		
	separation += abs(hand[loc1] - hand[loc2]) * 5;	
	separation += abs(row[loc1] - row[loc2]);
	separation += abs(column[loc1] - column[loc2]);
	
	if (separation > 5) separation = 5;
	if (areMirrors(k, char1, char2)) separation = 1;

	return separation;
}

void keepAdjacent(Keyboard *k, char char1, char char2, double cost) {
	int loc1 = locWithShifted(k, char1); 
	int loc2 = locWithShifted(k, char2);
	int notAdjacent = 0;

	if (abs(column[loc1] - column[loc2]) != 1 || row[loc1] != row[loc2])
		notAdjacent = 1;	

	saveAestheticPenalty(k, notAdjacent * cost);
}


void sameMirrorRule(Keyboard *k, char char1, char char2, char char3, char char4, double cost) {
	int numMirrors = areMirrors(k, char1, char2) + areMirrors(k, char3, char4);
	saveAestheticPenalty(k, numMirrors % 2);
}

void togetherOrMirrored(Keyboard *k, char firstChar, char secondChar, double cost) {

	int base = 2;
	int loc1 = locWithShifted(k, firstChar); 
	int loc2 = locWithShifted(k, secondChar);

	if (hand[loc1] == hand[loc2] && loc1 / ksize == loc2 / ksize) {
		if (cost == aestheticsMinor || (!isCenter[loc1] && !isCenter[loc2])) {
			base -= 1;
			if (row[loc1] == row[loc2]) base -= 1;
 			else if (finger[loc1] == finger[loc2]) base -= 1; 
		} 
		// else if (!isCenter[loc1] && !isCenter[loc2]) {
		// 	if (!isCenter[loc1] && !isCenter[loc2]) base -= 1;
		// 	if (row[loc1] == row[loc2] && abs(column[loc1] - column[loc2]) == 1 && !isCenter[loc1] && !isCenter[loc2]) base -= 1;
 		// 	if (finger[loc1] == finger[loc2] && !isCenter[loc1] && !isCenter[loc2]) base -= 1; 
		// }
	} else {
		if (column[loc1] == column[loc2] && row[loc1] == row[loc2] && loc1 / ksize == loc2 / ksize) base -= 2;
	}

 	saveAestheticPenalty(k, base * cost / 2);
}

void useShiftPair(Keyboard *k, char firstChar, char secondChar, double cost) {
	int loc1 = locWithShifted(k, firstChar); 
	int loc2 = locWithShifted(k, secondChar);
	int notUsingPair = 0;

	if (!(hand[loc1] == hand[loc2] && column[loc1] == column[loc2] && row[loc1] == row[loc2] && loc1 / ksize == 0 && loc2 / ksize == 1)) 
		notUsingPair = 1;
	
	saveAestheticPenalty(k, notUsingPair * cost);
}

void notTerribleLocation(Keyboard *k, char char1, double cost) {
	int loc1 = locWithShifted(k, char1); 

	int isTerrible = 0;

	if (finger[loc1] == PINKY && row[loc1] != 1) isTerrible = 1;
	else if (isCenter[loc1] && row[loc1] == 2 && loc1 / ksize != 0) isTerrible = 1;

	saveAestheticPenalty(k, isTerrible * cost);
}

void additionalSFBPenalty(Keyboard *k, char firstChar, char secondChar, double cost) {
	int loc1 = locWithShifted(k, firstChar); 
	int loc2 = locWithShifted(k, secondChar);
	// printf("- %d %d -", loc1, loc2);
	int mult = (abs(row[loc1] - row[loc2]) == 2) ? 2 : 1;
	int isSFB = 0;

	if (hand[loc1] == hand[loc2] && finger[loc1] == finger[loc2])
		isSFB = 1;

	saveAestheticPenalty(k, isSFB * mult);
}

void keepSameHand(Keyboard *k, char chars[], int size, double cost)
{
	if (size < 2) return;

	int layers[size];
	int lHand = 0;
	int rHand = 0;
	int usedCenter = 0;

	for (int i = 0; i < size; i++) {
		int loc = locWithShifted(k, chars[i]);
		layers[i] = loc / ksize;
		usedCenter += isCenter[loc];
		if (hand[loc] == LEFT) lHand++;
		else rHand++;
	}

	int layerDiff = 0;
	for (int i = 1; i < size; i++) {
		if (layers[i] != layers[0]) {
			layerDiff = 1;
			break;
		}
	}

	int notSameHand = ((lHand != 0 && rHand != 0) || layerDiff || (cost != aestheticsMinor && usedCenter));
	saveAestheticPenalty(k, notSameHand * cost);
}	

void keepSameRow(Keyboard *k, char chars[], int size, double cost)
{
	if (size < 2) return;

	int layers[size];
	int lHand = 0;
	int rHand = 0;
	int row0 = 0;
	int row1 = 0;
	int row2 = 0;
	int usedCenter = 0;

	for (int i = 0; i < size; i++) {
		int loc = locWithShifted(k, chars[i]);
 		
		layers[i] = loc / ksize;
		
		// usedCenter += isCenter[loc];
		
		if (hand[loc] == LEFT) lHand++;
		else rHand++;
		
		if (row[loc] == 0) row0++;
		else if (row[loc] == 1) row1++;
		else row2++;
	}

	int layerDiff = 0;
	for (int i = 1; i < size; i++) {
		if (layers[i] != layers[0]) {
			layerDiff = 1;
			break;
		}
	}

	int emptyRows = (row0 == 0) + (row1 == 0) + (row2 == 0);
	int notSameRow = (emptyRows < 2 || layerDiff || usedCenter || (lHand != 0 && rHand != 0));

	saveAestheticPenalty(k, notSameRow * cost);
}	

inline int64_t calcBracketsGeneric(Keyboard *k, char openChar, char closeChar)
{
	return 0;
}

inline int64_t calcNumbersShifted(Keyboard *k)
{
	int64_t score = 0;
	
	char c;
	for (c = '0'; c <= '9'; ++c)
		if (strchr(k->shiftedLayout, c))
			score += numbersShiftedCost;
	
	return score;
}

inline int calcInRoll(int loc0, int loc1, int layer0, int layer1)
{ 
 	if (hand[loc0] != hand[loc1] || row[loc0] != row[loc1] || isCenterOrOutside[loc0] || isCenterOrOutside[loc1]
	|| (!includeSymbolRolls && (layer0 != 0 || layer1 != 0))) 
		return 0;
 
	if ((finger[loc0] == INDEX || finger[loc0] == MIDDLE || finger[loc0] == RING) 
	&& (finger[loc1] == INDEX || finger[loc1] == MIDDLE || finger[loc1] == RING))
		return inRoll / (int)(pow(2, layerDiff(layer0, layer1)));
 	
	return 0;
}

inline int calcOutRoll(int loc0, int loc1, int layer0, int layer1)
{
	if (hand[loc0] != hand[loc1] || row[loc0] != row[loc1] || isCenterOrOutside[loc0] || isCenterOrOutside[loc1]
	|| (!includeSymbolRolls && (layer0 != 0 || layer1 != 0))) 
		return 0;

	if (abs(finger[loc0] - finger[loc1]) == 1) 
		return outRoll / (int)(pow(2, layerDiff(layer0, layer1)));
 	
	return 0; 
}

inline int calcSameFinger(int loc0, int loc1, int layer0, int layer1)
{
	if (loc0 == loc1 || finger[loc0] != finger[loc1] || (row[loc0] == row[loc1] && layer0 != layer1 && isCenter[loc0] == isCenter[loc1])) return 0;

	int mult = abs(row[loc0] - row[loc1]);
	if (row[loc0] == row[loc1]) mult = 1;

	if ((isCenter[loc0] || isCenter[loc1]) && !(isCenter[loc0] && isCenter[loc1])) mult *= 2;

	switch (finger[loc0]) {
		case PINKY:
			return sameFingerP * mult;
			break;
		case RING:
			return sameFingerR * mult;
			break;
		case MIDDLE:
			return sameFingerM * mult;
			break;
		case INDEX:
			return sameFingerI * mult;
			break;
		case THUMB:
			return sameFingerT * mult;
			break;
	}
	
	return 0;
}

inline int calcRowChange(int loc0, int loc1, int layer0, int layer1)
{
	if (row[loc0] != row[loc1]) return 0;
	if (isCenter[loc0] || isCenter[loc1]) return 0;
	// if (finger[loc0] == finger[loc1]) return 0;

	int fin0 = finger[loc0];
	int fin1 = finger[loc1];
	int base = 0;

	if (row[loc0] == 0) {
		if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == RING || fin1 == RING)) base = -1;
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = -1; 
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = -1; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 
		else if ((fin0 == MIDDLE || fin1 == MIDDLE) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 
	}

	else if (row[loc0] == 1) {
		if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == RING || fin1 == RING)) base = 0; 
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = 0; 
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == INDEX || fin1 == INDEX)) base = 0; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = 0; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == INDEX || fin1 == INDEX)) base = 0; 
		else if ((fin0 == MIDDLE || fin1 == MIDDLE) && (fin0 == INDEX || fin1 == INDEX)) base = 0; 			
	}

	else {
		if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == RING || fin1 == RING)) base = -1; 
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = -1; 
		else if ((fin0 == PINKY || fin1 == PINKY) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == MIDDLE || fin1 == MIDDLE)) base = -1; 
		else if ((fin0 == RING || fin1 == RING) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 
		else if ((fin0 == MIDDLE || fin1 == MIDDLE) && (fin0 == INDEX || fin1 == INDEX)) base = -1; 			
	}

	return rowChangeDown * base;
}

inline int calcBiLayerChange(int loc0, int loc1, int layer0, int layer1)
{
	int cost = 0;
	 
	if (layer0 == 2 && layer1 == 2) {
		cost = doubleSymbolCost;
	} else if ((layer0 == 2 && layer1 == 1) || (layer0 == 1 && layer1 == 2)) {
		cost = mixedLayersCost;
	} else if (layer0 == 1 && layer1 == 1) {
		cost = doubleShiftCost;
	} else if ((layer0 == 0 && layer1 == 2) || (layer0 == 2 && layer1 == 0)) {
		cost = symbolCost;
	} else if ((layer0 == 0 && layer1 == 1) || (layer0 == 1 && layer1 == 0)) {
		cost = shiftCost;
	}

	return cost * layerDiffBi;
}

inline int calcBiLayerHands(int loc0, int loc1, int layer0, int layer1)
{
	if (layer0 == layer1 && layer0 == 2 && hand[loc0] != hand[loc1] && biLayerSplit != 0) return biLayerSplit; 
	else return 0;
}

inline int calcHalfScissor(int loc0, int loc1, int layer0, int layer1)
{
	if (hand[loc0] != hand[loc1] || abs(row[loc0] - row[loc1]) != 1) return 0;

	int lf; // lower finger
	int uf;
	int lfr;
	int ufr;
	int base = 0;
	// int cntr = (isCenter[loc0] || isCenter[loc1]);

	if (row[loc0] > row[loc1]) { // greater number means lower row
		lf = finger[loc0];
		uf = finger[loc1];
		lfr = row[loc0];
		ufr = row[loc1];
	} else {
		lf = finger[loc1];
		uf = finger[loc0];
		lfr = row[loc1];
		ufr = row[loc0];
	}

	if (!(isCenter[loc0] || isCenter[loc1])) {

		if (ufr == 1) {
			switch (lf) {
				case PINKY:
					if (uf == RING) base = 1;
					if (uf == MIDDLE) base = 0;
					if (uf == INDEX) base = 0;
					break;
				case RING:
					if (uf == PINKY) base = 1;
 					if (uf == MIDDLE) base = 1;
					if (uf == INDEX) base = 1;
					break;
				case MIDDLE:
					if (uf == PINKY) base = 1;
					if (uf == RING) base = 1; 
					if (uf == INDEX) base = 0;
					break;
				case INDEX:
					if (uf == PINKY) base = 0;
					if (uf == RING) base = 0;
					if (uf == MIDDLE) base = 0;
 					break;
			}
		}

		if (lfr == 1) {
			switch (uf) {
				case PINKY:
 					if (lf == RING) base = 2;
					if (lf == MIDDLE) base = 2;
					if (lf == INDEX) base = 1;
					break;
				case RING:
					if (lf == PINKY) base = 2;
 					if (lf == MIDDLE) base = 1;
					if (lf == INDEX) base = 0;
					break;
				case MIDDLE:
					if (lf == PINKY) base = 0;
					if (lf == RING) base = 1;
 					if (lf == INDEX) base = 1;
					break;
				case INDEX:
					if (lf == PINKY) base = 1; // debated: 1
					if (lf == RING) base = 1;
					if (lf == MIDDLE) base = 1;
 					break;
			}
		}

	} else {

		if (ufr == 1) {
			if (lf == PINKY) base = 2; // 2, 3, 3
			if (lf == RING) base = 3;
			if (lf == MIDDLE) base = 4;
			if (lf == INDEX) {
				switch (uf) {
					case PINKY:	
						base = 1;
						break;			
					case RING:
						base = 2;
						break;
					case MIDDLE:
						base = 3;
						break;
				}
			}
		}

		if (lfr == 1) {
			if (uf == PINKY) base = 2;
			if (uf == RING) base = 2;
			if (uf == MIDDLE) base = 2;
			if (uf == INDEX) {
				switch (lf) {
					case PINKY:	
						base = 2;
						break;				
					case RING:
						base = 2;
						break;
					case MIDDLE:
						base = 2;
						break;
				}
			}
		}		
	}

	return halfScissor * base;
}


inline int calcFullScissor(int loc0, int loc1, int layer0, int layer1)
{
	if (hand[loc0] != hand[loc1] || abs(row[loc0] - row[loc1]) != 2) return 0;

	int lf; // lower finger
	int uf;
	int base = 0;
	int cntr = (isCenter[loc0] || isCenter[loc1]);

	if (row[loc0] > row[loc1]) { // greater number means lower row
		lf = finger[loc0];
		uf = finger[loc1];
	} else {
		lf = finger[loc1];
		uf = finger[loc0];
	}

	switch (lf) {
		case PINKY:
			switch (uf) {					
				case RING:
					base = 4;
					break;
				case MIDDLE:
					base = 2;
					break;
				case INDEX:
					if (!cntr) base = 2;
					else base = 2;
					break;
			}
			break;

		case RING:
			switch (uf) {					
				case PINKY:
					base = 5;
					break;
				case MIDDLE:
					base = 4;
					break;
				case INDEX:
					if (!cntr) base = 4;
					else base = 5;
					break;
			}
			break;

		case MIDDLE:
			switch (uf) {					
				case PINKY:
					base = 4;
					break;
				case RING: 
					base = 3;
					break;
				case INDEX:
					if (!cntr) base = 3;
					else base = 4;
					break;
			}
			break;
			
		case INDEX:
			switch (uf) {				
				case PINKY:
					if (!cntr) base = 2;
					else base = 3;
					break;
				case RING:
					if (!cntr) base = 2;//1
					else base = 3;
					break; 
				case MIDDLE:
					if (!cntr) base = 1;//1
					else base = 2;
					break;
			}
			break;
	}

	// if (base > 4) base = 4;
//	if (base == 0) return handWarp / 2;
	return fullScissor * base;
}

inline int calcLateralStretch(int loc0, int loc1, int layer0, int layer1)
{
	// cases where the keys are not on the same row are handled under the scissor logic
	if (row[loc0] != row[loc1] || finger[loc0] == finger[loc1]) return 0;
	if (!(isCenter[loc0] || isCenter[loc1])) return 0;

	int fin0 = finger[loc0];
	int fin1 = finger[loc1];
	int base = 0;

	if (row[loc0] == 0) {
		if ((fin0 == PINKY || fin1 == PINKY)) base = 0; 
		if ((fin0 == RING || fin1 == RING)) base = 0; 
		if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 2; 
	}

	else if (row[loc0] == 1) {
		if ((fin0 == PINKY || fin1 == PINKY)) base = 0; 
		if ((fin0 == RING || fin1 == RING)) base = 2; 
		if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 4; 
	}

	else {
		if ((fin0 == PINKY || fin1 == PINKY)) base = 2; // 2, 3, 3
		if ((fin0 == RING || fin1 == RING)) base = 4; 
		if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 4; 	
	}

	return lateralStretch * base;

	// if (row[loc0] == 0) {
	// 	if ((fin0 == PINKY || fin1 == PINKY)) base = 0; 
	// 	if ((fin0 == RING || fin1 == RING)) base = 2; 
	// 	if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 2; 
	// }

	// else if (row[loc0] == 1) {
	// 	if ((fin0 == PINKY || fin1 == PINKY)) base = 0;
	// 	if ((fin0 == RING || fin1 == RING)) base = 2; 
	// 	if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 2; 
	// }

	// else {
	// 	if ((fin0 == PINKY || fin1 == PINKY)) base = 1; 
	// 	if ((fin0 == RING || fin1 == RING)) base = 2; 
	// 	if ((fin0 == MIDDLE || fin1 == MIDDLE)) base = 4; 	
	// }

}

inline int calcHomeJump(int loc0, int loc1, int layer0, int layer1)
{
	return 0;

	if (abs(row[loc0] - row[loc1]) >= 2) return homeJump;
	else return 0;

	// if ((handTravelCosts[loc0] == 0 || handTravelCosts[loc1] == 0) 
	// 	|| abs(finger[loc0] - finger[loc1]) > 2
	// 	|| abs(row[loc0] - row[loc1]) < 2 
	// 	|| (isCenter[loc0] && isCenter[loc1])
	// ) return 0;
	// else return (handTravelCosts[loc0] + handTravelCosts[loc1]) * homeJump;
}

inline int calcRingJump(int loc0, int loc1, int layer0, int layer1) // actually calcDoubleTap
{
	if (loc0 != loc1 || layer0 != layer1) return 0;

	// int layerCost = 0;
	// if (layer0 == 1 && layer1 == 1) layerCost = doubleShiftCost;
	// else if (layer0 == 2 && layer1 == 2) layerCost = doubleSymbolCost;
	// else {
	// 	if (layer0 == 1) layerCost += shiftCost;
	// 	else if (layer0 == 2) layerCost += symbolCost;

	// 	if (layer1 == 1) layerCost += shiftCost;
	// 	else if (layer1 == 2) layerCost += symbolCost;

	// 	if (layer0 != layer1) layerCost += mixedLayersCost;
	// }
	
	switch (finger[loc0]) {
		case PINKY:
			return sameFingerP * 3 / 4; 
			break;
		case RING:
			return sameFingerR / 8; 
			break;
		case MIDDLE:
			return 0; 
			break;
		case INDEX:
			return 0; 
			break;
		case THUMB:
			return 0; 
			break;
	}
	
	return 0;

//	if ((finger[loc0] == PINKY && finger[loc1] == MIDDLE) || 
//			(finger[loc0] == MIDDLE && finger[loc1] == PINKY)) return ringJump;
//	else return 0; 
}

inline int calcToCenter(int loc0, int loc1, int layer0, int layer1)
{
	if (isCenter[loc0] ^ isCenter[loc1]) return toCenter;
	else return 0;
}

inline int calcTriSplitFinger (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) 
{ 
	if (hand[loc0] == hand[loc2] && finger[loc0] == finger[loc2] && loc0 != loc2) {

		int base = 0;

		switch (finger[loc0]) {
			case PINKY:
				base = sameFingerP / 2;
				if (abs(row[loc0] - row[loc2]) >= 2) base = sameFingerP * 3 / 2;
				else if ((row[loc0] == 0 || row[loc2] == 0) && (hand[loc1] == hand[loc0] && (finger[loc1] == RING || finger[loc1] == MIDDLE))) base = sameFingerP;
				break;
			case RING:
				base = sameFingerR / 4;
				if (abs(row[loc0] - row[loc2]) >= 2) base = sameFingerR;
				break;
			case MIDDLE: 
				base = 0;
				if (abs(row[loc0] - row[loc2]) >= 2) base = sameFingerM / 8;
				break;
			case INDEX:
				base = 0;
				if (abs(row[loc0] - row[loc2]) >= 2) base = sameFingerI / 4;
				break;
			case THUMB:
				base = sameFingerT / 4;
				break;
		}

		return base * triSplitFinger;
		// return (calcSameFinger(loc0, loc2, layer0, layer2) / scale / div) * triSplitFinger * mult; 
	}

	return 0;
}

/*
inline int calcTriInRoll (int loc0, int loc1, int loc2) {
	int row0 = row[loc0];
	int row1 = row[loc1];
	int row2 = row[loc2];

	if (
	 (hand[loc0] == hand[loc1] && hand[loc0] == hand[loc2]) 
	 && ((finger[loc0] > finger[loc1] && finger[loc1] > finger[loc2]) || (finger[loc0] < finger[loc1] && finger[loc1] < finger[loc2]))
	 && ((row0 == row1 && row0 == row2) || (row0 > row1 && row1 > row2) || (row0 == row2 && abs(row0 - row1) == 1))
	) 
	 return triInRoll;
	 else return 0;
}
*/

inline int calcTriInRoll (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) {
	 if (((hand[loc0] == hand[loc1] || hand[loc1] == hand[loc2]) && hand[loc0] != hand[loc2])) 
	//  if ((hand[loc0] == hand[loc1] && hand[loc0] != hand[loc2]) || (hand[loc1] == hand[loc2] && hand[loc0] != hand[loc2]))
	 	return triInRoll / (int)(pow(2, layerDiff(layer1, layer2)));
	 else return 0;
}
 
/*
inline int calcTriOutRoll (int loc0, int loc1, int loc2) {
	int row0 = row[loc0];
	int row1 = row[loc1];
	
	if ((hand[loc0] == hand[loc1] && hand[loc0] != hand[loc2]) 
	&& (finger[loc0] < finger[loc1])
	&& (finger[loc0] == INDEX || finger[loc0] == MIDDLE)
	&& (row0 == row1 || row0 < row1)
	) 
	return triOutRoll;
	 else return 0;
}
*/

inline int calcTriOutRoll (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) {
	if (hand[loc0] == hand[loc2] && row[loc0] == row[loc2] && finger[loc0] != finger[loc2] && hand[loc0] != hand[loc1]) {
		return calcRowChange(loc0, loc2, layer0, layer2) * triOutRoll;
		// return (base / rowChangeDown) * triOutRoll; 
	}
	return 0;
}

inline int calcTriOneHand (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) { 

	// if (hand[loc0] == hand[loc1] && hand[loc0] == hand[loc2]
	// && ((finger[loc0] > finger[loc1] && finger[loc1] > finger[loc2])
	// 	||
	// 	(finger[loc0] < finger[loc1] && finger[loc1] < finger[loc2]))
	// ) return triOneHand;

	if (hand[loc0] == hand[loc1] && hand[loc1] == hand[loc2] && 
	!((row[loc0] <= row[loc1] && row[loc1] <= row[loc2]) || (row[loc0] >= row[loc1] && row[loc1] >= row[loc2]))
	)
		return (
			calcHalfScissor(loc0, loc2, layer0, layer2) + calcFullScissor(loc0, loc2, layer0, layer2)
			// + calcHalfScissor(loc0, loc1, layer0, layer1) + calcHalfScissor(loc1, loc2, layer1, layer2)
			// + calcFullScissor(loc0, loc1, layer0, layer1) + calcFullScissor(loc1, loc2, layer1, layer2)
		) / triOneHand;
	else return 0;



			// (calcHalfScissor(loc0, loc1, layer0, layer1) / halfScissor + calcHalfScissor(loc1, loc2, layer1, layer2) / halfScissor)
			// + (calcFullScissor(loc0, loc1, layer0, layer1) / fullScissor + calcFullScissor(loc1, loc2, layer1, layer2) / fullScissor)

	// if (triOneHand != 0 && hand[loc0] == hand[loc1] && hand[loc0] == hand[loc2]) {
	// 	int penalty = 1;
	// 	penalty += calcHalfScissor(loc0, loc1, layer0, layer1) / halfScissor; 
	// 	penalty += calcHalfScissor(loc1, loc2, layer1, layer2) / halfScissor; 
	// 	penalty += calcFullScissor(loc0, loc1, layer0, layer1) / fullScissor; 
	// 	penalty += calcFullScissor(loc1, loc2, layer1, layer2) / fullScissor; 
	// 	penalty += calcLateralStretch(loc0, loc1, layer0, layer1) / lateralStretch; 
	// 	penalty += calcLateralStretch(loc1, loc2, layer1, layer2) / lateralStretch; 	
	// 	return penalty * triOneHand;		
	// }
	// else return 0;

}

inline int calcHalfScissorTri(int loc0, int loc1, int loc2, int layer0, int layer1, int layer2)
{
	if (hand[loc0] == hand[loc2] && finger[loc0] != finger[loc2] && abs(row[loc0] - row[loc2]) == 1) {
		int base = calcHalfScissor(loc0, loc2, layer0, layer2);
		return (base / halfScissor) * halfScissorTri; 
	}
	return 0;
}

inline int calcFullScissorTri(int loc0, int loc1, int loc2, int layer0, int layer1, int layer2)
{
	if (hand[loc0] == hand[loc2] && finger[loc0] != finger[loc2] && abs(row[loc0] - row[loc2]) == 2) {
		int base = calcFullScissor(loc0, loc2, layer0, layer2);
		return (base / fullScissor) * fullScissorTri; 
	}
	return 0;
}

inline int calcLateralStretchTri(int loc0, int loc1, int loc2, int layer0, int layer1, int layer2)
{
	// cases where the keys are not on the same row are handled under the scissor logic
	if (hand[loc0] == hand[loc2] && abs(row[loc0] - row[loc2]) == 0 && (isCenter[loc0] || isCenter[loc2])) {
		int base = calcLateralStretch(loc0, loc2, layer0, layer2);
		return (base / lateralStretch) * lateralStretchTri; 
	}
	return 0;
}

inline int calcTriAlt (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) { 
	if (hand[loc0] != hand[loc1] && hand[loc1] != hand[loc2]) return triAlt;
	else return 0;

	// if (hand[loc0] != hand[loc2] || hand[loc0] == hand[loc1] || row[loc0] != row[loc2] || isCenter[loc0] || isCenter[loc2] || triAlt == 0) return 0;
	// int64_t consec = calcOutRoll(loc0, loc2, layer0, layer2);
	// int64_t sameRow = calcInRoll(loc0, loc2, layer0, layer2);

	// return (consec + sameRow) / triAlt; 

	// // || ((finger[loc0] == finger[loc1] || finger[loc1] == finger[loc2]) && hand[loc0] == hand[loc1])
	// // || (row[loc0] != row[loc1] && hand[loc0] == hand[loc1])
	// // || (hand[loc0] == hand[loc1] && isCenter[loc1])) return 0;

}

inline int calcTriRedirect (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) { 
	if ((hand[loc0] == hand[loc1] && hand[loc0] == hand[loc2]) 
	&& ((finger[loc0] < finger[loc1] && finger[loc1] > finger[loc2]) || (finger[loc0] > finger[loc1] && finger[loc1] < finger[loc2]))
	&& !(finger[loc1] == INDEX && !isCenter[loc1] && abs(row[loc0] - row[loc1]) < 2 && abs(row[loc1] - row[loc2]) < 2)
	) return triRedirect;
		else return 0;
}

inline int calcTriHomeJump (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2) { 
	return calcHomeJump(loc0, loc2, layer0, layer2) * triHomeJump / homeJump;
}