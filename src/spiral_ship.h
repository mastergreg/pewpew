/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : spiral_ship.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:19:08 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef SPIRAL_SHIP_H
#define SPIRAL_SHIP_H

#include "game_ship.h"

class spiralShip : public game_ship
{
  private:
    std::list<vector2D *> pattern;
    std::list<game_object *> tail;
    int Ttime;
    bool rot;
  public:
    void draw();
    void die();
    void move();
    spiralShip(vector2D pos,vector2D sp);
};


#endif
