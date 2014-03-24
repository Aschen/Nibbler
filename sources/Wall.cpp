#include "Wall.hh"


Wall::Wall(const Coord &mapSize) : AObject(WALL), _mapSize(mapSize)
{
    unsigned int    i;

    // Init avec functor ?
    for (i = 0; i < mapSize.first; i++)
        _coords.push_back(Coord(i, 0));
    for (i = 0; i < mapSize.first; i++)
        _coords.push_back(Coord(i, mapSize.second - 1));
    for (i = 0; i < mapSize.second; i++)
        _coords.push_back(Coord(0, i));
    for (i = 0; i < mapSize.second; i++)
        _coords.push_back(Coord(mapSize.first - 1, i));
}

Wall::~Wall(void)
{
}

void Wall::addWall(const Coord &coord)
{
    if (coord.first > _mapSize.first || coord.second > _mapSize.second)
        throw Error("Wall is outside the map");
    _coords.push_back(coord);
}

void Wall::dump(void) const
{
    std::vector<Coord>::const_iterator   it = _coords.begin();

    std::cout << "Walls" << std::endl;
    while (it != _coords.end())
    {
        std::cout << "[" << it->first << "," << it->second << "]" << std::endl;
        ++it;
    }
}

////////////////
//  AObject   //
////////////////
const std::vector<Coord> &Wall::getCoord(void) const
{
    return _coords;
}

Object Wall::getType(void) const
{
    return _type;
}


///////////
// Error //
///////////
Wall::Error::Error(const std::string &error) : NibblerException(error)
{
}

const std::string Wall::Error::getMessage() const
{
    std::stringstream   ss;

    ss << "Wall : " << this->getError();
    return ss.str();
}
