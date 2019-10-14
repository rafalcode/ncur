/* this is casual coder's tutorial no. 2
 * ultra importnt point is about the ncurses virtual screen
 * which is where you're manipulations take place, and then the displayed
 * window which will only come about if you refresh.
 *
 * The default refresh is for the screen. If you have a window it needs separate refreshing via wrefresh()
 * However, your primary window will need a refresh() of its own */
#include <curses.h>

int main(int argc, char ** argv)
{
  // 1. Collects information on the terminal window
  // 2. Allocates memory for the two special WINDOWs `stdscr` and `curscr`
  initscr();

  // Concentrate on creating window, so we'll use these values for the window, not the main screen.
  int stpy = 10, stpx =5; // start point x and start point y .. note Fortan convention vertical pos comes first
  int hei = 20, wid =20;

  WINDOW *win = newwin(hei, wid, stpy, stpx); // won;t see if with out borders
  refresh();  // burn window to screen.
  box(win, 0, 0); // applies a broder to your window. the zero si for the top/bottom border char and the second int is for left/right.
  // the border takes up space, so if you are putting in input you need this:
  mvwprintw(win, 1, 1, "This is my box");
  
  // normal refresh won't work now, because we have a window, so: */
  wrefresh(win);
  
  // Wait for user input (blocks to allow us to see the output)
  getch();
  
  endwin();
  // Deallocates memory and restores terminal to saved state prior to program runtime
  
  return 0;
}
