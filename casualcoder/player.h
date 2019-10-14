/* ------------------------------------
 *               PLAYER.H
 * ------------------------------------
 * A basic implementation of a top-down
 * style player. Not optimized or feat-
 * ture rich, but easy to understand.
 * ------------------------------------
 * @author Austin Fishbaugh
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
  public:
    Player(WINDOW * win, int yc, int xc, char c);

    void mvup();
    void mvdown();
    void mvleft();
    void mvright();
    int  getmv();
    void display();

  private:
    int x, y, width, height;
    char character;
    WINDOW * curwin;
};

Player::Player(WINDOW * win, int yc, int xc, char c)
{
  curwin = win;
  y = yc;
  x = xc;
  getmaxyx(curwin, height, width);
  keypad(curwin, true);
  character = c;
}

void Player::mvup()
{
  mvwaddch(curwin, y, x, ' ');
  y -= 1;
  if(y < 1)
    y = 1;
}

void Player::mvdown()
{
  mvwaddch(curwin, y, x, ' ');
  y += 1;
  if(y > yMax-1)
    y = yMax-1;
}

void Player::mvleft()
{
  mvwaddch(curwin, y, x, ' ');
  x -= 1;
  if(x < 1)
    x = 1;
}

void Player::mvright()
{
  mvwaddch(curwin, y, x, ' ');
  x += 1;
  if(x > xMax-1)
    x = xMax-1;
}

int Player::getmv()
{
  int choice = wgetch(curwin);
  switch(choice)
  {
    case KEY_UP:
      mvup();
      break;
    case KEY_DOWN:
      mvdown();
      break;
    case KEY_LEFT:
      mvleft();
      break;
    case KEY_RIGHT:
      mvright();
      break;
    default:
      break;
  }
  return choice;
}

void Player::display()
{
  mvwaddch(curwin, y, x, character);
}

#endif
