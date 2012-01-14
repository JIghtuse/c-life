#include <stdlib.h>
#include <ncurses.h>
#include "menu.h"
#include "universe.h"

void init_ncurses(void);
void close_ncurses(void);
void run_life(cell c, cell newc);

int main (int argc, char *argv[])
{
	int command = 0;
	cell c = NULL, newc = NULL;
	init_ncurses();
	c = malloc (sizeof(cell) * COLS * LINES);
	newc = malloc (sizeof(cell) * COLS * LINES);

	while (command != EXIT) {
		command = get_input_method();
		switch (command) {
			case CLEAR:
				clear_universe(c);
				break;
			case RANDOM:
				rand_universe(c);
				break;
			case RUN:
				run_life(c, newc);
				break;
			case KEYBOARD:
				keyboard_init(c);
				break;
			case EXIT: case MOUSE:
				close_ncurses();
				break;
			case SAVE:
				save_universe(c);
				break;
			default:
				break;
		}
	}

	free(c);
	free(newc);
	return 0;
}

void run_life(cell c, cell newc)
{
	int key;
	int endlife = 0;
	print_universe(c);
	while (!endlife) {
		key = getch();
		switch(key) {
			case 10: case 32:
				print_universe(c);
				update_universe(c, newc);
				break;
			case 3: case KEY_F(5):
				endlife = 1;
				break;
			default:
				break;
		}
	}
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
