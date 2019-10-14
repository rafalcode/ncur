#include <stdlib.h>
#include <curses.h>

void prtwres(WINDOW *win, int lnum, char *cmd)
{
    FILE *fp=NULL;
    char *line=NULL;
    size_t len;
    ssize_t nread;
    if( (fp = popen(cmd, "r")) == NULL) {
        fprintf(stderr, "Failed to run sys call\n" );
        exit(EXIT_FAILURE);
    }
    len = 0;
    while ((nread = getline(&line, &len, fp)) != -1) {
        mvwprintw(win, lnum, 1, "%.*s", nread-1, line);
    }
    wrefresh(win);
}

int main(int argc, char ** argv)
{
    initscr();
    raw();				/* Line buffering disabled	*/
    noecho();			/* Don't echo() while we do getch */

    int ymx, xmx, ch;
    getmaxyx(stdscr, ymx, xmx);
    char *cmdSeq[2]={"uname -a", "uptime"};

    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/

    WINDOW *win = newwin(ymx, xmx, 0, 0);
    refresh(); // burn window to screen.
    box(win, 0, 0); // applies border

    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(EXIT_FAILURE);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);


    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 1, xmx/4, "Welcome to task interfacer");
    wattroff(win, COLOR_PAIR(4));
    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, 2, xmx/6, "Instructions: Right arrow advances, any other key quits");
    wattroff(win, COLOR_PAIR(6));
    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 4, 1, "Task 1: %s ...", cmdSeq[0]);
    wattroff(win, COLOR_PAIR(5));
    wrefresh(win);

    ch=getch();
    if(ch==KEY_RIGHT)
        prtwres(win, 5, cmdSeq[0]);

    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 7, 1, "Task 2: %s ...", cmdSeq[1]);
    wattroff(win, COLOR_PAIR(5));
    wrefresh(win);
    ch=getch();
    if(ch==KEY_RIGHT)
        prtwres(win, 8, cmdSeq[1]);

    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, 10, 1, "Task list has ended. Press any key to quit");
    wattroff(win, COLOR_PAIR(6));
    wrefresh(win);
    getch();
    endwin();
    return 0;
}
