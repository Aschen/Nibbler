#include "Portal.hh"



Portal::Portal(const Coord &mapSize, const Couple pos)
    : AObject(PORTAL), _mapSize(mapSize)
{
    _coords.push_back(pos.first);
    _coords.push_back(pos.second);
}

const Coord Portal::getOut(const Coord &in) const
{
    Coord       out;

    if (in.first == _coords[IN].first && in.second == _coords[IN].second)
    {
        out.first = _coords[OUT].first - 1;
        out.second = _coords[OUT].second;
    }
    else
    {
        out.first = _coords[IN].first + 1;
        out.second = _coords[IN].second;
    }
    return out;
}


/////////////
// AOBJECT //
/////////////
const std::vector<Coord> &Portal::getCoord(void) const
{
    return _coords;
}

Object Portal::getType(void) const
{
    return _type;
}

void Portal::dump(void) const
{
    std::cout << "Portal in " << _coords[IN] << " and " << _coords[OUT] << std::endl;
}


/////////////
//  Error  //
/////////////
Portal::Error::Error(const Portal::Error &cpy) : NibblerException("Portal")
{
    if (&cpy != this)
    {
        _msg << cpy.getMessage();
    }
}

Portal::Error::Error(const std::string &error) : NibblerException("Portal")
{
    _msg << error << std::endl;
}

const std::string Portal::Error::getMessage(void) const
{
    return _msg.str();
}


