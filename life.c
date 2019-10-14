#include <curses.h>
#include <stdlib.h>

int STARTX = 0;
int STARTY = 0;
int ENDX = 79;
int ENDY = 24;

#define CELL_CHAR '#'
#define TIME_OUT  300

typedef struct _state /* actually just two ints, olsta and nwsta */
{
	int olsta;
	int nwsta;
} state;

void display(WINDOW *win, state **area, int startx, int starty, int endx, int endy);
void calc(state **area, int x, int y);
void update_state(state **area, int startx, int starty, int endx, int endy);

int main()
{
    state **workarea;
	int i, j;
	
	initscr();
	cbreak();
	timeout(TIME_OUT);
	keypad(stdscr, TRUE);

    /*  note: COLS and LINES are ncurses public vars. */
	ENDX = COLS - 1;
	ENDY = LINES - 1;

	workarea = (state **)calloc(COLS, sizeof(state *));
	for(i = 0;i < COLS; ++i)
		workarea[i] = (state *)calloc(LINES, sizeof(state));
	
	/* For inverted U */
	workarea[39][15].nwsta = TRUE;
	workarea[40][15].nwsta = TRUE;
	workarea[41][15].nwsta = TRUE;
	workarea[39][16].nwsta = TRUE;
	workarea[39][17].nwsta = TRUE;
	workarea[41][16].nwsta = TRUE;
	workarea[41][17].nwsta = TRUE;
	update_state(workarea, STARTX, STARTY, ENDX, ENDY);
	
	/* For block  */
/*
	workarea[37][13].nwsta = TRUE;
	workarea[37][14].nwsta = TRUE;
	workarea[38][13].nwsta = TRUE;
	workarea[38][14].nwsta = TRUE;

	update_state(workarea, STARTX, STARTY, ENDX, ENDY);
*/
	display(stdscr, workarea, STARTX, STARTY, ENDX, ENDY);
	while(getch() != KEY_F(1)) {
        for(i = STARTX; i <= ENDX; ++i)
			for(j = STARTY; j <= ENDY; ++j)
				calc(workarea, i, j);
		update_state(workarea, STARTX, STARTY, ENDX, ENDY);
		display(stdscr,  workarea, STARTX, STARTY, ENDX, ENDY);	
	}
	
	endwin();
	return 0;
}	

void display(WINDOW *win, state **area, int startx, int starty, int endx, int endy)
{	int i, j;
	wclear(win);
	for(i = startx; i <= endx; ++i)
		for(j = starty;j <= endy; ++j)
			if(area[i][j].nwsta == TRUE)
				mvwaddch(win, j, i, CELL_CHAR);
	wrefresh(win);
}

void calc(state **area, int i, int j)
{
    int neighbours;
	int newstate;
 	
	neighbours	= 
		area[(i - 1 + COLS) % COLS][j].olsta		+
		area[(i - 1 + COLS) % COLS][(j - 1 + LINES) % LINES].olsta 	+
		area[(i - 1 + COLS) % COLS][(j + 1) % LINES].olsta 	+
		area[(i + 1) % COLS][j].olsta		+
		area[(i + 1) % COLS][(j - 1 + LINES) % LINES].olsta 	+
		area[(i + 1) % COLS][(j + 1) % LINES].olsta 	+
		area[i][(j - 1 + LINES) % LINES].olsta		+
		area[i][(j + 1) % LINES].olsta;
	
	newstate = FALSE;
	if(area[i][j].olsta == TRUE && (neighbours == 2 || neighbours == 3))
		 newstate = TRUE;
	else
		if(area[i][j].olsta == FALSE && neighbours == 3)
			 newstate = TRUE;
	area[i][j].nwsta = newstate;
}

void update_state(state **area, int startx, int starty, int endx, int endy)
{
    int i, j;
	for(i = startx; i <= endx; ++i)
		for(j = starty; j <= endy; ++j)
			area[i][j].olsta = area[i][j].nwsta;
}
