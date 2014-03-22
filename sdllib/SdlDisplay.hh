//
// SdlDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:37:26 2014 brunne-r
// Last update Sat Mar 22 15:52:03 2014 brunne-r
//

#ifndef SDLDISPLAY_H
# define SDLDISPLAY_H

# include <SDL/SDL.h>
# include "DLLoader.hh"
# include "IDisplay.hh"
# include "NibblerException.hh"

class		SdlDisplay : public IDisplay
{
  class		SdlError : public NibblerException
  {
  public:
    SdlError(const std::string &error);
  };
private:
  SDL_Surface	*_screen;
public:
  SdlDisplay();
  ~SdlDisplay();
public:
  void		init(int width, int height);
  void		display(const std::vector<AObject*> &map) const;
  Key		getKey(void) const;
};

IDisplay	*getInstance(void);

#endif /* !SDLDISPLAY_H */
