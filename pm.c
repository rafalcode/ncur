/* Crude beginner program to put a string in the middles of the screen.
 * However, "middle" is according to its own settings. See later versions for working out the
 * proper screen settings.
 *  Static screen only, no tupdating or anything like that. */
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>

/* proto */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

int main(int argc, char *argv[])
{
    initscr();			/* Start curses mode 		*/
	if(has_colors() == FALSE) {
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();	/* Start color */
	init_pair(1, COLOR_RED, COLOR_BLACK); /*  convetnion is to use colors in pairs */

	attron(COLOR_PAIR(1)); /*  attribute on */
	print_in_middle(stdscr, LINES / 2, 0, 0, "Voilà !!! In color ...");
	attroff(COLOR_PAIR(1));
    	getch();
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
