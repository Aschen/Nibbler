#ifndef NIBBLER_HH
#define NIBBLER_HH

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unistd.h>

#define MUP(c)     -1
#define MDOWN(c)   1
#define MLEFT(c)   -1
#define MRIGHT(c)  1

typedef std::pair<unsigned int, unsigned int>   Coord;
typedef enum e_key
{
    ESC = 0,
    LEFT,
    RIGHT
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

#endif // NIBBLER_HH
