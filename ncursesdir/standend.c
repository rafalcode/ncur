#include <ncurses.h>

int main(void)
{
	initscr();

	addstr("Yes, I must admit that ");
	attron(A_BOLD);
	addstr("Chris");
	standend();
	addstr(" is my favorite pupil.");
	refresh();
	getch();

	endwin();
	return 0;
}

