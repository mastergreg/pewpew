/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : player_ships.h

* Purpose :

* Creation Date : 20-12-2008

* Last Modified : Sat 05 Nov 2011 08:45:38 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef PLAYER_SHIPS_H
#define PLAYER_SHIPS_H

#include "game_ship.h"
#include "main_weapon.h"
#include "upgrades.h"


class ship : public game_ship
{
    void upgradeWeapons();
    int WeaponLevel;
    circle* UpgradeCirc;
    void drawUPArrow(game_ship * upgrade,GLfloat color[3]);
    std::list<game_object *> tail;
    int Ttime;
  public:
    void accelerate();
    void decelerate();
    void release_acc();
    void release_rot();
    void turn_right();
    void turn_left();
    void turbo_boost();
    void e_brake();

    void collectFireUpgrades(std::list<game_ship *> upgrades);
    void collectLifeUpgrades(std::list<game_ship *> upgrades);
    void draw();
    void move();
    void downgradeWeapons();
    std::list<fire*> shoot();
    std::list<fire*> shoot(double ang);
    void drawUpgradeRing(std::list<game_ship *> fireUpgradeList,std::list<game_ship *> lifeUpgradeList);
    ship();
    ~ship();
};







#endif
