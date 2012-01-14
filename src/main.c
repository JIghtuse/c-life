#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define LIFE 1
#define EMPTY 0
#define SYMBOL '#'

#define NBORN 3
#define NMIN 2
#define NMAX 3

typedef unsigned short int *cell;

void init_universe(cell c, cell newc);
void update_universe(cell c, cell newc);
void print_universe(cell c);

int main (int argc, char *argv[])
{
	cell c = NULL, newc = NULL;

	srand(time(NULL));
	
	initscr();
	curs_set(0);

	c = malloc (sizeof(cell) * COLS * LINES);
	newc = malloc (sizeof(cell) * COLS * LINES);

	init_universe(c, newc);
	print_universe(c);
	while (1) {
		sleep(1);
		print_universe(c);
		update_universe(c, newc);
	}

	curs_set(1);
	endwin();
	free(c);
	free(newc);
	return 0;
}

void init_universe(cell c, cell newc)
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
