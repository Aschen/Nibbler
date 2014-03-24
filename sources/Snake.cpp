#include "Snake.hh"

Snake::Snake(const Coord &mapSize, const Coord &start)
    : AObject(SNAKE), _map(mapSize), _size(4), _direction(MUP)
{
    unsigned int     i = 0;

    if (start.first > mapSize.first || start.second > mapSize.second)
        throw Error("Start point is outside the map !");
    while (i < _size)
    {
        if (start.second + i <= mapSize.second)
            _coords.push_back(Coord(start.first, start.second + i));
        else
            throw Error("Size of snake is too big with this start point !");
        ++i;
    }
    _tail = *(--(_coords.end()));
}

Snake::~Snake()
{
}

void Snake::move(Object obj)
{
    std::vector<Coord>::iterator    it = _coords.begin();
    Coord       tmp;
    Coord       last;

    this->verifMove(obj);
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

const Coord &Snake::getNextMove(void)
{
    _head = *(_coords.begin());
    switch (_direction)
    {
    case MUP:
        _head.second -= 1;
        break;
    case MDOWN:
        _head.second += 1;
        break;
    case MLEFT:
        _head.first -= 1;
        break;
    case MRIGHT:
        _head.first += 1;
        break;
    }
    std::cout << "Next move in " << _head.first << "," << _head.second << std::endl;
    return _head;
}

void Snake::setDirection(Direction direction)
{
    _direction = direction;
}

void Snake::verifMove(Object obj)
{
    switch (obj)
    {
    case SNAKE:
    case WALL:
        throw Error("Game over !");
        break;
    case POWERUP:
        this->grow();
        break;
    case EMPTY:
        std::cout << "Move is ok" << std::endl;
        break;
    }
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
Snake::Error::Error(const std::string &error) : NibblerException(error)
{
}

const std::string Snake::Error::getMessage(void) const
{
    std::stringstream   ss;

    ss << "Snake : " << this->getError();
    return ss.str();
}
