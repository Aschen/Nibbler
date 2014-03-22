//
// main.cpp for - in /home/brunne_r/Links/nibbler/sources
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Sat Mar 22 16:00:07 2014 brunne-r
// Last update Sat Mar 22 16:44:39 2014 brunne-r
//

#include <iostream>
#include <cstdlib>
#include "Nibbler.hh"
#include "DLLoader.hh"
#include "IDisplay.hh"

int		main(void)
{
  DLLoader<IDisplay, IDisplay*(*)()>	Dyn("./sdllib/libsdl.so");
  IDisplay	*Display;

  try
    {
      Display = Dyn.getInstance("getDisplay");
      Display->init(500,500);
      while (Display->getKey() != QUIT)
	{
	  usleep(200);
	}
    }
  catch (...)
    {
      std::cerr << "Error" << std::endl;
    }
  return 0;
}
