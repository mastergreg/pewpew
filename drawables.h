#ifndef DRAWABLES_H
#define DRAWABLES_H

#include "game_object.h"
#include <GL/glut.h>
//#include "level.h"

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
 
class circle : public game_object
{
  private:
    double radius;
    vector position;
    GLfloat  color[3];
    double angleStep;
    double x[256];
    double y[256];
    void move();
  public:
    circle(double radius,vector position,GLfloat mycolor[3]);
    void draw(vector pos);
};

#endif
