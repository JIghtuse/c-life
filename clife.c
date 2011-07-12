#include <stdio.h>
#include <unistd.h>

#define YSIZE 21
#define XSIZE 50
#define NBORN 3
#define NMIN 2
#define NMAX 3

#define UNIT '#'

char a[YSIZE + 2][XSIZE + 2];
char anew[YSIZE + 2][XSIZE + 2];

void init_universe(int sizey, int sixex);
void print_universe(int sizey, int sizex);
void update_universe(int sizey, int sizex);
void add_form();

int main(int argc, char *argv[])
{
	int num;

	init_universe(YSIZE + 1, XSIZE + 1);
	printf("Input numbers of lifeforms: ");
	scanf("%d", &num);
	while (num-- > 0) {
		add_form();
	}

	while (1) {
		print_universe(YSIZE + 2, XSIZE + 2);
		update_universe(YSIZE, XSIZE);
		sleep(1);
	}

	return 0;
}

void update_universe(int sizey, int sizex)
{
	int i, j, ni;
	int nneigh;

	for (i = 1; i <= sizey; i++) {
		for (j = 1; j <= sizex; j++) {
			/* present generation */
			nneigh = 0;
			for (ni = i - 1; ni <= i + 1; ni++) {
				if (a[ni][j - 1] == UNIT) {
					nneigh++;
				}
				if (a[ni][j + 1] == UNIT) {
					nneigh++;
				}
			}
			if (a[i - 1][j] == UNIT) {
				nneigh++;
			}
			if (a[i + 1][j] == UNIT) {
				nneigh++;
			}
			/* new generation forming */

			if (a[i][j] != UNIT) {
				if (nneigh == NBORN) {
					anew[i][j] = UNIT;
				} else {
					anew[i][j] = ' ';
				}
			} else {
				if (nneigh > NMAX || nneigh < NMIN) {
					anew[i][j] = ' ';
				} else {
					anew[i][j] = UNIT;
				}
			}
		}
	}

/* changing generations*/
	for (i = 1; i <= sizey; i++) {
		for (j = 1; j <= sizex; j++) {
			a[i][j]=anew[i][j];
		}
	}

	return;
}

void init_universe(int sizey, int sizex)
{
	int i, j;

	for (i = 1; i < sizey; i++) {
		for (j = 1; j < sizex; j++) {
			a[i][j] = anew[i][j] = ' ';
		}
	}

	for (i = 1; i < sizex; i++) {
		a[0][i] = anew[0][i] = '-';
		a[sizey][i] = anew[sizey][i] = '-';
	}

	for (i = 1; i < sizey; i++) {
		a[i][0] = anew[i][0] = '|';
		a[i][sizex] = anew[i][sizex] = '|';
	}

	a[0][0] = anew[0][0] = '+';
	a[sizey][sizex] = anew[sizey][sizex] = '+';
	a[0][sizex] = anew[0][sizex] = '+';
	a[sizey][0] = anew[sizey][0] = '+';
	return;
}

void print_universe(int sizey, int sizex)
{
	int i, j;
	for (i = 0; i < sizey; i++) {
		for (j = 0; j < sizex; j++) {
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
	return;
}

void add_form(void) {
	int i, j;

	printf("Input coordinates of lifeform(from 1x1 to %dx%d): ", YSIZE, XSIZE);
	scanf("%d%d", &i, &j);
	a[i][j] = UNIT;
	anew[i][j] = UNIT;
}
