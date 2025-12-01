	if (hand[loc0] != hand[loc1] || abs(row[loc0] - row[loc1]) != 1) return 0;

	int lf; // lower finger
	int uf;
 	int ufr; // upper finger row
	int center = (isCenter[loc0] || isCenter[loc1]);
	int base = 0;
 
	if (row[loc0] > row[loc1]) { // greater number means lower row
		lf = finger[loc0];
		uf = finger[loc1];
		ufr = row[loc1];
	} else {
		lf = finger[loc1];
		uf = finger[loc0];
		ufr = row[loc0];
	}

	if (ufr == 0) { // upper finger is on top row
		switch (uf) {
			case PINKY:
				if (lf == RING) base = 2;
				else if (lf == MIDDLE) base = 2;
				else if (lf == INDEX && !center) base = 1;
				else if (lf == INDEX && center) base = 0;
				break;
			case RING:
				if (lf == PINKY) base = 1;
				else if (lf == MIDDLE) base = 1;
				else if (lf == INDEX && !center) base = 0;
				else if (lf == INDEX && center) base = 1;
				break;
			case MIDDLE:
				if (lf == PINKY) base = 0;
				else if (lf == RING) base = 1;
				else if (lf == INDEX && !center) base = 0;
				else if (lf == INDEX && center) base = 2;
				break;
			case INDEX:
				if (!center) {
					if (lf == PINKY) base = 1;
					else if (lf == RING) base = 1;
					else if (lf == MIDDLE) base = 1;
				} else if (center) {
					if (lf == PINKY) base = 1;
					else if (lf == RING) base = 2;
					else if (lf == MIDDLE) base = 2;
				}
				break;
		}
	}

	if (ufr == 1) { // upper finger is on home row
		switch (uf) {
			case PINKY:
				if (lf == RING) base = 1;
				else if (lf == MIDDLE) base = 0;
				else if (lf == INDEX && !center) base = 0;
				else if (lf == INDEX && center) base = 1;
				break;
			case RING:
				if (lf == PINKY) base = 1;
				else if (lf == MIDDLE) base = 1;
				else if (lf == INDEX && !center) base = 0;
				else if (lf == INDEX && center) base = 1;
				break;
			case MIDDLE:
				if (lf == PINKY) base = 0;
				else if (lf == RING) base = 1; 
				else if (lf == INDEX && !center) base = 0;
				else if (lf == INDEX && center) base = 2;
				break;
			case INDEX:
				if (!center) {
					if (lf == PINKY) base = 0;
					else if (lf == RING) base = 0;
					else if (lf == MIDDLE) base = 1;
				} else if (center) {
					if (lf == PINKY) base = 2;
					else if (lf == RING) base = 2;
					else if (lf == MIDDLE) base = 2;
				}
				break;
		}
	}	

	return halfScissor * base;