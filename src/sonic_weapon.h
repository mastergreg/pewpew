/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sonic_weapon.h

* Purpose :

* Creation Date : 14-11-2011

* Last Modified : Mon 14 Nov 2011 09:41:11 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef SONIC_WEAPON_H
#define SONIC_WEAPON_H


#include "main_weapon.h"

class sonic : public main_weapon
{
  protected:
    GLuint theShot;
    void compileDraw();
  public:
    sonic(vector2D p,vector2D s);
    void draw();

};


#endif
