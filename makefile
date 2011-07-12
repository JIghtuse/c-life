.PHONY: all clean

all: clife.c
	gcc -Wall -pedantic -Werror clife.c -o clife

clean: 
	rm clife
