/* this is casual coder's tutorial no. 1
 * source code for the hello.c program */
#include <curses.h>

int main(int argc, char ** argv)
{
  // 1. Collects information on the terminal window
  // 2. Allocates memory for the two special WINDOWs `stdscr` and `curscr`
  initscr();
  int stpy = 10, stpx =5; // start point x and start point y .. note Fortan convention vertical pos comes first
  move(stpy, stpx); // first position of cursor

  /* important note here: the start point is not pixels, its a full line for y and a charecter width for x
   * but because charw is much less than line thickness, if both are equal, you definitely will not get a square! */
  
  // our boring content:
  printw("Hello, World from Casual Coder!");
  
  // Updates the terminal window to match `stdscr`
  // RF would say screen, because window is something else, it's subservient to the screen
  refresh();
  
  // Wait for user input (blocks to allow us to see the output)
  getch();
  
  endwin();
  // Deallocates memory and restores terminal to saved state prior to program runtime
  
  return 0;
}
