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
    bool collides(game_object *);//TODO
  public:
    game_object();
    game_object(vector pos);
    void set_life(int new_life);
    int get_life();
    //Pure virtual function 
    //to make it an abstract class
    virtual ~game_object(){}
    virtual void die();
    virtual void move()=0;
    virtual void draw();
};
#endif
