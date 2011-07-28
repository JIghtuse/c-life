#include "universe.h"

void update_universe(short int *a, short int *anew, int cols, int rows)
{
	int i, j, ni;
	int nneigh = 0;

	for (i = 1; i < rows - 1; i++) {
		for (j = 1; j < cols - 1; j++) {
			/* present generation */
			nneigh = 0;
			for (ni = i - 1; ni <= i + 1; ni++) {
				if (a[ni * cols + (j - 1)] == LIFE) {
					nneigh++;
				}
				if (a[ni * cols + (j + 1)] == LIFE) {
					nneigh++;
				}
			}
			if (a[(i - 1) * cols + j] == LIFE) {
				nneigh++;
			}
			if (a[(i + 1) * cols + j] == LIFE) {
				nneigh++;
			}
			/* new generation forming */

			if (a[i * cols + j] == 0) {
				if (nneigh == NBORN) {
					anew[i * cols + j] = LIFE;
				} else {
					anew[i * cols + j] = EMPTY;
				}
			} else {
				if (nneigh > NMAX || nneigh < NMIN) {
					anew[i * cols + j] = EMPTY;
				} else {
					anew[i * cols + j] = LIFE;
				}
			}
		}
	}

	/* changing generations*/
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			a[i * cols + j] = anew[i * cols + j];
		}
	}

	return;
}
