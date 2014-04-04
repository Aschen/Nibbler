#include "Game.hh"

Game::Game(const Coord &map, const std::string &library)
    : _map(map), _dyn(DLLoader<IDisplay, IDisplay*(*)()>(library)), _flag(MENU), _direction(MUP)
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

void Game::startGame(void)
{
    Snake       *python;
    Powerup     *fruit;
    Object      snakeHead;

    _flag = PLAY;
    python = dynamic_cast<Snake*>(_objects[SNAKE]);
    fruit = dynamic_cast<Powerup*>(_objects[POWERUP]);
    while (_flag >= PLAY)
    {
        snakeHead = this->lookup(python->getNextMove(_direction));
        switch (snakeHead)
        {
        case WALL:
        case SNAKE:
            _flag = MENU;
            break;
        case POWERUP:
            python->grow();
            fruit->clearPowerup();
            while (fruit->addPowerup(this->lookup(fruit->getNextPowerup())));
        case EMPTY:
            python->move();
            _display->display(_objects);
        }
        usleep(99000);
    }
}

void Game::startMenu(void)
{
    pthread_t   keyThread;
    Powerup     *fruit;

    _display->init(_map.first, _map.second);
    pthread_create(&keyThread, NULL, &hookKeys, this);
    while (_flag >= MENU)
    {
        this->clearGame();
        _objects.push_back(new Wall(_map));
        _objects.push_back(new Snake(_map, Coord(_map.first/2, _map.second/2)));
        _objects.push_back(new Powerup(_map));
        fruit = dynamic_cast<Powerup*>(_objects[POWERUP]);
        while (fruit->addPowerup(this->lookup(fruit->getNextPowerup())));
        _display->display(_objects);
        sleep(1);
        this->startGame();
    }
    pthread_kill(keyThread, SIGKILL);
}

void Game::clearGame(void)
{
    std::vector<AObject*>::iterator it = _objects.begin();

    while (it != _objects.end())
    {
        delete *it;
        ++it;
    }
    _objects.clear();
    _direction = MUP;
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

/////////////
// GET-SET //
/////////////
AObject *Game::getObject(Object type) const
{
    return _objects[type];
}

Flag Game::getFlag() const
{
    return _flag;
}

void Game::setFlag(Flag flag)
{
    _flag = flag;
}

void Game::setDirection(Key key)
{
    _direction = static_cast<Direction>(key);
}

IDisplay *Game::getDisplay() const
{
    return _display;
}

////////////
// EXTERN //
////////////
void *hookKeys(void *data)
{
    Game    *nibbler = NULL;
    Key     key;

    if ((nibbler = reinterpret_cast<Game*>(data)) == NULL)
        std::cerr << "La c'est la merde !" << std::endl;
    while (nibbler->getFlag() >= MENU)
    {
        key = nibbler->getDisplay()->getKey();
        if (key == QUIT)
        {
            nibbler->setFlag(EXIT);
	    // std::cout << "Key EXIT pressed" << std::endl;
            break;
        }
        if (key <= RIGHT && nibbler->getFlag() == PLAY)
        {
	  //std::cout << "Key " << key << " pressed" << std::endl;
            nibbler->setDirection(key);
        }
    }
    pthread_exit(0);
}

std::ostream &operator<<(std::ostream &os, const Coord &coord)
{
    os << "(" << coord.first << "," << coord.second << ")";
    return os;
}
