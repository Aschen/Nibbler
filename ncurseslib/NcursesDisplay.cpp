//
// NcursesDisplay.cpp for - in /home/brunne_r/Links/nibbler/ncurseslib
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Mon Mar 24 12:31:17 2014 brunne-r
// Last update Sun Apr  6 13:11:46 2014 brunne-r
//

#include <errno.h>
#include <string.h>
#include <curses.h>
#include "NcursesDisplay.hh"

NcursesDisplay::NcursesDisplay()
{
  if (initscr() == NULL ||
      cbreak() == ERR ||
      keypad(stdscr, TRUE) == ERR ||
      noecho() == ERR ||
      start_color() == ERR ||
      curs_set(0) == ERR)
    throw std::runtime_error("Can't initialize Ncurses");
  init_pair(PORTAL + 1, COLOR_RED, COLOR_BLUE);
  init_pair(SNAKE + 1, COLOR_GREEN, COLOR_BLACK);
  init_pair(POWERUP + 1, COLOR_RED, COLOR_BLACK);
  init_pair(WALL + 1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  strncpy(_chars[SNAKE], "[]", 2);
  strncpy(_chars[POWERUP], "::", 2);
  strncpy(_chars[WALL], "##", 2);
  strncpy(_chars[PORTAL], "()", 2);
}

NcursesDisplay::~NcursesDisplay()
{
  endwin();
}

void NcursesDisplay::init(int width, int height)
{
  if (width < 10 || height < 10 || width * 2 > COLS || height > LINES)
    throw std::runtime_error("Map size is not valid.");
  _lines = height;
  _nbcols = width * 2;
  if (border('|', '|', '-', '-', '+', '+', '+', '+') == ERR)
    throw std::runtime_error("Ncurses runtime error.");
  if (refresh() == ERR)
    throw std::runtime_error("Ncurses runtime error.");
}

void		NcursesDisplay::cleanScr(void) const
{
  int		i(0);
  std::string	empty_line;

  empty_line.reserve(_nbcols + 1);
  fill_n(empty_line.begin(), _nbcols, ' ');
  empty_line[_nbcols] = 0;
  while (i < _lines)
    {
      if (move(i + 1, 1) == ERR ||
	  printw(empty_line.c_str()) == ERR)
	throw std::runtime_error("Unexpected error while drawing\n");
      ++i;
    }
}

void NcursesDisplay::display(const std::vector<AObject*> &map) const
{
  std::vector<Coord>	c;

  std::vector<AObject*>::const_iterator	it, end;
  std::vector<Coord>::const_iterator a, z;

  end = map.end();
  it = map.begin();
  cleanScr();
  while (it < end)
    {
      c = ((*it)->getCoord());
      a = c.begin();
      z = c.end();
      while (a < z)
	{
	  if (move((*a).second + 1, ((*a).first * 2) + 1) == ERR ||
	      attron(COLOR_PAIR((*it)->getType() + 1)) == ERR ||
	      printw(_chars[(*it)->getType()]) == ERR)
	    {
	      throw std::runtime_error("Unexpected error while drawing\n");
	    }
	  ++a;
	}
      ++it;
    }
  if (refresh() == ERR)
    throw std::runtime_error("Undexpected error while drawing");
}

Key	NcursesDisplay::getKey(void) const
{
  int	k;

  k = getch();
  switch (k)
    {
    case 27:
      return QUIT;
    case KEY_LEFT:
      return LEFT;
    case KEY_RIGHT:
      return RIGHT;
    case KEY_F(1):
      return QUIT;
    case ' ':
      return SPACE;
    default:
      return OTHERS;
    }
  return OTHERS;
}

extern "C" IDisplay *getDisplay()
{
  return new NcursesDisplay();
}
