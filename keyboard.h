/*
 *  keyboard.h
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 * Includes the keyboard struct and the fitness function.
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "tools.h"

/* Takes a Keyboard pointer k and an integer index. 
 * 
 * WARNING: Both k and index are evaluated multiple times.
 */
#define charAt(k, index) ((index) < ksize ? (k)->layout[index] : (index) < ksize * 2 ? (k)->shiftedLayout[index - ksize] : (k)->symbolLayer[index - ksize * 2])
#define setCharAt(k, index, c) ((index) < ksize ? ((k)->layout[index] = (c)) : (index) < ksize * 2 ? ((k)->shiftedLayout[index - ksize] = (c)) : ((k)->symbolLayer[index - ksize * 2] = (c)))

void buildShuffledIndices(Keyboard *k, int indices[], int length);

int initKeyboard(Keyboard *k);
int setLayout(Keyboard *k, char *layout);
int layoutFromFile(FILE *file, Keyboard *k);
int swap(Keyboard *k, int loc1, int loc2);
int swapPair(Keyboard *k, int loc1, int loc2);
int printLayoutOnly(Keyboard *k);
int printLayoutRaw(char layout[]);
int printPercentages(Keyboard *k);
int charToPrintable(char *buffer, char c, int changeSpace);
int isSwapCandidate(char c);
void forcePlausibleHomeRow(Keyboard *k);

void sameMirrorRule(Keyboard *k, char char1, char char2, char char3, char char4, double cost);
void togetherOrMirrored(Keyboard *k, char firstChar, char secondChar, double cost);
void additionalSFBPenalty(Keyboard *k, char firstChar, char secondChar, double cost);
void useShiftPair(Keyboard *k, char firstChar, char secondChar, double cost);
void keepSameHand(Keyboard *k, char chars[], int size, double cost);
void keepSameRow(Keyboard *k, char chars[], int size, double cost);
void cluster(Keyboard *k, char chars[], int size, double cost);
void clusterPairs(Keyboard *k, char chars[], int size, double cost);
void alignPairs(Keyboard *k, char chars[], int size, double cost);
void sameRelation(Keyboard *k, char chars[], int size, double cost);
void keepAdjacent(Keyboard *k, char char1, char char2, double cost);
void allMirrors(Keyboard *k, char chars[], int size, double cost);
void notTerribleLocation(Keyboard *k, char char1, double cost);
int areMirrors(Keyboard *k, char char1, char char2);
int calcSeparation(Keyboard *k, char char1, char char2);
float calcClustering(Keyboard *k, char char1, char char2);
float calcClusteringPairs(Keyboard *k, char char1, char char2, char char3, char char4);
void applyAdHocPenalties(Keyboard *k, double cost);
void saveAestheticPenalty(Keyboard *k, double penalty);

int qwertyPositions(Keyboard *k);
int readLayouts(Keyboard pool[], int length);

int isSwappable(char c);
int isLegalSwap(Keyboard *k, int i, int j);
void shuffleLayout(Keyboard *kbd);

/* Returns the index of c on either the shifted or unshifted layout. */
int locIgnoreShifted(Keyboard *k, char c);

/* Returns the index of c if c is on the unshifted layout, or index + ksize
 * if c is on the shifted layout. 
 */
int locWithShifted(Keyboard *k, char c);

/* To use, set USE_COST_ARRAY to TRUE. */
int allDigraphCosts[KSIZE_MAX][KSIZE_MAX];
int allDigraphsLayerChange[KSIZE_MAX][KSIZE_MAX];
int allDigraphsHomeJump[KSIZE_MAX][KSIZE_MAX];
int allDigraphsSameHand[KSIZE_MAX][KSIZE_MAX];
int allDigraphsSameFinger[KSIZE_MAX][KSIZE_MAX];
int allDigraphsInRoll[KSIZE_MAX][KSIZE_MAX];
int allDigraphsOutRoll[KSIZE_MAX][KSIZE_MAX];
int allDigraphsRowChange[KSIZE_MAX][KSIZE_MAX];
int allDigraphsRingJump[KSIZE_MAX][KSIZE_MAX];
int allDigraphsToCenter[KSIZE_MAX][KSIZE_MAX];
int allDigraphsLayerSplit[KSIZE_MAX][KSIZE_MAX];
int allDigraphsHalfScissor[KSIZE_MAX][KSIZE_MAX];
int allDigraphsFullScissor[KSIZE_MAX][KSIZE_MAX];
int allDigraphsLateralStretch[KSIZE_MAX][KSIZE_MAX];

int allTrigraphCosts[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsLayerChange[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsInRoll[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsOutRoll[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsSplitFinger[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsOneHand[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsAlt[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsHomeJump[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsRedirect[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsHalfScissor[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsFullScissor[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];
int allTrigraphsLateralStretch[KSIZE_MAX][KSIZE_MAX][KSIZE_MAX];

int calcFitnessDirect(Keyboard *k);
int scoreDigraphDirect(Keyboard *k, char digraph[], int64_t multiplier);
int scoreTrigraphDirect(Keyboard *k, char trigraph[], int64_t multiplier);
int calcFitness(Keyboard *k, int generateDetailedOutput);
int scoreMonograph(Keyboard *k, char monograph, int64_t multiplier, int allLocs[], int generateDetailedOutput);
int scoreDigraph(Keyboard *k, char digraph[], int64_t multiplier, int allLocs[], int generateDetailedOutput);
int scoreTrigraph(Keyboard *k, char trigraph[], int64_t multiplier, int allLocs[], int generateDetailedOutput);


char shortcutKeys[4];
char seedLayout[KSIZE_MAX]; // Holds every letter and is randomly shuffled. Used to seed the keyboards. 
unsigned int seedVal;

int64_t calcShortcuts(Keyboard *k);
int64_t calcQWERTY(Keyboard *k);
int64_t calcBrackets(Keyboard *k);
void calcAesthetics(Keyboard *k);
int64_t calcBracketsGeneric(Keyboard *k, char openChar, char closeChar);
int64_t calcNumbersShifted(Keyboard *k);

int calcFingerWork(Keyboard *k);
int calcInRoll(int loc0, int loc1, int layer0, int layer1);
int calcOutRoll(int loc0, int loc1, int layer0, int layer1);
int calcSameFinger(int loc0, int loc1, int layer0, int layer1);
int calcRowChange(int loc0, int loc1, int layer0, int layer1);
int calcHomeJump(int loc0, int loc1, int layer0, int layer1);
int calcRingJump(int loc0, int loc1, int layer0, int layer1);
int calcToCenter(int loc0, int loc1, int layer0, int layer1);
int calcBiLayerHands(int loc0, int loc1, int layer0, int layer1);
int calcBiLayerChange(int loc0, int loc1, int layer0, int layer1);
int calcHalfScissor(int loc0, int loc1, int layer0, int layer1);
int calcFullScissor(int loc0, int loc1, int layer0, int layer1);
int calcLateralStretch(int loc0, int loc1, int layer0, int layer1);

int calcTriSplitFinger (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriInRoll (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriOutRoll (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriOneHand (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriAlt (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriHomeJump (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcTriRedirect (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcHalfScissorTri (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcFullScissorTri (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);
int calcLateralStretchTri (int loc0, int loc1, int loc2, int layer0, int layer1, int layer2);

#endif
