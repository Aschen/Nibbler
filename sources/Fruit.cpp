#include "Fruit.hh"


Fruit::Fruit(const Coord &mapSize) : AObject(POWERUP), _mapSize(mapSize)
{
}

Fruit::~Fruit(void)
{
}

int Fruit::addFruit(Object obj)
{
    if (obj != EMPTY)
        return 1;
    _coords.clear();
    _coords.push_back(_next);
    _full = 0;
    return 0;
}

Coord Fruit::getNextFruit(void)
{
    if (++_full > _mapSize.first * _mapSize.second)
        throw Error("Can't place a powerup");
    _next.first = rand() % _mapSize.first;
    _next.second = rand() % _mapSize.second;
    return _next;
}

//////////////
// AObject  //
//////////////
const std::vector<Coord> &Fruit::getCoord(void) const
{
    return _coords;
}

Object Fruit::getType(void) const
{
    return _type;
}

void Fruit::dump(void) const
{
    std::cout << "Fruit in " << _coords.begin()->first << "," << _coords.begin()->second << std::endl;
}

/////////////
//  Error  //
/////////////
Fruit::Error::Error(const std::string &error) : NibblerException(error)
{
}

const std::string Fruit::Error::getMessage(void) const
{
    std::stringstream   ss;

    ss << "Fruit : " << this->getError();
    return ss.str();
}

