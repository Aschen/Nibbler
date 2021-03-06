#ifndef WALL_HH
#define WALL_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"

class   Wall : public AObject
{
public:
    class   Error : public NibblerException
    {
    private:
        std::stringstream   _msg;
    public:
        Error(const Coord &wall, const Coord &map);
        Error(const Error &cpy);
        ~Error(void) throw() {}
        const std::string   getMessage(void) const;
    };
private:
    const Coord     _mapSize;
public:
    Wall(const Coord &mapSize);
    ~Wall(void);
    void    addWall(const Coord &coord);
public:
    //AObject
    void     dump(void) const;
    const std::vector<Coord>    &getCoord(void) const;
    Object getType(void) const;


};

#endif // WALL_HH
