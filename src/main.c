#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define LIFE 1
#define EMPTY 0
#define SYMBOL '#'

typedef unsigned short int *cell;

void init_universe(cell c, cell newc);
void print_universe(cell c);

int main (int argc, char *argv[])
{
	cell c = NULL, newc = NULL;

	srand(time(NULL));
	
	initscr();
	printw("Hello world! cols: %d, rows: %d\n", COLS, LINES);

	c = malloc (sizeof(cell) * COLS * LINES);
	newc = malloc (sizeof(cell) * COLS * LINES);

	init_universe(c, newc);
	print_universe(c);

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

	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			mvprintw(i, j, "%c", c[i * COLS + j] == LIFE ? SYMBOL : ' ');
		}
	}

	refresh();
	getch();
}
