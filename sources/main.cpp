#include "IDisplay.hh"
#include "Game.hh"
#include "Snake.hh"


int     main(int ac, char **av)
{
    try
    {
        Game        nibbler(Coord(50, 50), "/sdllib/libsdl.so");

        nibbler.startMenu();
    }
    catch (const NibblerException &e)
    {
        std::cerr << e.getMessage() << std::endl;
    }

    return 0;
}
/*
int		main(int ac , char **av)
{
  if (ac >= 2)
    {
      DLLoader<IDisplay, IDisplay*(*)()>	Dyn(av[1]);
      IDisplay	*Display;

      try
	{
	  Display = Dyn.getInstance("getDisplay");
	  Display->init(10,10);
	  while (Display->getKey() != QUIT)
	    {
	      usleep(200);
	    }
	}
      catch (NibblerException &e)
	{
	  std::cerr << "Error:" << e.getMessage() << std::endl;
	}
    }
  return 0;
}
*/
