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
    return result;
}

void *hookKeys(void *data)
{
    Snake   *python = NULL;
    Game    *nibbler = NULL;
    Key     key;

    nibbler = reinterpret_cast<Game*>(data);
    python = reinterpret_cast<Snake*>(nibbler->getSnake());
    while (nibbler->getFlag())
    {
        key = nibbler->getDisplay()->getKey();
        if (key == QUIT)
            nibbler->setFlag(0);
        if (key <= RIGHT)
            python->setDirection(key);
    }
    pthread_exit(0);
}

void Game::startGame(Snake &python, Fruit &powerup)
{
    Key key;
    pthread_t   keyThread;
    _flag = 1;

    pthread_create(&keyThread, NULL, &hookKeys, this);
    while (_flag)
    {
        try
        {
            if (python.move(this->lookup(python.getNextMove())) == POWERUP)
                while (powerup.addFruit(this->lookup(powerup.getNextFruit())));
            this->dumpObjects();
            _display->display(_objects);
            usleep(500000);
        }
        catch (const Snake::Error &e)
        {
            std::cout << "startGame() : " << e.getMessage() << std::endl;
            pthread_kill(keyThread, SIGKILL);
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

AObject *Game::getSnake(void) const
{
    return _objects[0];
}

unsigned int Game::getFlag() const
{
    return _flag;
}

void Game::setFlag(unsigned int flag)
{
    _flag = flag;
}

IDisplay *Game::getDisplay() const
{
    return _display;
}
