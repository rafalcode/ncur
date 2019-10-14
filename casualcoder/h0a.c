/* we see here how our last line is ymx -1, not ymx */
#include <curses.h>

int main(int argc, char ** argv)
{
  initscr();
  
  // printw("Hello, World from Casual Coder!\n");
  int ymx, xmx;
  getmaxyx(stdscr, ymx, xmx);
  printw("stdscr size if vertlines=%d, horchars= %d\n", ymx, xmx);
  move(ymx-1, 0); // note this is absolute. It does not depend on number of lines already printed.
  printw("Last line.");
  
  refresh();
  getch();
  endwin();
  
  return 0;
}
