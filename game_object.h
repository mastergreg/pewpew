#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "vector.h"

class game_object
{
  protected:
    vector position;
    double radius;
    int life;
    //Pure virtual function 
    //to make it an abstract class
    virtual void move()=0;
    bool collides(game_object *);//TODO
  public:
    game_object();
    game_object(vector pos);
    int get_life();
    //Pure virtual function 
    //to make it an abstract class
    virtual void die();
    virtual void draw();
};
#endif
