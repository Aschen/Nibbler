#ifndef OPENGLDISPLAY_HH
#define OPENGLDISPLAY_HH

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "NibblerException.hh"
#include "DLLoader.hh"
#include "AObject.hh"
#include "IDisplay.hh"

# define _PI    3.1415926
# define FOVY   90.0
# define NEAR   1.0
# define FAR    1000.0
# define CAMX   50
# define CAMY   50
# define CAMZ   50
# define TARGX  50
# define TARGY  50
# define TARGZ  50
# define VERTX  50
# define VERTY  50
# define VERTZ  50

typedef struct  s_coo3  Coo3;
struct  s_coo3
{
    GLdouble      x;
    GLdouble      y;
    GLdouble      z;
};

typedef unsigned char   GLubyte;
typedef struct  s_color Color;
struct  s_color
{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
};

class   OpenGLDisplay : public IDisplay
{
private:
   Coord          _map;
public:
    OpenGLDisplay(void);
    ~OpenGLDisplay(void);
private:
    void    drawCube(Coo3 coord, Color col) const;
    void    drawFloor() const;
    void    reset(void) const;
    void    refresh(void) const;
    void    setView(Coo3 eye, Coo3 center, Coo3 vert) const;
    Coo3    getCoo(GLdouble x, GLdouble y, GLdouble z) const;
    Color   getCol(GLubyte red, GLubyte green, GLubyte blue) const;

// IDisplay Interface
public:
    void    init(int width, int height);
    void    display(const std::vector<AObject*> &map) const;
    Key     getKey(void) const;
};

#endif // OPENGLDISPLAY_HH
