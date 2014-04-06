#ifndef GAME_HH
#define GAME_HH

#include "Nibbler.hh"
#include "IDisplay.hh"
#include "DLLoader.hh"
#include "AObject.hh"
#include "NibblerException.hh"
#include "Snake.hh"
#include "Wall.hh"
#include "Powerup.hh"
#include "Portal.hh"

class   Game
{
public:
    typedef enum    e_speed
    {
        NORMAL = 150000,
        BOOST = 99000
    }               Speed;
public:
    typedef void (Game::*methodPtr)(const AObject *obj);
private:
    const Coord             _map;
    DLLoader<IDisplay, IDisplay*(*)()>        _dll;
    Flag                    _flag;
    Key                     _direction;
    IDisplay                *_display;
    std::vector<AObject*>   _objects;
    int                     _moveType;
    unsigned int            _speed;
public:
    Game(const Coord &map, const std::string &library);
    ~Game(void);
    Object      lookup(const Coord &coord) const;
    void        startGame(void);
    void        startMenu(void);
    void        dumpObjects(void) const;
    void        clearGame(void);
//GETTER SETTER
public:
    AObject         *getObject(Object type) const;
    Flag            getFlag(void) const;
    IDisplay        *getDisplay(void) const;
    void            setFlag(Flag flag);
    void            setDirection(Key key);
    void            switchBoost(void);
};

void        *hookKeys(void *data);
#endif // GAME_HH
