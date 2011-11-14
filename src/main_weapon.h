/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : main_weapon.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Mon 14 Nov 2011 10:15:05 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef MAIN_WEAPON_H
#define MAIN_WEAPON_H

#ifndef WEAPONS
#define WEAPONS 3
#endif
#include "game_ship.h"

class main_weapon : public game_ship
{
  protected:
    GLuint theShot;
    virtual void compileDraw();
    int killStep;
    double wfs;
  public:
    void move();
    main_weapon(vector2D posit,vector2D sp);
    virtual void draw();
};


#endif
