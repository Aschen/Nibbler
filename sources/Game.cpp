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

void Game::startGame(Snake &python, Fruit &powerup)
{
    int flag = 1;
    Key key;

    while (flag)
    {
        try
        {
            if (python.move(this->lookup(python.getNextMove())) == POWERUP)
                while (powerup.addFruit(this->lookup(powerup.getNextFruit())));
            python.dump();            
            _display->display(_objects);
            sleep(1);
            if ((key = _display->getKey()) == QUIT)
                flag = 0;
            if (key <= RIGHT)
                python.setDirection(key);
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
    Fruit       powerup(_map);

    _objects.clear();
    _objects.push_back(&python);
    _objects.push_back(&walls);
    _objects.push_back(&powerup);
    while (powerup.addFruit(this->lookup(powerup.getNextFruit())));
    _display->init(_map.first, _map.second);
    std::cout << std::endl << "Bienvenu sur le Menu !" << std::endl;
    this->dumpObjects();
    sleep(2);
    std::cout << "Demarrage de la partie :D" << std::endl;
    this->startGame(python, powerup);
    std::cout << "FIN" << std::endl;
}

void Game::dumpObjects(void) const
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
