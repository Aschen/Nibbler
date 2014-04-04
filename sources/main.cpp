#include "IDisplay.hh"
#include "Game.hh"
#include "Snake.hh"

template <typename T>
T StringToNumber (const std::string &Text)
{
  std::istringstream ss(Text);
  T result;
  return (ss >> result ? result : 0);
}

int			main(int ac, char **av)
{
  int			sx, sy;

  if (ac == 4)
    {
      sx = StringToNumber<int>(av[1]);
      sy = StringToNumber<int>(av[2]);
      try
	{
	  Game        nibbler(Coord(sx, sy),
			      av[3]);
	  nibbler.startMenu();
        }
      catch (const NibblerException &e)
        {
	  std::cerr << e.getMessage() << std::endl;
	  return -1;
        }
    }
  else
    std::cout << "Usage : " << av[0] << " X Y <library> " << std::endl;
  return 0;
}
