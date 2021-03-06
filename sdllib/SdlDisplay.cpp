//
// SdlDisplay.cpp for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:58:14 2014 brunne-r
// Last update Sun Apr  6 16:25:07 2014 brunne-r
//

#include "SdlDisplay.hh"

SdlDisplay::SdlDisplay()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error(SDL_GetError());
  _surfaces = new SDL_Surface*[4];
  if (!_surfaces)
    throw std::runtime_error("Cannot allocate more memory.");
  _surfaces[WALL] = NULL;
  _surfaces[SNAKE] = NULL;
  _surfaces[POWERUP] = NULL;
  _surfaces[PORTAL] = NULL;
  _extras[0] = NULL;
  _extras[1] = NULL;
  _fond = NULL;
}

SdlDisplay::~SdlDisplay()
{
  if (_surfaces[WALL])
    SDL_FreeSurface(_surfaces[WALL]);
  if (_surfaces[SNAKE])
    SDL_FreeSurface(_surfaces[SNAKE]);
  if (_surfaces[POWERUP])
    SDL_FreeSurface(_surfaces[POWERUP]);
  if (_surfaces[PORTAL])
  SDL_FreeSurface(_surfaces[PORTAL]);
  delete[] _surfaces;
  if (_extras[0])
    SDL_FreeSurface(_extras[0]);
  if (_extras[1])
    SDL_FreeSurface(_extras[1]);
  if (_fond)
    SDL_FreeSurface(_fond);
  SDL_Quit();
}

SDL_Surface*	SdlDisplay::headDirection(const std::vector<Coord> &c) const
{
  std::vector<Coord>::const_iterator	a, z;
  int					sx, sy;
  double				angle(180.0);

  a = c.begin();
  z = a + 1;
  sx = (*a).first - (*z).first;
  sy = (*a).second - (*z).second;
  if (sy < 0)
    angle = 0.0;
  else if (sx > 0)
    angle = -90.0;
  else if (sx < 0)
    angle = 90.0;
  return rotozoomSurface(_extras[0], angle, 1.0, 0);
}

SDL_Surface*	SdlDisplay::queueDirection(const std::vector<Coord> &c) const
{
  std::vector<Coord>::const_iterator	a, z;
  int					sx, sy;
  double				angle(0.0);

  a = c.end();
  --a;
  z = a - 1;
  sx = (*a).first - (*z).first;
  sy = (*a).second - (*z).second;
  if (sy < 0)
    angle = 180.0;
  else if (sx > 0)
    angle = 90.0;
  else if (sx < 0)
    angle = -90.0;
  return rotozoomSurface(_extras[1], angle, 1.0, 0);
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
    throw std::runtime_error("Unexpected error while drawing.");
  while (it < end)
    {
      c = ((*it)->getCoord());
      a = c.begin();
      z = c.end();
      while (a < z)
	{
	  actu = _surfaces[(*it)->getType()];
	  if ((*it)->getType() == SNAKE && a == c.begin())
	    actu = headDirection(c);
	  else if ((*it)->getType() == SNAKE && a + 1 == c.end())
	    actu = queueDirection(c);
	  off.x = (*a).first * SBLOCK;
	  off.y = (*a).second * SBLOCK;
	  if (SDL_BlitSurface(actu, NULL, _screen, &off) < 0)
	    throw std::runtime_error("Unexpected error while drawing.");
	  ++a;
	}
      ++it;
    }
  if (SDL_Flip(_screen) < 0)
    throw std::runtime_error("Unexpected error while drawing.");
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
    case SDLK_SPACE:
      return SPACE;
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
    throw std::runtime_error("Cannot load images.");
  i = 0;
  while (i < width)
    {
      j = 0;
      while (j < height)
	{
	  off.x = (i * SBLOCK);
	  off.y = (j * SBLOCK);
	  if (SDL_BlitSurface(ground, NULL, _fond, &off) < 0)
	    throw std::runtime_error("Unexpected error while drawing.");
	  ++j;
	}
      ++i;
    }
  off.x = 0;
  off.y = 0;
  if (SDL_BlitSurface(_fond, NULL, _screen, &off) < 0 ||
      SDL_Flip(_screen) < 0)
    throw std::runtime_error("Unexpected error while drawing.");
  SDL_FreeSurface(ground);
}

void		SdlDisplay::init(int width, int height)
{
  if (width * SBLOCK > 1920 || height * SBLOCK > 1080)
    throw std::runtime_error("The size of the map is too big");
  else if (width < 10 || height < 10)
    throw std::runtime_error("The size of the map is too small");
  _screen = SDL_SetVideoMode(width * SBLOCK,
			     height * SBLOCK,
			     0,
			     SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!_screen)
    throw std::runtime_error(SDL_GetError());
  else
    {
      initFond(width, height);
      _surfaces[WALL] = IMG_Load("./images/wood.png");
      _surfaces[SNAKE] = IMG_Load("./images/snake_body.png");
      _surfaces[POWERUP] = IMG_Load("./images/apple.png");
      _surfaces[PORTAL] = IMG_Load("./images/portal.png");
      if (!_surfaces[WALL] || !_surfaces[SNAKE] || !_surfaces[POWERUP] || !_surfaces[PORTAL])
	throw std::runtime_error("Cannot load images.");
      _extras[0] = IMG_Load("./images/snake_head.png");
      _extras[1] = IMG_Load("./images/snake_queue.png");
      if (!_extras[0] || !_extras[1])
	throw std::runtime_error("Cannot load images.");
    }
}

extern "C" IDisplay *getDisplay(void)
{
  return new SdlDisplay();
}
