#ifndef AOBJECT_HH
#define AOBJECT_HH

#include "Nibbler.hh"

class   AObject
{
protected:
    std::vector<Coord>  _coords;
public:
    virtual ~AObject(void) {}
    virtual const std::vector<Coord>  &getCoord(void) const = 0;
    virtual const Object              getType(void) const = 0;
};

#endif // AOBJECT_HH
