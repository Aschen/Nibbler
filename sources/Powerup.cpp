#include "Powerup.hh"


Powerup::Powerup(const Coord &mapSize)
    : AObject(POWERUP), _mapSize(mapSize), _full(0)
{
}

Powerup::~Powerup(void)
{
}

int Powerup::addPowerup(Object obj)
{
    if (obj != EMPTY)
        return 1;
    _coords.push_back(_next);
    _full = 0;
    return 0;
}

Coord &Powerup::getNextPowerup(void)
{
    if (++_full > _mapSize.first * _mapSize.second)
        throw Error("Can't place powerup");
    _next.first = rand() % _mapSize.first;
    _next.second = rand() % _mapSize.second;
    return _next;
}

void Powerup::clearPowerup(void)
{
    _coords.clear();
}

//////////////
// AObject  //
//////////////
const std::vector<Coord> &Powerup::getCoord(void) const
{
    return _coords;
}

Object Powerup::getType(void) const
{
    return _type;
}

void Powerup::dump(void) const
{
    std::cout << "Powerup in " << _coords.begin()->first << "," << _coords.begin()->second << std::endl;
}

/////////////
//  Error  //
/////////////
Powerup::Error::Error(const Powerup::Error &cpy) : NibblerException("Powerup")
{
    if (&cpy != this)
    {
        _msg << cpy.getMessage();
    }
}

Powerup::Error::Error(const std::string &error) : NibblerException("Powerup")
{
    _msg << error << std::endl;
}

const std::string Powerup::Error::getMessage(void) const
{
    return _msg.str();
}

