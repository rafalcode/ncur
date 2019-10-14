# Makefile for JustForFun Files

# A few variables

CC=gcc
FLAGS=-Wall -g
LIBS=-lncurses

EXES=hamlet1

# hamlet1 ... starts with text at top left
# prints a spearate string on each line.
# exits with q
hamlet1: hamlet1.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

color_me: color_me.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

all: ${EXES}

clean:
	@rm -f ${EXES}
