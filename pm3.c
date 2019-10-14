/* OK, this is a much less annoying version of pm. Gets decent data, gets rid of
 * the pesky cursor, etc. */
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/* proto */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{

    initscr();			/* Start curses mode 		*/
    int row, col;
    getmaxyx(stdscr, row, col);		/* find the boundaries of the screeen */

    /* do you want get stuck with the cursor being shown, if not go for this baby */
    curs_set(0);

    char comment[128];
    sprintf(comment, "this screen has %i rows and %i columns", row, col);
	if(has_colors() == FALSE) {
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();	/* Start color */
	init_pair(1, COLOR_RED, COLOR_BLACK); /*  convetnion is to use colors in pairs */
	init_pair(2, COLOR_BLUE, COLOR_BLACK); /*  convetnion is to use colors in pairs */
	init_pair(3, COLOR_GREEN, COLOR_BLACK); /*  convetnion is to use colors in pairs */
	init_pair(4, COLOR_YELLOW, COLOR_BLACK); /*  convetnion is to use colors in pairs */

	attron(COLOR_PAIR(4)); /*  attribute on */
	print_in_middle(stdscr, row/2, 0, col, comment);
	attroff(COLOR_PAIR(4));

    /*  now if you don't put getch() next .. the painted screen won't stay on for even a second,
     *  though you will see a flicker. Basically this is a hack, the prog asks for a character
     *  and will hold whatever's on until it gets one.
     *  The upshot is, the screen holds and then when you press a key is all disappears,
     *  as if you had pressed ESC */
//    	getch();
    	sleep(2);
	endwin();
    return 0;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}
