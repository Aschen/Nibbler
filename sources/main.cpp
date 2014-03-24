#include "Game.hh"
#include "Snake.hh"


int     main(int ac, char **av)
{
    try
    {
        Game        nibbler(Coord(50, 50), "lib_nibbler_sdl.so");

        nibbler.startMenu();
    }
    catch (const NibblerException &e)
    {
        std::cerr << e.getMessage() << std::endl;
    }

    return 0;
}
