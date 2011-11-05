/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : dummyship.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:38:25 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef DUMMYSHIP_H
#define DUMMYSHIP_H

#include "game_ship.h"

class dummyship : public game_ship
{
  public:
    void draw();
    void die();
    dummyship(vector2D pos,vector2D sp);
};
#endif
