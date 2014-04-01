#include "IDisplay.hh"
#include "Game.hh"
#include "Snake.hh"


int     main(int ac, char **av)
{
  if (ac == 2)
    {
      try
	{
	  Game        nibbler(Coord(15, 15), av[1]);
	  nibbler.startMenu();
        }
      catch (const NibblerException &e)
        {
	  std::cerr << e.getMessage() << std::endl;
	  return -1;
        }
    }
  else
    std::cout << "Usage : " << av[0] << " <library> " << std::endl;
  return 0;
}
