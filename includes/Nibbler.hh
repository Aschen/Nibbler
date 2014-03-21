#ifndef NIBBLER_HH
#define NIBBLER_HH

#include <string>
#include <vector>
#include <stdexcept>

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
    POWERUP
}            Object;

#endif // NIBBLER_HH
