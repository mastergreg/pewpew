#ifndef DRAWABLES_H
#define DRAWABLES_H

#include "game_object.h"
#include <list>
#include <GL/glut.h>

extern std::list<game_object *> drawableList; 

class chink : public game_object
{
    void die();
    void move();
  public:
    chink(vector position);
    void draw();
};

class xplosion : public game_object
{
    void die();
    void move();
    double spini;
    double spinnit();
  public:
    xplosion(vector position);
    void draw();
};
 

#endif
