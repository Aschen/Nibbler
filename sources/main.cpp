//
// main.cpp for - in /home/brunne_r/Links/nibbler/sources
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Sat Mar 22 16:00:07 2014 brunne-r
// Last update Mon Mar 24 13:31:22 2014 brunne-r
//

#include <iostream>
#include <cstdlib>
#include "Nibbler.hh"
#include "NibblerException.hh"
#include "DLLoader.hh"
#include "IDisplay.hh"

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
	  usleep(200000);
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
