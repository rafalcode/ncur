# Makefile for JustForFun Files

# A few variables

CC=gcc
FLAGS=-Wall -g
LIBS=-lncurses
INCS=-I./include

EXES = hanoi life magic queens shuffle tt dots pm pm2 embc meh pm7 pm7a

# meh, a very basic program
meh: meh.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

hanoi: hanoi.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

queens: queens.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

magic: magic.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

shuffle: shuffle.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# typing practice, works only OK
tt: tt.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# from HOWTO, just prints something in the midel with colors.
pm: pm.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# pm2 clars some annoying beginner's sutff otu of pm.c
pm2: pm2.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

f2llb:f2llb.c
	${CC} ${FLAGS} -o $@ $<

# pm3 will incorporate microsec screening of strings in the middel of the screen
pm3: pm3.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

#  OK, pm4 was able to time up and screen a poem.
pm4: pm4.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

pm5: pm5.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# I was interested in making the Shallott slide show more dramatic
# of course you need to print out he words. SO here I start the mods by
# courting the words.
pm6: pm6.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# so I kept on goign and realised how neat it would be to have an array of strings for the 
# words in each line. But that would make things to complicated so I did some hazardous editting
# to print character by charavter and actually it did not go so bady. Actually owrked with no leaks.
pm7: pm7.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# Get rid of the ncurses .. because I need to work on the text
pm7a: pm7a.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# embolden c comments, includes a pager
embc: embc.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

# very crude version of life program
life: life.c
	${CC} ${FLAGS} -o $@ $< ${LIBS}

dots: dots.c
	${CC} ${FLAGS} -o $@ $< $(INCS) ${LIBS}

dots1: dots1.c
	${CC} ${FLAGS} -o $@ $< $(INCS) ${LIBS}

# very confused editting stilll on this.
dots2: dots2.c
	${CC} ${FLAGS} -o $@ $< $(INCS) ${LIBS}

all: ${EXES}

clean:
	@rm -f ${EXES}
