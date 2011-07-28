.PHONY: all clean

CC = gcc
CFLAGS = -Wall -pedantic -Werror

all: clife

clife: universe.o main.o term.o box.o sighandler.o io.o
	$(CC) $(CFLAGS) $^ -o $@

main: main.c
universe.o: universe.c universe.h
term.o: term.c term.h
box.o: box.c box.h
sighandler.o: sighandler.c sighandler.h
io.o: io.c io.h

.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	rm clife *.o
