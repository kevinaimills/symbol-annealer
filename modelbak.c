	switch (lf) {
			case PINKY:
				switch (uf) {					
					case RING:
						if (lfr == 2 && ufr == 1) base = handWarp * 4;
						if (lfr == 1 && ufr == 0) base = handWarp * 3;
						if (lfr == 2 && ufr == 0) base = handWarp * 6;

					case MIDDLE:
						if (lfr == 2 && ufr == 1) base = handWarp * 4;
						if (lfr == 1 && ufr == 0) base = handWarp * 2;
						if (lfr == 2 && ufr == 0) base = handWarp * 5;

					case INDEX:
						if (!cntr) {
							if (lfr == 2 && ufr == 1) base = handWarp * 4;
							if (lfr == 1 && ufr == 0) base = handWarp * 2;
							if (lfr == 2 && ufr == 0) base = handWarp * 4;
						} else {
							if (lfr == 2 && ufr == 1) base = handWarp * 6;
							if (lfr == 1 && ufr == 0) base = handWarp * 3;
							if (lfr == 2 && ufr == 0) base = handWarp * 6;
						}
				}

			case RING:
				switch (uf) {					
					case PINKY:
						if (lfr == 2 && ufr == 1) base = handWarp * 4;
						if (lfr == 1 && ufr == 0) base = handWarp * 2;
						if (lfr == 2 && ufr == 0) base = handWarp * 8;

					case MIDDLE:
						if (lfr == 2 && ufr == 1) base = handWarp * 3;
						if (lfr == 1 && ufr == 0) base = handWarp * 2;
						if (lfr == 2 && ufr == 0) base = handWarp * 6;

					case INDEX:
						if (!cntr) {
							if (lfr == 2 && ufr == 1) base = handWarp * 3;
							if (lfr == 1 && ufr == 0) base = handWarp * 2;
							if (lfr == 2 && ufr == 0) base = handWarp * 5;
						} else {
							if (lfr == 2 && ufr == 1) base = handWarp * 6;
							if (lfr == 1 && ufr == 0) base = handWarp * 3;
							if (lfr == 2 && ufr == 0) base = handWarp * 8;
						}
				}

			case MIDDLE:
				switch (uf) {					
					case PINKY:
						if (lfr == 2 && ufr == 1) base = handWarp * 2;
						if (lfr == 1 && ufr == 0) base = handWarp * 2;
						if (lfr == 2 && ufr == 0) base = handWarp * 7;

					case RING:
						if (lfr == 2 && ufr == 1) base = handWarp * 2;
						if (lfr == 1 && ufr == 0) base = handWarp * 3;
						if (lfr == 2 && ufr == 0) base = handWarp * 6;

					case INDEX:
						if (!cntr) {
							if (lfr == 2 && ufr == 1) base = handWarp * 2;
							if (lfr == 1 && ufr == 0) base = handWarp * 2;
							if (lfr == 2 && ufr == 0) base = handWarp * 5;
						} else {
							if (lfr == 2 && ufr == 1) base = handWarp * 6;
							if (lfr == 1 && ufr == 0) base = handWarp * 3;
							if (lfr == 2 && ufr == 0) base = handWarp * 6;
						}
				}

			case INDEX:
				if (!cntr) {
					switch (uf) {				
						case PINKY:
							if (lfr == 2 && ufr == 1) base = handWarp * 2;
							if (lfr == 1 && ufr == 0) base = handWarp * 2;
							if (lfr == 2 && ufr == 0) base = handWarp * 4;
						case RING:
							if (lfr == 2 && ufr == 1) base = handWarp * 2;
							if (lfr == 1 && ufr == 0) base = handWarp * 3;
							if (lfr == 2 && ufr == 0) base = handWarp * 5;
						case MIDDLE:
							if (lfr == 2 && ufr == 1) base = handWarp * 2;
							if (lfr == 1 && ufr == 0) base = handWarp * 2;
							if (lfr == 2 && ufr == 0) base = handWarp * 3;
					}
				} else {
					switch (uf) {				
						case PINKY:
							if (lfr == 2 && ufr == 1) base = handWarp * 4;
							if (lfr == 1 && ufr == 0) base = handWarp * 4;
							if (lfr == 2 && ufr == 0) base = handWarp * 8;
							if (lfr == 2 && ufr == 2) base = handWarp * 6;
							if (lfr == 1 && ufr == 1) base = handWarp * 4;
							if (lfr == 0 && ufr == 0) base = handWarp * 4;
						case RING:
							if (lfr == 2 && ufr == 1) base = handWarp * 4;
							if (lfr == 1 && ufr == 0) base = handWarp * 5;
							if (lfr == 2 && ufr == 0) base = handWarp * 8;
							if (lfr == 2 && ufr == 2) base = handWarp * 6;
							if (lfr == 1 && ufr == 1) base = handWarp * 2;
							if (lfr == 0 && ufr == 0) base = handWarp * 4;
						case MIDDLE:
							if (lfr == 2 && ufr == 1) base = handWarp * 6;
							if (lfr == 1 && ufr == 0) base = handWarp * 4;
							if (lfr == 2 && ufr == 0) base = handWarp * 6;
							if (lfr == 2 && ufr == 2) base = handWarp * 8;
							if (lfr == 1 && ufr == 1) base = handWarp * 4;
							if (lfr == 0 && ufr == 0) base = handWarp * 3;
					}
				}
	}