//
// SdlDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:37:26 2014 brunne-r
// Last update Sat Apr  5 12:03:17 2014 brunne-r
//

#ifndef SDLDISPLAY_H
# define SDLDISPLAY_H

# include <stdexcept>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_rotozoom.h>
# include "AObject.hh"
# include "DLLoader.hh"
# include "IDisplay.hh"

class		SdlDisplay : public IDisplay
{
private:
  SDL_Surface	*_screen;
  SDL_Surface	*_fond;
  SDL_Surface	**_surfaces;
  SDL_Surface	*_extras[2];

  SDL_Surface*	headDirection(const std::vector<Coord> &c) const;
  SDL_Surface*	queueDirection(const std::vector<Coord> &c) const;
  void		initFond(int width, int height);
public:
  SdlDisplay();
  ~SdlDisplay();
public:
  void		init(int width, int height);
  void		display(const std::vector<AObject*> &map) const;
  Key		getKey(void) const;
};

#endif /* !SDLDISPLAY_H */
