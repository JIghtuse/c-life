#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sighandler.h"
#include "term.h"

void int_handler(int sig) {

	signal(sig, SIG_IGN);
	/* restore terminal parameters */
	write(1, NONASCII, 3);
	write(1, "\033[?25h", 6);
	mt_clrscr();

	exit(0);
}
