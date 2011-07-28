#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include "box.h"
#include "term.h"
#include "io.h"
#include "universe.h"

void init_universe(short int *a, short int *anew, int cols, int rows)
{
	bzero(a, sizeof(a[0]) * cols * rows);
	bzero(anew, sizeof(anew[0]) * cols * rows);

	return;
}

void print_universe(short int *a, int cols, int rows)
{
	int i, j;
	
	write(1, "\033[?25l", 6);
	mt_clrscr();
	bc_box(1, 1, rows - 1, cols - 1);
	
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (a[i * cols + j] == LIFE) {
				mt_gotoXY(i + 1, j + 1);
				write(1, UNIT, 1);
			}
		}
	}
	return;
}

void add_form(short int *a, short int *anew, int cols) {
	int i, j;

	printf("Input coordinates: ");
	
	scanf("%d%d", &i, &j);
	
	a[i * cols + j] = LIFE;
	anew[i * cols + j] = LIFE;
	printf("Form at position (%d,%d) added\n", i, j);
	return;
}
