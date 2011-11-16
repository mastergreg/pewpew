/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : player_ships.h

* Purpose :

* Creation Date : 20-12-2008

* Last Modified : Mon 14 Nov 2011 09:46:37 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef PLAYER_SHIPS_H
#define PLAYER_SHIPS_H

#include "game_ship.h"
#include "fire_weapon.h"
#include "pulse_weapon.h"
#include "sonic_weapon.h"
#include "upgrades.h"


class ship : public game_ship
{
    void upgradeWeapons();
    int WeaponLevel;
    circle* UpgradeCirc;
    void drawUPArrow(game_ship * upgrade,GLfloat color[3]);
    std::list<game_object *> tail;
    int Ttime;
    int WeaponType;
    template <class T> 
      std::list<main_weapon*> fireWeapon(double angle);
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
    std::list<main_weapon*> shoot();
    std::list<main_weapon*> shoot(double ang);
    void drawUpgradeRing(std::list<game_ship *> fireUpgradeList,std::list<game_ship *> lifeUpgradeList);
    ship();
    ~ship();
};







#endif
