/* this is casual coder's tutorial no. 0
 * source code for the hello.c program */
#include <curses.h>

int main(int argc, char ** argv)
{
  // 1. Collects information on the terminal window
  // 2. Allocates memory for the two special WINDOWs `stdscr` and `curscr`
  initscr();
  
  // Prints "Hello, World!" at the current cursor position
  // thi is the very basic output content. Starts at top left.
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
