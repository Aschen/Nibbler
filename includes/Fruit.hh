#ifndef FRUIT_HH
#define FRUIT_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"

class   Fruit : public AObject
{
public:
    class   Error : public NibblerException
    {
    public:
        Error(const std::string &error);
        ~Error(void) throw() {}
        const std::string   getMessage(void) const;
    };
private:
    const Coord     _mapSize;
public:
    Fruit(const Coord &mapSize);
    ~Fruit(void);
    void    addFruit(const Coord &coord);
    void    getNextFruit(void);
public:
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    Object getType(void) const;
    void     dump(void) const;
};

#endif // FRUIT_HH
