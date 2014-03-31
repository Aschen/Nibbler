//
// NcursesDisplay.cpp for - in /home/brunne_r/Links/nibbler/ncurseslib
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Mon Mar 24 12:31:17 2014 brunne-r
// Last update Mon Mar 31 16:08:35 2014 brunne-r
//

#include "NcursesDisplay.hh"

NcursesDisplay::NcursesDisplay()
{
  std::cout << "Start init" << std::endl;
  if (initscr() == NULL ||
      cbreak() == ERR ||
      keypad(stdscr, TRUE) == ERR ||
      noecho() == ERR ||
      start_color() == ERR)
    {
      std::cout << "launch error" << std::endl;
      throw NcursesError("Unable to init Ncurses.");
    }
  std::cout << "FIN init" << std::endl;
  init_pair(SNAKE + 1, COLOR_BLACK, COLOR_GREEN);
  init_pair(POWERUP + 1, COLOR_BLACK, COLOR_RED);
  init_pair(WALL + 1, COLOR_BLACK, COLOR_BLUE);
  init_pair(8, COLOR_BLACK, COLOR_BLACK);
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
  std::vector<Coord>	c;

  std::vector<AObject*>::const_iterator	it, end;
  std::vector<Coord>::const_iterator a, z;

  end = map.end();
  it = map.begin();
  while (it < end)
    {
      c = ((*it)->getCoord());
      a = c.begin();
      z = c.end();
      while (a < z)
	{
	  if (wmove(_win, (*a).second + 1, (*a).first * 2 + 2) == ERR ||
	      wattron(_win, COLOR_PAIR((*it)->getType() + 1)) == ERR ||
	      wprintw(_win, "  ") == ERR)
	    throw NcursesError("Unexpected error while drawing\n");
	  ++a;
	}
      ++it;
    }
  if (wrefresh(_win) == ERR)
    throw NcursesError("Undexpected error while drawing");
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

///////////
// Error //
///////////

NcursesDisplay::NcursesError::NcursesError(const std::string &error) : NibblerException("NcursesDisplay")
{
    _msg << error << std::endl;
}

NcursesDisplay::NcursesError::NcursesError(const NcursesDisplay::NcursesError &cpy) : NibblerException("NcursesDisplay")
{
    if (&cpy != this)
    {
        _msg << this->getMessage();
    }
}

const std::string NcursesDisplay::NcursesError::getMessage() const
{
    return _msg.str();
}
