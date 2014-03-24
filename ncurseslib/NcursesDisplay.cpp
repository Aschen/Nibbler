//
// NcursesDisplay.cpp for - in /home/brunne_r/Links/nibbler/ncurseslib
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Mon Mar 24 12:31:17 2014 brunne-r
// Last update Mon Mar 24 13:44:33 2014 brunne-r
//

#include "NcursesDisplay.hh"

NcursesDisplay::NcursesDisplay()
{
  if (initscr() == NULL ||
      cbreak() == ERR ||
      keypad(stdscr, TRUE) == ERR ||
      noecho() == ERR)
    throw NcursesDisplay::NcursesError("Unable to init Ncurses.");
}

NcursesDisplay::~NcursesDisplay()
{
  delwin(_win);
  endwin();
}

void NcursesDisplay::init(int width, int height)
{
  _win = newwin((width + 2) * 2, height * 2,
		0, 0);
  if (!_win)
    throw NcursesDisplay::NcursesError("Cannot launch ncurses");
  if (wborder(_win,'|', '|', '-', '-', '+', '+', '+', '+') == ERR)
    throw NcursesDisplay::NcursesError("Ncurses runtime error.");
  if (wrefresh(_win) == ERR)
    throw NcursesDisplay::NcursesError("Ncurses runtime error.");
}

void NcursesDisplay::display(const std::vector<AObject*> &map) const
{
  (void)map;
}

Key	NcursesDisplay::getKey(void) const
{
  int	k;

  k = wgetch(_win);
  return QUIT;
  switch (k)
    {
    case KEY_LEFT:
      return LEFT;
    case KEY_RIGHT:
      return RIGHT;
    case KEY_DOWN:
      return DOWN;
    case KEY_UP:
      return UP;
    case KEY_F(1):
      return QUIT;
    default:
      return OTHERS;
    }
  return UP;
}

extern "C" IDisplay *getDisplay()
{
  return new NcursesDisplay();
}
