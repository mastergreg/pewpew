/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : game_ship.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:52:12 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef GAME_SHIP_H
#define GAME_SHIP_H


#include "game_object.h"
#include "drawables.h"
#include <list>
#include <GL/glut.h>





class game_ship : public game_object
{
  protected:
    double angle;
    vector2D speed;
    double spini;
    double spinnit();
  public:
    virtual void die();
    virtual void move();
    double get_angle();
    void set_angle(double newAngle);
    game_ship(vector2D pos,vector2D sp);
    vector2D get_speed();
    bool isAlive();
    void set_speed(vector2D new_speed);
    std::list<game_object *> collisions(std::list<game_ship *> lst);
    vector2D get_pos();
};


#endif
