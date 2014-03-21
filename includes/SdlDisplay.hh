//
// SdlDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:37:26 2014 brunne-r
// Last update Fri Mar 21 17:01:12 2014 brunne-r
//

#ifndef SDLDISPLAY_H
# define SDLDISPLAY_H

# include <SDL/SDL.h>
# include "DLLoader.hh"
# include "IDisplay.hh"

class		SdlDisplay : public IDisplay
{
  class		Error
  {

  };
private:
  SDL_Surface	*screen;
public:
  SdlDisplay();
  ~SdlDisplay();
public:
  void		display(const std::vector<AObject*> &map) const;
  Key		getKey(void) const;
};

IDisplay	*getInstance(void);

#endif /* !SDLDISPLAY_H */
