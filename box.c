#include <unistd.h>
#include "term.h"
#include "box.h"

int bc_box(int x1, int y1, int x2, int y2) {
	int rows, cols, i, j;

	mt_getscreensize(&rows, &cols);
	if (x1 + x2 > cols || y1 + y2 > rows) {
		return -1;
	}

	write(1, ASCII, 3);
	mt_gotoXY(x1, y1);
	
	write(1, LU_CORNER, 1);
	for (i = 1; i < x2; i++) {
		write(1, HLINE, 1);
	}
	
	write(1, RU_CORNER, 1);
	for (i = 1; i < y2; i++) {
		mt_gotoXY(x1, y1 + i);
		write(1, VLINE, 1);
		for (j = 1; j < x2; j++) {
			write (1, " ", 1);
		}
		write(1, VLINE, 1);
	}
	
	mt_gotoXY(x1, y1 + y2);
	write(1, LD_CORNER, 1);
	for (i = 1; i < x2; i++) {
		write(1, HLINE, 1);
	}
	write(1, RD_CORNER, 1);
	write(1, NON_ASCII, 3);
	return 0;
}
