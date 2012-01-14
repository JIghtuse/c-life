#include <ncurses.h>
#include "menu.h"

char *methods[] = {
	"Random fill",
	"Mouse input",
	"Keyboard input",
	"Exit"
};
int nmethods = sizeof(methods) / sizeof(char *);

int get_input_method(void)
{
	WINDOW *menu_win;
	const int menu_width = 50;
	const int menu_height = 10;

	int hl = 1;
	int choice = 0;
	int c;
	int mstartx = (80 - menu_width) / 2;
	int mstarty = (24 - menu_height) / 2;

	menu_win = newwin(menu_height, menu_width, mstarty, mstartx);
	keypad(menu_win, true);
	mvprintw(0, 0, "Use arrow keys to go up and down, Enter to select input method");
	refresh();
	print_menu(menu_win, hl);
	while (!choice) {
		c = wgetch(menu_win);
		switch(c) {
			case KEY_UP:
				if (hl == 1) hl = nmethods;
				else hl--;
				break;
			case KEY_DOWN:
				if (hl == nmethods) hl = 1;
				else hl++;
				break;
			case 10:
				choice = hl;
				break;
			case 3:
				choice = 4;
				break;
			default:
				mvprintw(24, 0, "Character pressed is = %3d (%c)", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, hl);
	}
	mvprintw(23, 0, "You chose method %d (%s)\n", choice, methods[choice - 1]);
	clrtoeol();
	refresh();
	getch();
	return choice;
}

void print_menu(WINDOW *menu_win, int hl)
{
	int x = 2, y = 2, i;
	box (menu_win, 0, 0);
	for (i = 0; i < nmethods; i++) {
		if (hl == i + 1) {
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", methods[i]);
			wattroff(menu_win, A_REVERSE);
		} else {
			mvwprintw(menu_win, y, x, "%s", methods[i]);
		}
		y++;
	}
	wrefresh(menu_win);
}
