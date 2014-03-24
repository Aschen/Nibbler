#include "Game.hh"

Game::Game(const Coord &map, const std::string &library)
    : _map(map), _dyn(DLLoader<IDisplay, IDisplay*(*)()>(library))
{
    _display = _dyn.getInstance("getDisplay");
}

Game::~Game(void)
{
    delete _display;
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
    int flag = 1;

    while (flag)
    {
        try
        {
            python.move(this->lookup(python.getNextMove()));
            python.dump();            
            _display->display(_objects);
            sleep(1);
            flag = _display->getKey() == QUIT ? 0 : 1;
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
    Snake       python(_map, Coord(_map.first/2, _map.second/2));
    Wall        walls(_map);

    _objects.erase(_objects.begin(), _objects.end());
    _objects.push_back(&python);
    _objects.push_back(&walls);
    _display->init(10, 10);
    std::cout << std::endl << "Bienvenu sur le Menu !" << std::endl;
    this->dump();
    sleep(2);
    std::cout << "Demarrage de la partie :D" << std::endl;
    this->startGame(python);
    std::cout << "FIN" << std::endl;
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
