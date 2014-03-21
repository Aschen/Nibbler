#ifndef SNAKE_HH
#define SNAKE_HH

#include <string>
#include <vector>

typedef Coord std::pair<unsigned int, unsigned int>;

class   Snake
{
private:
    std::vector<Coord>    _corpse;
public:
    Snake(char **map, Coord size);
    ~Snake(void);
    void     moveUp(char **map);
    void     moveRight(char **map);
    void     moveLeft(char **map);
};

#endif // SNAKE_HH
