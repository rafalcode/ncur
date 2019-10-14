CC=gcc
FLAGS=-Wall -g
LIBS=-lncurses

EXES=h0 h0a h0b h1 h2 h2a

h0: h0.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

h0a: h0a.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

h0b: h0b.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

h1: h1.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

h2: h2.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

h2a: h2a.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

all: ${EXES}

.PHONY: clean

clean:
	@rm -f ${EXES}
