#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>
#include "menu.h"
#include "universe.h"

void init_ncurses(void);
void close_ncurses(void);
void run_life(cell c, cell newc);

int main (int argc, char *argv[])
{
	int command = 0;
	int saving = 0;
	if (argc > 1) {
		saving = 1;
	}
	cell c = NULL, newc = NULL;
	init_ncurses();
	c = malloc (sizeof(cell) * COLS * LINES);
	newc = malloc (sizeof(cell) * COLS * LINES);
	bzero(c, sizeof(c) * COLS * LINES);
	bzero(newc, sizeof(newc) * COLS * LINES);

	while (command != 4) {
		command = get_input_method();
		switch (command) {
			case 1:
				rand_universe(c);
				run_life(c, newc);
				break;
			case 2: case 3: case 4:
				close_ncurses();
				break;
			default:
				break;
		}
	}

	if (saving == 1) save_universe(c);
	free(c);
	free(newc);
	return 0;
}

void run_life(cell c, cell newc)
{
	int key;
	int endlife = 0;
	while (!endlife) {
		key = getch();
		switch(key) {
			case KEY_RIGHT: case 10: case 32:
				print_universe(c);
				update_universe(c, newc);
				break;
			case 27: case 3:
				endlife = 1;
				break;
			default:
				break;
		}
	}
	clear();
	refresh();
}

void init_ncurses(void)
{
	initscr();
	clear();
	raw();
	noecho();
	curs_set(0);
}

void close_ncurses(void)
{
	clear();
	noraw();
	curs_set(1);
	echo();
	endwin();
}
