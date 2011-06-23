#ifndef SHIPS_H
#define SHIPS_H
#include "game_object.h"
#include "drawables.h"
#include <list>
#include <GL/glut.h>


class game_ship : public game_object
{
  protected:
    double angle;
    vector speed;
    double spini;
    double spinnit();
    virtual void die();
  public:

    virtual void move();
    double get_angle();
    game_ship(vector pos,vector sp);
    vector get_speed();
    bool isAlive();
    void set_speed(vector new_speed);
    std::list<game_object *> collisions(std::list<game_ship *> lst);
    
};



class dummyship : public game_ship
{
    void die();
  public:
    void draw();
    dummyship(vector pos,vector sp);
};
class ship : public game_ship
{
    void die();
  public:
    void draw();
    int getLife();
    ship();
    vector get_pos();
};





class fire : public game_ship
{
    void die();
    void move();
  public:
    fire(vector posit,vector sp);
    void draw();
};




#endif
