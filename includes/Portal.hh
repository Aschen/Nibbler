#ifndef PORTAL_HH
#define PORTAL_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"

class Portal : public AObject
{
public:
    class   Error : public NibblerException
    {
    private:
        std::stringstream   _msg;
    public:
        Error(const Error &cpy);
        Error(const std::string &error);
        ~Error(void) throw() {}
        const std::string   getMessage(void) const;
    };
private:
    const Coord         _mapSize;
public:
    Portal(const Coord &mapSize, const Couple pos);
    ~Portal(void) {}
    const Coord getOut(const Coord &in) const;
public:
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    Object                      getType(void) const;
    void                        dump(void) const;

};

#endif // PORTAL_HH
