/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sonic_weapon.h

* Purpose :

* Creation Date : 14-11-2011

* Last Modified : Wed 16 Nov 2011 01:45:38 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef SONIC_WEAPON_H
#define SONIC_WEAPON_H


#include "main_weapon.h"

class sonic : public main_weapon
{
  private:
    double internal_radius;
  protected:
    GLuint theShot;
    void compileDraw();
  public:
    void move();
    sonic(vector2D p,vector2D s);
    void draw();

};


#endif
