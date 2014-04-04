#include "Game.hh"

Game::Game(const Coord &map, const std::string &library)
    : _map(map), _dll(DLLoader<IDisplay, IDisplay*(*)()>(library)), _flag(MENU), _direction(OTHERS)
{
    _display = _dll.getInstance("getDisplay");
    _moveType = 1;
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
    Portal      *portal;
    Object      snakeHead;

    python = dynamic_cast<Snake*>(_objects[SNAKE]);
    fruit = dynamic_cast<Powerup*>(_objects[POWERUP]);
    portal = dynamic_cast<Portal*>(_objects[PORTAL]);
    _flag = PLAY;
    while (_flag >= PLAY)
    {
        this->dumpObjects();
        if (_moveType == 1)
            snakeHead = this->lookup(python->getNextMove(_direction));
        else
        {
            snakeHead = this->lookup(python->getNextMove(portal->getOut(python->getHead())));
            _moveType = 1;
        }
        switch (snakeHead)
        {
        case PORTAL:
            _moveType = 2;
            python->move();
            _display->display(_objects);
            break;
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
        _objects.push_back(new Portal(_map, Couple(Coord(0, _map.second/2), Coord(_map.first - 1, _map.second/2))));
        fruit = dynamic_cast<Powerup*>(_objects[POWERUP]);
        while (fruit->addPowerup(this->lookup(fruit->getNextPowerup())));
        this->dumpObjects();
        _display->display(_objects);
        while (_direction == OTHERS && _flag >= MENU)
            usleep(10000);
        if (_flag >= MENU)
            this->startGame();
    }
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
    _direction = OTHERS;
    _moveType = 1;
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
    if (_direction * -1 != key)
        _direction = key;
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
        switch (key)
        {
        case QUIT:
            if (nibbler->getFlag() == PLAY)
                nibbler->setFlag(MENU);
            else
                nibbler->setFlag(EXIT);
            break;
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            nibbler->setDirection(key);
            break;
        default:
            break;
        }
    }
    pthread_exit(0);
}

std::ostream &operator<<(std::ostream &os, const Coord &coord)
{
    os << "(" << coord.first << "," << coord.second << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, Key key)
{
    switch (key)
    {
    case UP:
        os << "UP";
        break;
    case DOWN:
        os << "DOWN";
        break;
    case LEFT:
        os << "LEFT";
        break;
    case RIGHT:
        os << "RIGHT";
        break;
    case QUIT:
        os << "QUIT";
        break;
    case OTHERS:
        os << "OTHER";
        break;
    }
    return os;
}
