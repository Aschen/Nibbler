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
        Coord
    public:
        Error(const std::string &error);
        ~Error(void) throw {}
        const std::string   &getMessage(void) const;
    };

private:
    unsigned int    _size;
public:
    Snake(Coord mapSize);
    ~Snake(void);
    void     moveUp(char **map);
    void     moveRight(char **map);
    void     moveLeft(char **map);
    // AObject
    const std::vector<Coord>    &getCoord(void) const;
    const Object                getType(void) const;
};

#endif // SNAKE_HH
