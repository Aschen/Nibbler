#ifndef NIBBLER_HH
#define NIBBLER_HH

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define	SBLOCK	40

typedef std::pair<unsigned int, unsigned int>   Coord;

typedef enum e_key
{
    UP = 1,
    DOWN = -1,
    LEFT = 2,
    RIGHT = -2,
    QUIT = 3,
    OTHERS = 4
}            Key;
typedef enum e_object
{
    WALL = 0,
    SNAKE,
    POWERUP,
    EMPTY
}            Object;
typedef enum e_direct
{
    MUP = 0,
    MDOWN,
    MLEFT,
    MRIGHT
}            Direction;
typedef enum e_flag
{
    EXIT = 0,
    MENU,
    PLAY
}            Flag;

std::ostream    &operator<<(std::ostream &os, const Coord &coord);
std::ostream    &operator<<(std::ostream &os, Key key);

#endif // NIBBLER_HH
