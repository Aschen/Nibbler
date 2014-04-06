#include "Snake.hh"

Snake::Snake(const Coord &mapSize, const Coord &start)
    : AObject(SNAKE), _map(mapSize), _size(4)
{
    unsigned int     i = 0;

    if (start.first > mapSize.first - 1 || start.second > mapSize.second - 1)
        throw Error(start, _map);
    while (i < _size)
    {
        if (start.second + i <= mapSize.second - 1)
            _coords.push_back(Coord(start.first, start.second + i));
        else
            throw Error(start, _map, _size);
        ++i;
    }
    _tail = *(--(_coords.end()));
}

Snake::~Snake(void)
{
}

void Snake::move(void)
{
    std::vector<Coord>::iterator    it = _coords.begin();
    Coord                           tmp;
    Coord                           last;

    last = *it;
    _tail = *(--(_coords.end()));
    while (it != _coords.end())
    {
        tmp = *it;
        *it = last;
        last = tmp;
        ++it;
    }
    *(_coords.begin()) = _head;
}

void Snake::grow(void)
{
    _coords.push_back(Coord(_tail.first, _tail.second));
}

const Coord &Snake::getNextMove(const Coord &next)
{
    _head = next;
    return _head;
}

const Coord &Snake::getHead() const
{
    return _head;
}

unsigned int Snake::getSize() const
{
    return _size;
}

const Coord &Snake::getNextMove(Key direction)
{
    _head = *(_coords.begin());
    switch (direction)
    {
    case UP:
        _head.second -= 1;
        break;
    case DOWN:
        _head.second += 1;
        break;
    case LEFT:
        _head.first -= 1;
        break;
    case RIGHT:
        _head.first += 1;
        break;
    default:
        break;
    }
    return _head;
}

void Snake::dump(void) const
{
    std::vector<Coord>::const_iterator    it = _coords.begin();

    while (it != _coords.end())
    {
        std::cout << "[" << it->first << "," << it->second << "]";
        if (it == _coords.begin())
            std::cout << "    <= HEAD";
        std::cout << std::endl;
        ++it;
    }
    std::cout << std::endl;
}

////////////////
//  AObject   //
////////////////
const std::vector<Coord> &Snake::getCoord() const
{
    return _coords;
}

Object Snake::getType() const
{
    return _type;
}

///////////
// Error //
///////////
Snake::Error::Error(const Coord &start, const Coord &map) : NibblerException("Snake")
{
    _msg << this->_module << "Start point " << start;
    _msg << " is outside the map ! " << map << std::endl;
}

Snake::Error::Error(const Coord &start, const Coord &map, int size) : NibblerException("Snake")
{
    _msg << this->_module << "Size of snake (" << size << ") is too big with this start point !";
    _msg << start << " for the map of size " << map << std::endl;
}

Snake::Error::Error(const Error &cpy) : NibblerException("Snake")
{
    if (&cpy != this)
    {
        _msg << cpy.getMessage();
    }
}

const std::string Snake::Error::getMessage(void) const
{
    return _msg.str();
}
