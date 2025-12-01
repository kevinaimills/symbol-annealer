/*
 *  keyboard.c
 *  Typing
 *  
 *  Created by Michael Dickens on 8/7/09. 
 * 
 */

#include "keyboard.h"

int legalBox[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int legalBox2[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 
	3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 
};

int legalBox3[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 
	4, 4, 3, 3, 3, 3, 3, 3, 4, 4, 
};

int legalBox4[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 
	3, 3, 4, 4, 3, 3, 4, 4, 3, 3, 
};

int legalBox5[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int bigLegalBox[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int bigLegalBox1[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int bigLegalBox2[] = {
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int bigLegalBoxAtle[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int bigLegalBoxConsonants[] = {
	1,12, 3, 4, 5, 6, 7, 8, 9,10,11, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int kinesisLegalBox[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

int kinesisLegalBox2[] = {
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

void buildShuffledIndices(Keyboard *k, int indices[], int length)
{
	int i, j, l;

	for (l = 0; l < 1; l++) {
		
		for (i = 0; i < length; ++i) {
			j = rand() % (i + 1);
			int temp = indices[i];
			indices[i] = indices[j];
			indices[j] = temp;
			// indices[j] = i; 
		}
	}
}

void forcePlausibleHomeRow(Keyboard *k)
{
	// printf(" in: %s\n", k->layout); 
	if (keepAlphas || (keepHomeRowLeft && keepHomeRowRight)) return 0;
	for (int i = 10; i < 20; i++) {
		if (i == 14 || i == 15) continue;

		int isPlausible = 0;

		for (int j = 0; j < PLAUSIBLE_HOMEROW_THRESHOLD; j++) {
			if (charAt(k, i) == monographs[j].key) {
				isPlausible = 1;
				break;
			}
		}

		while (!isPlausible) {
			int foundSwap = 0;
			int swapLoc = rand() % 30;
			if (swapLoc >= 10 && swapLoc < 20 && swapLoc != 14 && swapLoc != 15) continue; // don't swap with another homerow char
			for (int l = 0; l < PLAUSIBLE_HOMEROW_THRESHOLD; l++) {
				if (charAt(k, swapLoc) == monographs[l].key) {
					foundSwap = 1;
					break;
				}
			}
			if (foundSwap) {
				if (isLegalSwap(k, i, swapLoc)) {
					swap(k, i, swapLoc);
					isPlausible = 1;
				}
			}
		}
	}
	// printf("out: %s\n", k->layout); 
}

int initKeyboard(Keyboard *k)
{
	copyKeyboard(k, &nilKeyboard);
	setLayout(k, keysToInclude);
	shuffleLayout(k);
	if (rand() % 2 > 0) forcePlausibleHomeRow(k);
	return 0;
}

/* 
 * Copies a layout from file onto k.
 * 
 * Return Codes
 * -1: Error.
 * -2: No new layout was found in the file.
 * 0: Success.
 */
int layoutFromFile(FILE *file, Keyboard *k)
{
	int i;
	int prevC = 0, c = 0;
	
	copyKeyboard(k, &nilKeyboard);
	
	int readUntilN = FALSE, noNewKeyboard = TRUE, escaped = FALSE;
	for (i = 0; (c = getc(file)) != EOF && i < 2 * ksize; ++i, prevC = c) {
		if (readUntilN) {
			i = -1;
			if (c == '\n') readUntilN = FALSE;
		} else if (c == '/' && prevC == '/') { // "//" comments out the rest of the line.
			noNewKeyboard = TRUE;
			copyKeyboard(k, &nilKeyboard);
			readUntilN = TRUE;
			i = -1;
		} else if (!escaped && c == '\\') {
			escaped = TRUE;
			--i;
		} else if (c == '\n') { 
			if (i > 0) {
				fprintf(stderr, "Error: In layoutFromFile(), keyboard layout is not %d characters.\n", trueksize);
				copyKeyboard(k, &nilKeyboard);
				return -1;
			} else i = -1;
		} else if (strchr(keysToInclude, c) == NULL) {
			fprintf(stderr, "Error: In layoutFromFile(), character '%c' (#%d) may not be used in a keyboard.\n", c, c);
			fprintf(stderr, "i = %d\n", i);
			copyKeyboard(k, &nilKeyboard);
			return -1;
		} else {
			while (i < 2 * ksize && !printable[i % ksize])
				++i;
			
			if (escaped) {
				escaped = FALSE;
				char saved = c;
				c = convertEscapeChar(c);
				if (c == 0) {
					fprintf(stderr, "Error: Unknown escape character \\%c (#%d).\n", saved, saved);
					return -1;
				} else if (strchr(keysToInclude, c) == NULL) {
					fprintf(stderr, "Error: In layoutFromFile(), escape character '%c' (#%d) may not be used in a keyboard.\n", c, c);
					fprintf(stderr, "i = %d\n", i);
					copyKeyboard(k, &nilKeyboard);
					return -1;
				}
			}
						
			if (i < ksize) k->layout[i] = (char) c;
			else if (i < 2 * ksize) k->shiftedLayout[i - ksize] = (char) c;
			else if (i < 3 * ksize) k->symbolLayer[i - ksize * 2] = (char) c;

			while (i+1 < 3 * ksize && !printable[(i+1) % ksize])
				++i;
			noNewKeyboard = FALSE;
		}
	}
	
	k->layout[ksize] = '\0';
	k->shiftedLayout[ksize] = '\0';
	k->symbolLayer[ksize] = '\0';
	while (c != EOF && c != '\n') c = fgetc(file);
		
	if (noNewKeyboard)
		return -2;
	calcFitness(k, 0);
	
	return 0;
}

inline void copyKeyboard(Keyboard *k, Keyboard *original)
{
	memcpy(k, original, sizeof(Keyboard));
}

/* 
 * If loc1 or loc2 falls on [0, ksize), it swaps an unshifted char. 
 * If it falls on [ksize, 2 * ksize), it swaps a shifted char. 
 * If loc1 or loc2 is a char that has a paired shifted char, this will 
 * automatically call swapPair(). 
 * 
 * WARNING: Can perform illegal swaps.
 *  
 * Return Codes
 * 0: Success.
 * -1: loc1 or loc2 is out of bounds.
 * -2: loc1 or loc2 is at an unprintable position.
 */

int setLayout(Keyboard *k, char *layout)
{
	int i;
	int nextCandidate = 0;

	char *savedLayout = layout;
	for (i = 0; i < ksize; ++i) {
		if (printable[i] && *layout == '\0') {
			fprintf(stderr, "Error: in setLayout(), layout %s does not have enough characters (%d expected, %ld found).\n", 
					savedLayout, trueksize, strlen(savedLayout));
			return -1;
		}
		if (printable[i]) k->layout[i] = *(layout++);		
		else k->layout[i] = 1; /* 1 is used as a placeholder*/ 

		if (isSwapCandidate(k->layout[i])) {
			k->swapCandidates[nextCandidate] = i;
			nextCandidate++;
		}
	}
	
	savedLayout = layout;
	for (i = 0; i < ksize; ++i) {
		if (printable[i] && *layout == '\0') {
			fprintf(stderr, "Error: in setLayout(), layout %s does not have enough characters (%d expected, %ld found).\n", 
					savedLayout, trueksize, strlen(savedLayout));
			return -1;
		}
		if (printable[i]) k->shiftedLayout[i] = *(layout++);
		else k->shiftedLayout[i] = 1;

		if (isSwapCandidate(k->shiftedLayout[i])) {
			k->swapCandidates[nextCandidate] = i + ksize;
			nextCandidate++;
		}
	}

	savedLayout = layout;
	for (i = 0; i < ksize; ++i) {
		if (printable[i] && *layout == '\0') {
			fprintf(stderr, "Error: in setLayout(), layout %s does not have enough characters (%d expected, %ld found).\n", 
					savedLayout, trueksize, strlen(savedLayout));
			return -1;
		}
		if (printable[i]) k->symbolLayer[i] = *(layout++);
		else k->symbolLayer[i] = 1;

		if (isSwapCandidate(k->symbolLayer[i])) {
			k->swapCandidates[nextCandidate] = i + ksize * 2;
			nextCandidate++;
		}
	}

	// printf("\n");
	// printf("\n");
	// for (int i = 0; i < KSIZE_MAX; i++) printf("%c", charAt(k, k->swapCandidates[i]));
	// printf("\n");
	// printf("\n");

	k->layout[i] = '\0';
	k->shiftedLayout[i] = '\0';
	k->symbolLayer[i] = '\0';
	k->numCans = nextCandidate;
	return 0;
}

int isSwapCandidate(char c) {
	// for (int i = 0; i < 30; i++) {
		if (strchr(doNotMove, c)) return 0;
	// }
	
	// if (c == 'x')  isCandidate = 0;
	if (isupper(c)) return 0;
	
	if (keepHomeRowLeft) {
		if (c == keysToInclude[10]) return 0;
		if (c == keysToInclude[11]) return 0;
		if (c == keysToInclude[12]) return 0;
		if (c == keysToInclude[13]) return 0;
	}

	if (keepHomeRowRight) {
		if (c == keysToInclude[16]) return 0;
		if (c == keysToInclude[17]) return 0;
		if (c == keysToInclude[18]) return 0;
		if (c == keysToInclude[19]) return 0;
	}

	// if (isalpha(c) && keepAlphas) return 0;
	if (isalpha(c) && keepAlphas && !flexibleSymbolLocations) return 0;
	if (isalpha(c) && keepAlphas && flexibleSymbolLocations &&
		c != 'z'
		&& c != 'q'
		&& c != 'j'
		&& c != 'x'
		&& c != 'k'
		&& c != 'v'
		&& c != 'q'
		&& c != 'y' 
	) return 0;
 
	return 1;
}

inline int swap(Keyboard *k, int loc1, int loc2)
{
	// if (loc1 < 0 || loc2 < 0 || loc1 >= 3 * ksize || loc2 >= 3 * ksize)
    //     return -1;
	// if (printable[loc1 % ksize] ^ printable[loc2 % ksize])
    //     return -2;
	
 	if (keepShiftPair(k->layout[loc1]) ||
 			 keepShiftPair(k->layout[loc2])) {
			 return swapPair(k, loc1, loc2);
 	}
	
	char *layout1;
	char *layout2;
	
	if (loc1 < ksize) {
        layout1 = k->layout;
	} else if (loc1 < 2 * ksize) {
		layout1 = k->shiftedLayout;
		loc1 -= ksize;
	} else {
		layout1 = k->symbolLayer;
		loc1 -= 2 * ksize;
	}
	
	if (loc2 < ksize) {
        layout2 = k->layout;
    } else if (loc2 < 2 * ksize) {
		layout2 = k->shiftedLayout;
		loc2 -= ksize;
	} else {
		layout2 = k->symbolLayer;
		loc2 -= 2 * ksize;
	}
	
	char temp = layout1[loc1];
	layout1[loc1] = layout2[loc2];
	layout2[loc2] = temp;
			
	return 0;
}

/* 
 * Simultaneously swaps two keys' shifted and unshifted values.
 */
inline int swapPair(Keyboard *k, int loc1, int loc2)
{
 	//todo: symbol layer
	if (strchr(doNotMove, charAt(k, loc1)) || strchr(doNotMove, charAt(k, loc2))) return 0;
	if (loc1 < 0 || loc2 < 0 || loc1 >= ksize || loc2 >= ksize) return -1;
	if (printable[loc1] ^ printable[loc2]) return -2;
	
	char temp = k->layout[loc1];
	k->layout[loc1] = k->layout[loc2];
	k->layout[loc2] = temp;
	
	temp = k->shiftedLayout[loc1];
	k->shiftedLayout[loc1] = k->shiftedLayout[loc2];
	k->shiftedLayout[loc2] = temp;

	// temp = k->symbolLayer[loc1];
	// k->symbolLayer[loc1] = k->symbolLayer[loc2];
	// k->symbolLayer[loc2] = temp;

	return 0;
}

int isSwappable(char c)
{
	return !(keepNumbers && isdigit(c));
}

int isLegalSwap(Keyboard *k, int i, int j)
{
// 	if (charAt(k, i) == '@' && charAt(k, j) == '=') return 1;
// 	if (charAt(k, i) == '=' && charAt(k, j) == ',') return 1;

// return 0;
	if (!isSwapCandidate(charAt(k, i)) || !isSwapCandidate(charAt(k, j))) return FALSE;
	// if ((i < 30 || j < 30) && (keepShiftPair((charAt(k, i))) || keepShiftPair((charAt(k, j)))) && 
	// 	((!isalpha(charAt(k, i)) && !isSwapCandidate(charAt(k, i+30))) || (!isalpha(charAt(k, j)) && !isSwapCandidate(charAt(k, j+30))))) return 0;

	// if (i < 30  && j >= 30 && isalpha(charAt(k, i))) return 0;
	// if (j < 30  && i >= 30 && isalpha(charAt(j, i))) return 0;
	

	// if (i / ksize == 1 && isalpha(charAt(k, i))) return FALSE;
	// if (j / ksize == 1 && isalpha(charAt(k, j))) return FALSE; 
	// if (i / ksize == 1 && j / ksize == 1 && (isalpha(charAt(k, i)) || isalpha(charAt(k, j)))) return FALSE;
	// if ((isalpha(charAt(k, i)) && j >= 30) || (isalpha(charAt(k, j)) && i >= 30)) return FALSE;

	if (i < 0 || j < 0 || i >= 3 * ksize || j >= 3 * ksize)
		return FALSE;
	
	// if (!printable[i % ksize] || !printable[j % ksize])
	// 	return FALSE;
	
	// if (!doSymbolLayer && 
	// 	((i >= ksize && (keepShiftPairs || keepShiftPair(k->shiftedLayout[i % ksize]))) || 
	// 		(j >= ksize && (keepShiftPairs || keepShiftPair(k->shiftedLayout[j % ksize]))))) {
	// 	return FALSE;
	// }
	
//	if (isalpha(charAt(k, i)) || (isalpha(charAt(k, j)))) return FALSE;
	
	// if (keepNumbers == 1 && (isdigit(charAt(k, i)) || isdigit(charAt(k, j)))) {
	// 	return FALSE;
	// } else if (keepNumbers == 2 && (isdigit(charAt(k, i)) ^ isdigit(charAt(k, j)))) {
	// 	return FALSE;
	// }
	
	// if (keepTab && (charAt(k, i) == '\t' || charAt(k, j) == '\t'))
	// 	return FALSE;
		
	// i %= ksize;
	// j %= ksize;
	
	// if (fullKeyboard == K_NO) {
	// 	return legalBox[i] == legalBox[j];
	// } else if (fullKeyboard == K_STANDARD) {
	// 	if (keepConsonantsLeft) return bigLegalBoxConsonants[i] == bigLegalBoxConsonants[j];
	// 	else return bigLegalBox[i] == bigLegalBox[j];
	// } else if (fullKeyboard == K_KINESIS) {
	// 	return kinesisLegalBox[i] == kinesisLegalBox[j];
	// }

	return TRUE;
}

int qwertyPositions(Keyboard *k)
{
	NOT_WORK_WITH_FULL_KEYBOARD("qwertyPositions()");
	
	int count = 0;
	
	int i;
	for (i = 0; i < ksize; ++i)
		if (k->layout[i] == qwerty[i])
			count++;
	
	return count;
}

int printLayoutOnly(Keyboard *k)
{
	if (!keepAlphas && !keepHomeRowLeft && !keepHomeRowRight && keepConsonantsLeft && hand[locWithShifted(k, 'e')] == LEFT) {
		reverseLayout(k->shiftedLayout);
		reverseLayout(k->layout);
		if (doSymbolLayer) reverseLayout(k->symbolLayer);
	}
	
	printLayoutRaw(k->shiftedLayout);
	printLayoutRaw(k->layout);
	if (doSymbolLayer) printLayoutRaw(k->symbolLayer);
	return 0;
}

int printLayoutRaw(char layout[])
{
	int i;
	
	char str[10];
	// printf("\n%s\n", layout);
	
	for (i = 0; i < ksize; ++i) {
		charToPrintable(str, layout[i], TRUE);
		
		if (fullKeyboard == K_KINESIS) {
			if (printable[i]) {
				if (i % 12 == 11) printf("%s\n", str);
				else if (i % 12 == 5) printf("%s  ", str);
				else printf("%s ", str);
			} else {
				if (i % 12 == 11) printf(" \n");
				else if (i % 12 == 5) printf("    ");
				else printf("   ");
			}
		} else if (fullKeyboard == K_STANDARD) {
			if (printable[i] == FALSE) {
				if (i % 14 == 13) printf("   \n");
				else printf("   ");
			} else if (i % 14 == 13) printf("%s\n", str);
			else if (i % 14 == 5) printf("%s  ", str);
			else printf("%s ", str);
		} else {
			if (printable[i] == FALSE) {
				if (i % 10 == 9) printf("  \n");
				else printf("   ");
			} else if (i % 10 == 9) printf("%s\n", str);
			else if (i % 10 == 4) printf("%s  ", str);
			else printf("%s ", str);
		}
	}
	printf("\n");
	return 0;
}

int printPercentages(Keyboard *k)
{
	int i;
 	// printf("fitness: %li\n", k->fitness);
	
	/* Calculate fitness so that the keyboard's values will print properly. */
	Keyboard unscaled;
	Keyboard *uk = &unscaled;
	calcFitness(k, 1);
	copyKeyboard(uk, k);
	calcFitnessDirect(uk);

	if (k->layout[0] == '\0') {
		printf("keyboard is null.\n");
		return 0;
	}

	// printf("fitness: %li\n", k->fitness);

	int64_t total = 0;
	for (i = 0; i < FINGER_COUNT; ++i) total += k->fingerUsage[i];

	// Hand
	printf("\nHands:   ");
	printf("%.2f%% ", (float) 100 * (k->fingerUsage[0] + k->fingerUsage[1] + 
			k->fingerUsage[2] + k->fingerUsage[3] + k->fingerUsage[4]) / total);
	printf("%.2f%%\n", (float) 100 * (k->fingerUsage[5] + 
			k->fingerUsage[6] + k->fingerUsage[7] + k->fingerUsage[8]
			 + k->fingerUsage[9]) / total);

	// Finger
	printf("Fingers: ");
	for (i = 0; i < FINGER_COUNT; ++i) {
		double usage = (100.0 * k->fingerUsage[i] / total);
		if (usage < 1) printf(" "); //printf("%.1f%% ", usage);
		else if (usage < 10) printf("%.1f%% ", usage);
		else printf("%.1f%% ", usage);
	}
	printf("\n");
	if (useRingForTopPinky) printf("*** Using the ring finger for top row pinky; can be disabled in values.c\n");

	// Finger
	printf("Travel:  ");
	for (i = 0; i < FINGER_COUNT; ++i) {
		double usage = (100.0 * k->fingerUsage[i] / total);
		double travel = (100.0 * k->fingerTravel[i] / total);
		if (usage <= 0) printf(" "); //printf("%.1f%% ", usage); 
		else if (usage >= 10 && travel < 10) printf("%.1f%%  ", travel);
		else printf("%.1f%% ", travel);
	}
	printf("\n\n");
	// Print the keyboard layout. 
	printLayoutOnly(k); 
	
	double sfbAboveMax = (double)(100*uk->sameFinger) / totalDi - sameFingerMax;  
	if (sfbAboveMax < 0) sfbAboveMax = 0;

	// Print all the fitness criteria.
	// printf("Fitness:                %lld\n",   k->fitness - k->aesthetics);
	printf("Fitness (-aesthetics):  %lld (%lld)\n",   k->fitness, k->fitness - k->aesthetics);
	if (keepQWERTY) printf("QWERTY positions: %d\n", qwertyPositions(k));
	printf("Finger travel:          %lld\n",   (        (    k->distance  )           ));
	printf("Excess finger press:    %lld\n",   (        (    k->fingerWork)           ));
	printf("Excess finger travel:   %lld\n",   (        (    k->fingerTravelWork)           ));
	printf("Hand travel:            %lld\n",   (        (    k->handTravel  )           ));
 	if (handSmooth < 50)
		printf("Hand imbalance:         %lld\n",   (        (    k->handImbalance)           ));
	else
		printf("Hand imbalance (DISABLED):   %lld\n",   (        (    k->handImbalance)           ));
	printf("Aesthetics:             %lld\n",   (        (    k->aesthetics)           ));
	printf("Layer change:           %lld\n",   (        (    k->layerChange)           ));
	printf("(Bigram) layer, diff:       %.2f%% (%i)\n", ((double)(100*uk->biLayerChange  ) / totalDi ), k->biLayerChange);
	printf("(Bigram) layer, diff hands: %.2f%% (%i)\n", ((double)(100*uk->biLayerSplit  ) / totalDi ), k->biLayerSplit);
	printf("(Bigram) rolls, separated   %.2f%% (%i)\n", ((double)(100*uk->inRoll    ) / totalDi ), k->inRoll);
	printf("(Bigram) rolls, consec:     %.2f%% (%i)\n", ((double)(100*uk->outRoll   ) / totalDi ), k->outRoll);
	printf("(Bigram) same hand:         %.2f%% (%i)\n", ((double)(100*uk->sameHand  ) / totalDi ), k->sameHand);
	printf("(Bigram) same finger:       %.2f%% (%i)\n", ((double)(100*uk->sameFinger) / totalDi ), k->sameFinger);
	printf("(Bigram) sfb above max:     %.2f%% (%i)\n", sfbAboveMax, k->sameFingerMax);
	printf("(Bigram) same row:          %.2f%% (%i)\n", ((double)(100*uk->rowChange ) / totalDi ), k->rowChange);
	// printf("(Bigram) hand reposition:   %.2f%% (%i)\n", ((double)(100*uk->homeJump  ) / totalDi ), k->homeJump);
	printf("(Bigram) double tap:        %.2f%% (%i)\n", ((double)(100*uk->ringJump  ) / totalDi ), k->ringJump);
	printf("(Bigram) scissors, half:    %.2f%% (%i)\n", ((double)(100*uk->halfScissor  ) / totalDi ), k->halfScissor);
	printf("(Bigram) scissors, full:    %.2f%% (%i)\n", ((double)(100*uk->fullScissor  ) / totalDi ), k->fullScissor);	                              
	printf("(Bigram) lat stretch:       %.2f%% (%i)\n", ((double)(100*uk->lateralStretch  ) / totalDi ), k->lateralStretch);

	// printf("(Bigram) center column:  %.2f%% \(%i\)\n", ((double)(100*uk->toCenter  ) / totalDi ), k->toCenter);

	// printf("Layer change (tri):    %lld\n",   (        (    k->triLayerChange)           ));
	printf("(Trigram) same finger, split:   %.2f%% (%i)\n", ((double)(100*uk->triSplitFinger  ) / totalTri ), k->triSplitFinger);
	printf("(Trigram) same row, split:      %.2f%% (%i)\n", ((double)(100*uk->triOutRoll  ) / totalTri ), k->triOutRoll);
	printf("(Trigram) rolls:                %.2f%% (%i)\n", ((double)(100*uk->triInRoll  ) / totalTri ), k->triInRoll);
	printf("(Trigram) alternates:           %.2f%% (%i)\n", ((double)(100*uk->triAlt  ) / totalTri ), k->triAlt);
	printf("(Trigram) bad redirects:        %.2f%% (%i)\n", ((double)(100*uk->triRedirect  ) / totalTri ), k->triRedirect);
	// printf("(Trigram) hand reposition:      %.2f%% (%i)\n", ((double)(100*uk->triHomeJump  ) / totalTri ), k->triHomeJump);
	printf("(Trigram) scissors, one hand:   %.2f%% (%i)\n", ((double)(100*uk->triOneHand  ) / totalTri ), k->triOneHand);
	printf("(Trigram) scissors, half split: %.2f%% (%i)\n", ((double)(100*uk->halfScissorTri  ) / totalTri ), k->halfScissorTri);
	printf("(Trigram) scissors, full split: %.2f%% (%i)\n", ((double)(100*uk->fullScissorTri  ) / totalTri ), k->fullScissorTri);
	printf("(Trigram) lat stretch, split:   %.2f%% (%i)\n", ((double)(100*uk->lateralStretchTri  ) / totalTri ), k->lateralStretchTri);
	printf("\n");

	return 0;
}

/* Assumes buffer is at least 3 characters. 
 * 
 * Converts ' ' to "SP" if changeSpace is true.
 */
int charToPrintable(char *buffer, char c, int changeSpace)
{
	if (c == '\n') sprintf(buffer, "\\n");
	else if (c == '\t') sprintf(buffer, "\\t");
	else if (c == ASCII_SHIFT) sprintf(buffer, "\\s");
	else if (c == '\b') sprintf(buffer, "\\b");
	else if (changeSpace && c == ' ') sprintf(buffer, "SP");
	else sprintf(buffer, "%2c", c);

	return 0;
}

inline void shuffleLayout(Keyboard *k)
{
	int x, n = 3 * ksize;
	int i, legalSwapExists;
	while (n > 1) 
	{
		--n;
		while (!printable[n]) --n;
				
		legalSwapExists = FALSE;
		for (i = 0; i < n; ++i)
			if (isLegalSwap(k, i, n)) {
				legalSwapExists = TRUE;
				break;
			}
		
		if (legalSwapExists) {
			do {
				x = rand() % (n + 1);
			} while (!isLegalSwap(k, x, n));

			swap(k, x, n);
		}		
	}
}

inline int locIgnoreShifted(Keyboard *k, char c)
{
	char *ptr = strchr(k->layout, c);
    if (ptr) return (int) (ptr - k->layout);
    
    ptr = strchr(k->shiftedLayout, c);
    if (ptr) return (int) (ptr - k->shiftedLayout);

    ptr = strchr(k->symbolLayer, c);
    if (ptr) return (int) (ptr - k->symbolLayer);

	return -1;
}

/* Guaranteed to check unshifted first, so if a character is the same on both 
 * shifted and unshifted layouts, it will return unshifted first.
 */
inline int locWithShifted(Keyboard *k, char c)
{
	char *ptr = strchr(k->layout, c);
    if (ptr) return (int) (ptr - k->layout);
    
    ptr = strchr(k->shiftedLayout, c);
    if (ptr) return (int) (ptr - k->shiftedLayout) + ksize;
	
	ptr = strchr(k->symbolLayer, c);
    if (ptr) return (int) (ptr - k->symbolLayer) + ksize * 2;
 
	return -1;	
}

