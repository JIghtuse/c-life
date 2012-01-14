#include "universe.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void init_universe(cell c)
{
	return;
}

void rand_universe(cell c)
{
	int i, j;
	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			c[i * COLS + j] = rand()/(double)RAND_MAX < 0.5 ? LIFE : EMPTY;
		}
	}
}

void print_universe(cell c) {
	int i, j;
	clear();
	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			if (c[i * COLS + j] == LIFE) {
				mvprintw(i, j, "%c", SYMBOL);
			}
		}
	}
	refresh();
}

void update_universe(cell c, cell newc) {
	int i, j, ni, neighs;

	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			neighs = 0;
			for (ni = i - 1; ni <= i + 1; ni++) {
				if (c[ni * COLS + (j - 1)] == LIFE) neighs++;
				if (c[ni * COLS + (j + 1)] == LIFE) neighs++;
			}
			if (c[(i - 1) * COLS + j] == LIFE) neighs++;
			if (c[(i + 1) * COLS + j] == LIFE) neighs++;

			if (c[i * COLS + j] != LIFE) {
				newc[i * COLS + j] = (neighs == NBORN) ? LIFE : EMPTY;
			} else {
				newc[i * COLS + j] = (neighs > NMAX || neighs < NMIN) ? EMPTY : LIFE;
			}
		}
	}
	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			c[i * COLS + j] = newc[i * COLS + j];
		}
	}
}

void save_universe(cell c)
{
	FILE *fp;
	char fname[20];
	int i, j;

	sprintf(fname, "%d.txt", (int)time(NULL));
	fp = fopen(fname, "wt");
	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			fprintf(fp, "%d", c[i * COLS + j] == LIFE ? 1 : 0);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
