/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : fire_weapon.h

* Purpose :

* Creation Date : 14-11-2011

* Last Modified : Mon 14 Nov 2011 12:22:01 AM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef FIRE_WEAPON_H
#define FIRE_WEAPON_H

#include "main_weapon.h"
class fire : public main_weapon
{
  private:
    GLuint theShot;
    void compileDraw();
  public:
    fire(vector2D posit,vector2D sp);
    void draw();
};


#endif
