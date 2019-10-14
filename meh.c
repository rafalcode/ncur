#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include <unistd.h> 

int main()
{
    char mesg[]="Just a string";
    int row,col;

    initscr();
    getmaxyx(stdscr, row, col); /* stdscr, the default screen */
    mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

    /* print the message at the center of the screen */
    mvprintw(row-5, 0, "This screen has %d rows and %d columns\n", row, col);

    printw("Try resizing your window(if possible) and then run this program again");
    refresh();
    char ch=getch(); /* seems to hold the window and wait for any key press */
    printw("%c", ch);
    sleep(2);
    endwin();

    return 0;
}
