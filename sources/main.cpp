#include "IDisplay.hh"
#include "Game.hh"
#include "Snake.hh"


int     main(int ac, char **av)
{
    if (ac == 2)
    {
        try
        {
//            Game        nibbler(Coord(15, 15), av[1]);

//            nibbler.startMenu();

            DLLoader<IDisplay, IDisplay*(*)()>  dyn(av[1]);
            IDisplay                            *display;
            std::vector<AObject*>   objs;

            display = dyn.getInstance("getDisplay");
            display->init(20, 20);
            display->display(objs);
            delete display;
        }
        catch (const NibblerException &e)
        {
            std::cerr << e.getMessage() << std::endl;
        }
    }
    else
        std::cout << "Usage : " << av[0] << " <library> " << std::endl;
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
