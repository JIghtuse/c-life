#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "sighandler.h"
#include "universe.h"
#include "term.h"
#include "io.h"

int main(int argc, char *argv[])
{
	int num;
	int cols, rows;
	short int *a = NULL, *anew = NULL;

	signal(SIGINT, int_handler);

	if (mt_getscreensize(&cols, &rows)) {
		printf("Terminal size defining error\n");
		return -1;
	} else {
		/*printf("Setting terminal size: %dx%d\n", rows, cols);*/
		printf("Cell coordinates must be set from (1, 1) to (%d, %d)\n", rows-2, cols-2);
	}

	a = malloc(sizeof(int) * cols * rows);
	anew = malloc(sizeof(int) * cols * rows);

	init_universe(a, anew, cols, rows);

	printf("Input numbers of lifeforms: ");
	scanf("%d", &num);
	while (num-- > 0) {
		add_form(a, anew, cols);
	}

	print_universe(a, cols,rows);
	
	while (1) {
		sleep(1);
		print_universe(a, cols, rows);
		update_universe(a, anew, cols, rows);
	}

	return 0;
}
