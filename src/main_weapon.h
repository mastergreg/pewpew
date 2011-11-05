/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : main_weapon.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:14:04 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef MAIN_WEAPON_H
#define MAIN_WEAPON_H

#include "game_ship.h"

class fire : public game_ship
{
  private:
    GLuint theShot;
  public:
    void move();
    fire(vector2D posit,vector2D sp);
    void draw();
};


#endif
