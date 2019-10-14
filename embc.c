/* Embolden C comments: doesn't hold window
 * pager functionality by Joseph Spainhour" <spainhou@bellsouth.net> */
#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
    /* declarations */
    int ch, prev, row, col;
    prev = EOF; /* will remember our previous character */
    FILE *fp;
    int y, x;
    /* argument checking */
    if(argc != 2) {
        printf("Usage: %s <a c file name>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Cannot open input file");
        exit(1);
    }

    /* ncurses program proper */
    initscr();				/* Start curses mode */
    getmaxyx(stdscr, row, col);		/* find the boundaries of the screeen */

    while((ch = fgetc(fp)) != EOF) {	/* read the file till we reach the end */

        getyx(stdscr, y, x);		/* get the current curser position */
        if(y == (row - 1)) {			/* are we are at the end of the screen */
            printw("<-Press Any Key->");	/* tell the user to press a key */
//             printw("Press a key now to page");
            getch();
            clear();				/* clear the screen */
            move(0, 0);			/* start at the beginning of the screen */
        }

        if(prev == '/' && ch == '*') {   	/* If it is / and * then only switch bold on */    
            attron(A_BOLD);			/* cut bold on */
            getyx(stdscr, y, x);		/* get the current curser position */
            move(y, x - 1);			/* back up one space */
            printw("%c%c", '/', ch); 		/* The actual printing is done here */
        } else
            printw("%c", ch); /* print the character as normal */

        refresh();

        if(prev == '*' && ch == '/')
            attroff(A_BOLD); /* Switch it off once we got  and then / */
        prev = ch;
    }
    getch(); /*without this, screen does not hold */
    endwin(); /* End curses mode */
    fclose(fp);
    return 0;
}
