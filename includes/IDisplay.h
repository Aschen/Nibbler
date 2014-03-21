#ifndef IDISPLAY_H
#define IDISPLAY_H

class   IDisplay
{
    virtual ~IDisplay(void) {}
    virtual displayMap(char **map) = 0;
    virtual getKeys(void) = 0;
};

#endif // IDISPLAY_H
