//
// IDisplay.hh for - in /home/brunne_r/Links/nibbler/includes
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Fri Mar 21 16:54:29 2014 brunne-r
// Last update Sat Mar 22 15:50:28 2014 brunne-r
//

#ifndef IDISPLAY_H
#define IDISPLAY_H

# include <vector>
# include "Nibbler.hh"
# include "AObject.hh"

class		IDisplay
{
public:
  virtual	~IDisplay() {}
  virtual void	init(int width, int height) = 0;
  virtual void	display(const std::vector<AObject*> &map) const = 0;
  virtual Key	getKey(void) const = 0;
};

#endif // IDISPLAY_H
