.PHONY: all clean

CC = gcc

CFLAGS = -Wall -pipe -lncurses
PEDANTIC_FLAGS = -pedantic -Werror -ansi -pedantic-errors
APP = clife

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPENDENCIES = $(SOURCES:.c=.d)

BIN_DIR = bin

OPTIMIZATION = -O3
DEBUG = no

ifeq ($(DEBUG), yes)
	CFLAGS += -g
	OPTIMIZATION += -O0
endif

ifeq ($(PEDANTIC), yes)
	CFLAGS += $(PEDANTIC_FLAGS)
endif

all: $(APP)

clean:
	rm -rf $(BIN_DIR)/$(APP) $(OBJECTS) $(DEPENDENCIES)

$(APP): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

%.o: %.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard *.d)
