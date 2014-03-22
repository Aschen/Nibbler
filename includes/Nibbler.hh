#ifndef NIBBLER_HH
#define NIBBLER_HH

#define	SBLOCK	40

#include <string>
#include <vector>
#include <stdexcept>

typedef std::pair<unsigned int, unsigned int>   Coord;
typedef enum e_key
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    OTHERS
}            Key;
typedef enum e_object
{
    WALL = 0,
    SNAKE,
    POWERUP
}            Object;

#endif // NIBBLER_HH
