//
// IDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:54:29 2014 brunne-r
// Last update Fri Mar 21 16:57:01 2014 brunne-r
//

#ifndef IDISPLAY_H
#define IDISPLAY_H

# include <vector>
# include "AObject.hh"

typedef enum	eKey
  {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    OTHERS
  }		Key;

class		IDisplay
{
public:
  virtual	~IDisplay() {}
  virtual void	display(const std::vector<AObject*> &map) const = 0;
  virtual Key	getKey(void) const = 0;
};

#endif // IDISPLAY_H
