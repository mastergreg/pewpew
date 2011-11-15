/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : pulse_weapon.h

* Purpose :

* Creation Date : 13-11-2011

* Last Modified : Mon 14 Nov 2011 12:19:26 AM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef PULSE_WEAPON_H
#define PULSE_WEAPON_H

#include "main_weapon.h"

class pulse : public main_weapon
{
  protected:
    GLuint theShot;
    void compileDraw();
  public:
    pulse(vector2D p,vector2D s);
    void draw();

};



#endif
