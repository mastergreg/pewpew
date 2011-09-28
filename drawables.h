#ifndef DRAWABLES_H
#define DRAWABLES_H

#include "game_object.h"
#include <string.h>
#include <algorithm>
#include <GL/glut.h>
//#include "level.h"

class chink : public game_object
{
    void die();
    void move();
  public:
    chink(vector2D position);
    void draw();
};

class xplosion : public game_object
{
    void die();
    void move();
    double spini;
    double spinnit();
  public:
    xplosion(vector2D position);
    void draw();
};
 
class circle : public game_object
{
  private:
    double radius;
    vector2D position;
    GLfloat  color[3];
    double angleStep;
    double x[256];
    double y[256];
    void move();
  public:
    circle(double radius,vector2D position,GLfloat mycolor[3]);
    void draw(vector2D pos);
};
class score_tag : public game_object
{
  private:
    void *font;
    char c_points[20];
    int len;
  public:
    score_tag(vector2D pos,int pts);
    void draw();
    void move();
};

class ship_tail : public game_object
{
  protected:
    vector2D position;
    GLfloat  color[3];
    double angle;
    int spin;
  public:
    ship_tail(vector2D position,double ang,GLfloat mycolor[3]);
    void draw();
    void move();
};
class big_ship_tail : public ship_tail
{
  public:
    big_ship_tail(vector2D position,double ang,GLfloat mycolor[3]);
    void draw();
};

class minimap : public game_object
{
  private:
  public:
    minimap(vector2D position);
    void draw();
};
#endif
