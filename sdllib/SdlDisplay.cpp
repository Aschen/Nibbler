//
// SdlDisplay.cpp for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:58:14 2014 brunne-r
// Last update Sat Mar 22 17:21:56 2014 brunne-r
//

#include "SdlDisplay.hh"

SdlDisplay::SdlDisplay()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      throw SdlDisplay::SdlError(SDL_GetError());
    }
}

SdlDisplay::~SdlDisplay()
{
  SDL_Quit();
}

void		SdlDisplay::display(const std::vector<AObject*> &map) const
{
  (void)map;
}

Key			SdlDisplay::getKey(void) const
{
  static SDL_Event	e;

  SDL_WaitEvent(&e);

  if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
	{
	case SDLK_UP:
	  return UP;
	case SDLK_DOWN:
	  return DOWN;
	case SDLK_LEFT:
	  return LEFT;
	case SDLK_RIGHT:
	  return RIGHT;
	case SDLK_ESCAPE:
	  return QUIT;
	default:
	  return OTHERS;
	}
    }
  else if (e.type == SDL_QUIT)
    return QUIT;
  else
    return OTHERS;
}

void		SdlDisplay::init(int width, int height)
{
  _screen = SDL_SetVideoMode(width * SBLOCK,
			     height * SBLOCK,
			     0,
			     SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!_screen)
    {
      throw SdlDisplay::SdlError(SDL_GetError());
    }
}

extern "C" IDisplay *getDisplay(void)
{
  return new SdlDisplay();
}
