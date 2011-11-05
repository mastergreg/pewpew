/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : upgrades.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:12:42 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef UPGRADES_H
#define UPGRADES_H

#include "game_ship.h"

class fireUpgrade : public game_ship
{
  public:
    void move();
    void draw();
    fireUpgrade(vector2D p);
};
class lifeUpgrade : public game_ship
{
  public:
    void move();
    void draw();
    lifeUpgrade(vector2D p);
};
#endif
