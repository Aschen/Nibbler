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
    {
        std::cout << "Invalid new Powerup position" << std::endl;
        return 1;
    }
    std::cout << "Add Powerup in " << _next.first << "," << _next.second << std::endl;
    _coords.push_back(_next);
    _full = 0;
    std::cout << "New Powerup successfully added ! " << std::endl;
    return 0;
}

Coord &Powerup::getNextPowerup(void)
{
    std::cout << "Find a new Powerup position" << std::endl;
    if (++_full > _mapSize.first * _mapSize.second)
        throw Error("Can't place a powerup");
    _next.first = rand() % _mapSize.first;
    _next.second = rand() % _mapSize.second;
    std::cout << "New Powerup position finded ! " << _next.first << "," << _next.second << std::endl;
    return _next;
}

void Powerup::clearPowerup(void)
{
    std::cout << "Remove old Powerup" << std::endl;
    _coords.clear();
    std::cout << "Old Powerup deleted !" << std::endl;
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
Powerup::Error::Error(const std::string &error) : NibblerException(error)
{
}

const std::string Powerup::Error::getMessage(void) const
{
    std::stringstream   ss;

    ss << "Powerup : " << this->getError();
    return ss.str();
}

