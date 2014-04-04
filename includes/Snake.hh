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
    private:
        std::stringstream   _msg;
    public:
        Error(const Coord &start, const Coord &map);
        Error(const Coord &start, const Coord &map, int size);
        Error(const Error &cpy);
        ~Error(void) throw() {}
        const std::string   getMessage(void) const;
    };

private:
    const Coord     _map;
    unsigned int    _size;
    Coord           _head;
    Coord           _tail;

public:
    Snake(const Coord &mapSize, const Coord &start);
    ~Snake(void);
    void            move(void);
    void            grow(void);
    const Coord     &getNextMove(Key direction);
    const Coord     &getNextMove(const Coord &next);
    const Coord     &getHead(void) const;
    unsigned int    getSize(void) const;
public:
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    Object                      getType(void) const;
    void                        dump(void) const;
};

#endif // SNAKE_HH
