#include <ncurses.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "universe.h"

void clear_universe(cell c) {
	bzero(c, sizeof(c) * COLS * LINES);
	mvprintw(LINES - 2, 0, "Universe cleared!");
	getch();
}

void rand_universe(cell c)
{
	int i, j;
	for (i = 0; i < LINES; i++) {
		for (j = 0; j < COLS; j++) {
			c[i * COLS + j] = rand()/(double)RAND_MAX < 0.5 ? LIFE : EMPTY;
		}
	}
	mvprintw(LINES - 2, 0, "Universe randomized!");
	getch();
}

void keyboard_init(cell c)
{
	int x = 10, y = 10;
	int key = 0;
	int endinput = 0;
	curs_set(1);

	clear();
	print_universe(c);
	mvprintw(0, 0, "Space - toggle, arrows to move, F5 to menu");
	keypad(stdscr, true);
	refresh();
	move(y, x);
	while (!endinput) {
		key = wgetch(stdscr);
		switch(key) {
			case KEY_DOWN:
				if (y == LINES) y = 1;
				else y++;
				break;
			case KEY_UP:
				if (y == 1) y = LINES;
				else y--;
				break;
			case KEY_LEFT:
				if (x == 0) x = COLS;
				else x--;
				break;
			case KEY_RIGHT:
				if (x == COLS) x = 0;
				else x++;
				break;
			case 10: case 32:
				c[y * COLS + x] = 1 - c[y * COLS + x];
				print_universe(c);
				mvprintw(0, 0, "Space - toggle, arrows to move, F5 to menu");
				break;
			case 3: case KEY_F(5):
				endinput = 1;
				break;
			default:
				break;
		}
		move(y, x);
	}
	curs_set(0);
}

void mouse_init(cell c)
{
	return;
}

void print_universe(cell c) {
	int i, j;
	clear();
	mvprintw(0, 0, "Space, Enter to next generation, F5 to menu");
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
