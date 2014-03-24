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
