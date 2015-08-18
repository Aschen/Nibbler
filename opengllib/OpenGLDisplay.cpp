#include "OpenGLDisplay.hh"

OpenGLDisplay::OpenGLDisplay(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
      throw std::runtime_error(SDL_GetError());
}

OpenGLDisplay::~OpenGLDisplay(void)
{
    SDL_Quit();
}

void OpenGLDisplay::reset(void) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLDisplay::refresh(void) const
{
    glFlush();
    SDL_GL_SwapBuffers();
}

void OpenGLDisplay::setView(Coo3 eye, Coo3 center, Coo3 vert) const
{
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, vert.x, vert.y, vert.z);
}



void OpenGLDisplay::drawCube(Coo3 coord, Color col) const
{
    glBegin(GL_QUADS);

    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x, coord.y, coord.z);
    glVertex3d(coord.x + 1, coord.y, coord.z);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x + 1, coord.y, coord.z + 1);
    glVertex3d(coord.x, coord.y, coord.z + 1);

    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x + 1, coord.y, coord.z);
    glVertex3d(coord.x + 1, coord.y + 1, coord.z);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x + 1, coord.y + 1, coord.z + 1);
    glVertex3d(coord.x + 1, coord.y, coord.z + 1);

    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x + 1, coord.y + 1, coord.z);
    glVertex3d(coord.x, coord.y + 1, coord.z);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x, coord.y + 1, coord.z + 1);
    glVertex3d(coord.x + 1, coord.y + 1, coord.z + 1);

    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x, coord.y + 1, coord.z);
    glVertex3d(coord.x, coord.y, coord.z);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x, coord.y, coord.z + 1);
    glVertex3d(coord.x, coord.y + 1, coord.z + 1);

    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x, coord.y, coord.z + 1);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x + 1, coord.y, coord.z + 1);
    glColor3ub(col.red, col.green, col.blue);
    glVertex3d(coord.x + 1, coord.y + 1, coord.z + 1);
    glColor3ub(0, 0, 0);
    glVertex3d(coord.x, coord.y + 1, coord.z + 1);

    glEnd();
}

void OpenGLDisplay::drawFloor() const
{
    glBegin(GL_QUADS);

    glColor3ub(255, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(_map.first, 0, 0);
    glColor3ub(50, 50, 50);
    glVertex3d(_map.first, _map.second, 0);
    glVertex3d(0, _map.second, 0);

    glEnd();
}

Coo3    OpenGLDisplay::getCoo(GLdouble x, GLdouble y, GLdouble z) const
{
    Coo3    c;

    c.x = x;
    c.y = y;
    c.z = z;
    return c;
}

Color   OpenGLDisplay::getCol(GLubyte red, GLubyte green, GLubyte blue) const
{
    Color   c;

    c.red = red;
    c.green = green;
    c.blue = blue;
    return c;
}

//////////////
// IDISPLAY //
//////////////
void OpenGLDisplay::init(int width, int height)
{
    if (width * SBLOCK > 1920 || height * SBLOCK > 1080)
      throw std::runtime_error("The size of the map is too big");
    else if (width < 10 || height < 10)
      throw std::runtime_error("The size of the map is too small");
    SDL_WM_SetCaption("Nibbler", NULL);
    SDL_SetVideoMode(width * SBLOCK, height * SBLOCK, 32, SDL_OPENGL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, static_cast<double>((width * SBLOCK)/(height * SBLOCK)), NEAR, FAR);
    glEnable(GL_DEPTH_TEST);
    _map.first = width;
    _map.second = height;
}


void OpenGLDisplay::display(const std::vector<AObject*> &map) const
{
    std::vector<Coord>                      coo;
    std::vector<Coord>::const_iterator      pos, last;

    std::vector<AObject*>::const_iterator   it, begin;

    Color                                   col;

    begin = map.begin();
    it = map.end();

    this->reset();
    this->setView(getCoo(_map.first/2, _map.second + 5 , (_map.first+_map.second)/2), getCoo(_map.first/2, _map.second/2, 0), getCoo(0, 0, 1));
    glRotated(0.0, 0, 0, 1);
    this->drawFloor();
    while (--it >= begin)
    {
        coo = ((*it)->getCoord());
        pos = coo.begin();
        last = coo.end();
        switch ((*it)->getType())
        {
        case WALL:
            col = getCol(0, 0, 255);
            break;
        case SNAKE:
            col = getCol(0, 255, 0);
            break;
        case POWERUP:
            col = getCol(255, 255, 0);
            break;
        case PORTAL:
            col = getCol(175, 0, 175);
            break;
        default:
            col = getCol(255, 0, 255);
            break;
        }
        while (pos < last)
        {
            this->drawCube(getCoo(pos->first, pos->second, 0), col);
            ++pos;
        }
    }
    this->refresh();
}

Key  OpenGLDisplay::getKey(void) const
{
    static SDL_Event	e;

    SDL_WaitEvent(&e);

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
	case SDLK_UP:
	  return UP;
	case SDLK_DOWN:
	  return DOWN;
        case SDLK_LEFT:
            return RIGHT;
        case SDLK_RIGHT:
            return LEFT;
        case SDLK_ESCAPE:
            return QUIT;
        case SDLK_SPACE:
          return SPACE;
        default:
            return OTHERS;
        }
    }
    else if (e.type == SDL_QUIT)
        return QUIT;
    else
        return OTHERS;
}

/////////////////
// Entry point //
/////////////////
extern "C" IDisplay *getDisplay(void)
{
    return new OpenGLDisplay();
}
