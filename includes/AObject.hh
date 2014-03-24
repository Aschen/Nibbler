#ifndef AOBJECT_HH
#define AOBJECT_HH

#include "Nibbler.hh"

class   AObject
{
protected:
    std::vector<Coord>  _coords;
    const Object        _type;
public:
    AObject(const Object type) : _type(type) {}
    virtual ~AObject(void) {}
    virtual const std::vector<Coord>  &getCoord(void) const = 0;
    virtual Object              getType(void) const = 0;
    virtual void                dump(void) const = 0;
};

#endif // AOBJECT_HH
