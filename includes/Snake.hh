#ifndef SNAKE_HH
#define SNAKE_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"

class   Snake : public AObject
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
    const Coord     _map;
    unsigned int    _size;
    Coord           _head;
    Coord           _tail;
    Direction       _direction;

public:
    Snake(const Coord &mapSize, const Coord &start);
    ~Snake(void);
    Object     move(Object obj);
    void     setDirection(Key direction);
    void     grow(void);
    const Coord     &getNextMove(void);

public:
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    Object getType(void) const;
    void     dump(void) const;
private:
    Object verifMove(Object obj);
};

#endif // SNAKE_HH
