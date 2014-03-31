//
// SdlDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:37:26 2014 brunne-r
// Last update Mon Mar 31 16:07:08 2014 brunne-r
//

#ifndef NCDISPLAY_H
# define NCDISPLAY_H

# include <ncurses.h>
# include "AObject.hh"
# include "DLLoader.hh"
# include "IDisplay.hh"
# include "NibblerException.hh"

class		NcursesDisplay : public IDisplay
{
  class		NcursesError : public NibblerException
  {
  private:
      std::stringstream _msg;
  public:
    NcursesError(const std::string &error);
    NcursesError(const NcursesError &cpy);
    ~NcursesError(void) throw() {}
    const std::string getMessage(void) const;
  };
private:
  WINDOW	*_win;
  char		*_chars[3];

public:
  NcursesDisplay();
  ~NcursesDisplay();
public:
  void		init(int width, int height);
  void		display(const std::vector<AObject*> &map) const;
  Key		getKey(void) const;
};

#endif /* !NCDISPLAY_H */
