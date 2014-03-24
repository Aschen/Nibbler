#include "Game.hh"

Game::Game(const Coord &map, const std::string &library)
    : _map(map), _lib(library)
{
}

Game::~Game(void)
{
}

Object Game::lookup(const Coord &search) const
{
    std::vector<AObject*>::const_iterator     it = _objects.begin();
    Object      result = EMPTY;

    while (it != _objects.end())
    {
        if (find((*it)->getCoord().begin(), (*it)->getCoord().end(), search) != (*it)->getCoord().end())
           result = (*it)->getType();
        ++it;
    }
    std::cout << "Object in " << search.first << "," << search.second << " is " << result << std::endl;
    return result;
}

void Game::startGame(Snake &python)
{
    while (1)
    {
        try
        {
            python.move(this->lookup(python.getNextMove()));
            python.dump();            
            sleep(1);
        }
        catch (const Snake::Error &e)
        {
            std::cout << "startGame() : " << e.getMessage() << std::endl;
            this->startMenu();
        }
    }
}

void Game::startMenu(void)
{
    Snake       python(_map, Coord(25, 5));
    Wall        walls(_map);

    _objects.erase(_objects.begin(), _objects.end());
    _objects.push_back(&python);
    _objects.push_back(&walls);
    std::cout << std::endl << "Bienvenu sur le Menu !" << std::endl;
    this->dump();
    sleep(2);
    std::cout << "Demarrage de la partie :D" << std::endl;
    this->startGame(python);
}

void Game::dump(void) const
{
    std::vector<AObject*>::const_iterator   it = _objects.begin();

    while (it != _objects.end())
    {
        std::cout << "Object of type " << (*it)->getType() << std::endl;
        (*it)->dump();
        std::cout << std::endl;
        ++it;
    }
}
