#ifndef GAME_HH
#define GAME_HH

#include "Nibbler.hh"
#include "IDisplay.hh"
#include "DLLoader.hh"
#include "AObject.hh"
#include "NibblerException.hh"
#include "Snake.hh"
#include "Wall.hh"
#include "Fruit.hh"

class   Game
{
public:
    typedef void (Game::*methodPtr)(const AObject *obj);
private:
    const Coord             _map;
    DLLoader<IDisplay, IDisplay*(*)()>        _dyn;
    IDisplay                *_display;
    std::vector<AObject*>   _objects;
    unsigned int            _flag;
public:
    Game(const Coord &map, const std::string &library);
    ~Game(void);
    Object      lookup(const Coord &coord) const;
    void        startGame(Snake &python, Fruit &powerup);
    void        startMenu(void);
    void        dumpObjects(void) const;
    AObject *getSnake(void) const;
    unsigned int    getFlag(void) const;
    void        setFlag(unsigned int flag);
    IDisplay    *getDisplay(void) const;
};

void        *hookKeys(void *data);
#endif // GAME_HH
