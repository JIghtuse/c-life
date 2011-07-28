#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "term.h"

int mt_clrscr(void) {
	write(1,"\033[H\033[2J",7);
	return 0;
}

int mt_getscreensize(int *rows, int *cols) {
	struct winsize ws;
	if (rows == NULL || cols == NULL) {
		return -1;
	}
	
	if (!ioctl(1,TIOCGWINSZ, &ws)) {
		(*rows) = ws.ws_row;
		(*cols) = ws.ws_col;
		return 0;
	} else {
		return -1;
	}
}

int mt_gotoXY(int x, int y) {
	int len, rows, cols;
	char s[20];
	mt_getscreensize(&rows, &cols);
	if (x < 0 || y < 0 || x > cols || y > rows) {
		return -1;
	}
	len = sprintf (s, "\033[%d;%dH", y, x);
	write(1, s, len);
	return 0;
}
