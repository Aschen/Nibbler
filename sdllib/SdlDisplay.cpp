//
// SdlDisplay.cpp for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:58:14 2014 brunne-r
// Last update Sat Mar 22 19:03:34 2014 brunne-r
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
  SDL_FreeSurface(_fond);
  SDL_Quit();
}

void		SdlDisplay::display(const std::vector<AObject*> &map) const
{
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

void		SdlDisplay::initFond(int width, int height)
{
  int		i;
  int		j;
  SDL_Rect	off;
  SDL_Surface	*ground;

  ground = IMG_Load("./images/ground.png");
  _fond = SDL_CreateRGBSurface(SDL_HWSURFACE, width * SBLOCK,
			       height * SBLOCK, 32, 0, 0, 0, 0);
  if (!ground || !_fond)
    throw SdlDisplay::SdlError("Cannot load images\n");
  i = 0;
  while (i < width)
    {
      j = 0;
      while (j < height)
	{
	  off.x = (i * SBLOCK);
	  off.y = (j * SBLOCK);
	  if (SDL_BlitSurface(ground, NULL, _fond, &off) < 0)
	    throw SdlDisplay::SdlError("Unexpected error while drawing\n");
	  ++j;
	}
      ++i;
    }
  off.x = 0;
  off.y = 0;
  if (SDL_BlitSurface(_fond, NULL, _screen, &off) < 0 ||
      SDL_Flip(_screen) < 0)
    throw SdlDisplay::SdlError("Unexpected error while drawing\n");
  SDL_FreeSurface(ground);
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
  else
    {
      initFond(width, height);
    }
}

extern "C" IDisplay *getDisplay(void)
{
  return new SdlDisplay();
}
