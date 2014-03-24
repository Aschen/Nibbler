#include "Fruit.hh"


Fruit::Fruit(const Coord &mapSize) : AObject(POWERUP), _mapSize(mapSize)
{
}

Fruit::~Fruit(void)
{
}

void Fruit::addFruit(const Coord &coord)
{
}

void Fruit::getNextFruit(void)
{
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

