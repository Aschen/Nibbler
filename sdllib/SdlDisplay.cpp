//
// SdlDisplay.cpp for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:58:14 2014 brunne-r
// Last update Mon Mar 24 17:45:41 2014 brunne-r
//

#include "SdlDisplay.hh"

SdlDisplay::SdlDisplay()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw SdlError(SDL_GetError());

  _surfaces = new SDL_Surface*[3];
  if (!_surfaces)
    throw SdlError("Cannot allocate more memory.");
}

SdlDisplay::~SdlDisplay()
{
  SDL_FreeSurface(_surfaces[WALL]);
  SDL_FreeSurface(_surfaces[SNAKE]);
  SDL_FreeSurface(_surfaces[POWERUP]);
  delete[] _surfaces;
  SDL_FreeSurface(_fond);
  SDL_Quit();
}

void		SdlDisplay::display(const std::vector<AObject*> &map) const
{
  std::vector<Coord>	c;
  SDL_Rect	off;
  SDL_Surface	*actu;

  std::vector<AObject*>::const_iterator	it, end;
  std::vector<Coord>::const_iterator a, z;

  end = map.end();
  it = map.begin();
  off.x = 0;
  off.y = 0;
  if (SDL_BlitSurface(_fond, NULL, _screen, &off) < 0)
    throw SdlError("Unexpected error while drawing\n");
  while (it < end)
    {
      c = ((*it)->getCoord());
      a = c.begin();
      z = c.end();
      actu = _surfaces[(*it)->getType()];
      while (a < z)
	{
	  off.x = (*a).first * SBLOCK;
	  off.y = (*a).second * SBLOCK;
	  if (SDL_BlitSurface(actu, NULL, _screen, &off) < 0)
	    throw SdlError("Unexpected error while drawing\n");
	  ++a;
	}
      ++it;
    }
  if (SDL_Flip(_screen) < 0)
    throw SdlError("Undexpected error while drawing");
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
    throw SdlError("Cannot load images\n");
  i = 0;
  while (i < width)
    {
      j = 0;
      while (j < height)
	{
	  off.x = (i * SBLOCK);
	  off.y = (j * SBLOCK);
	  if (SDL_BlitSurface(ground, NULL, _fond, &off) < 0)
	    throw SdlError("Unexpected error while drawing\n");
	  ++j;
	}
      ++i;
    }
  off.x = 0;
  off.y = 0;
  if (SDL_BlitSurface(_fond, NULL, _screen, &off) < 0 ||
      SDL_Flip(_screen) < 0)
    throw SdlError("Unexpected error while drawing\n");
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
      throw SdlError(SDL_GetError());
    }
  else
    {
      initFond(width, height);
      _surfaces[WALL] = IMG_Load("./images/wood.png");
      _surfaces[SNAKE] = IMG_Load("./images/snake_body.png");
      _surfaces[POWERUP] = IMG_Load("./images/apple.png");
      if (!_surfaces[WALL] || !_surfaces[SNAKE] || !_surfaces[POWERUP])
	throw SdlError("Cannot load images.");
    }
}

extern "C" IDisplay *getDisplay(void)
{
  return new SdlDisplay();
}


///////////
// Error //
///////////
SdlDisplay::SdlError::SdlError(const std::string &error) : NibblerException(error)
{
}

const std::string SdlDisplay::SdlError::getMessage(void) const
{
    std::stringstream   ss;

    ss << "SdlDisplay : " << this->getError();
    return ss.str();
}
