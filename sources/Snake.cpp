#include "Snake.hh"

Snake::Snake(Coord mapSize, Coord start) : _size(4)
{
    unsigned int     i = 0;

    if (start.first > mapSize.first || start.second > mapSize.second)
        throw Error("Start point is outside the map !");
    while (i < _size)
    {
        if (start.second + i++ <= mapSize.second)
            _coords.push_back(Coord(start.first, start.second + i - 1));
        else
            throw Error("Size of snake is too big with this start point !");
    }
}

Snake::~Snake()
{
}

const std::vector &Snake::getCoord() const
{
}

const Object Snake::getType() const
{
}



// Error
Snake::Error::Error(const std::string &error) : NibblerException(error)
{
}

const std::string   &Snake::Error::getMessage(void) const
{


}
