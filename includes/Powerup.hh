#ifndef POWERUP_HH
#define POWERUP_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"

class   Powerup : public AObject
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
    const Coord     _mapSize;
    unsigned int    _full;
    Coord           _next;
public:
    Powerup(const Coord &mapSize);
    ~Powerup(void);
    int             addPowerup(const Object obj);
    Coord           &getNextPowerup(void);
    void            clearPowerup(void);
public:
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    Object                      getType(void) const;
    void                        dump(void) const;
};

#endif // POWERUP_HH
