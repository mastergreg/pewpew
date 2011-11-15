/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : upgrades.h

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Mon 14 Nov 2011 12:19:59 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef UPGRADES_H
#define UPGRADES_H

#include "game_ship.h"


class fireUpgrade : public game_ship
{
    int WeaponType;
  public:
    void move();
    void draw();
    fireUpgrade(vector2D p,int wT);
    int getType();
};
class lifeUpgrade : public game_ship
{
  public:
    void move();
    void draw();
    lifeUpgrade(vector2D p);
};
#endif
