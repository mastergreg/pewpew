#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "vector2D.h"

class game_object
{
  protected:
    vector2D position;
    double radius;
    int life;
    //Pure virtual function 
    //to make it an abstract class
    bool collides(game_object *);//TODO
  public:
    game_object();
    game_object(vector2D pos);
    void set_life(int new_life);
    int get_life();
    //Pure virtual function 
    //to make it an abstract class
    virtual ~game_object(){};
    virtual void die();
    virtual void move()=0;
    virtual void draw();
};
#endif
