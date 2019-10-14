# Makefile for JustForFun Files

# A few variables

CC=gcc
FLAGS=-Wall -g
LIBS=-lpanel -lncurses

EXES = ex1 ex2 ex3

ex1: ex1.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

ex2: ex2.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

ex3: ex3.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

all: ${EXES}

clean:
	@rm -f ${EXES}
