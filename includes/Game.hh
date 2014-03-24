#ifndef GAME_HH
#define GAME_HH

#include "Nibbler.hh"
#include "AObject.hh"
#include "NibblerException.hh"
#include "Snake.hh"
#include "Wall.hh"

class   Game
{
public:
    typedef void (Game::*methodPtr)(const AObject *obj);
private:
    const Coord             _map;
    const std::string       _lib;
    std::vector<AObject*>   _objects;
public:
    Game(const Coord &map, const std::string &library);
    ~Game(void);
    Object      lookup(const Coord &coord) const;
    void        startGame(Snake &python);
    void        startMenu(void);
    void        dump(void) const;
};

#endif // GAME_HH
