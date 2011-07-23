#ifndef SHIPS_H
#define SHIPS_H
#include "game_object.h"
#include "drawables.h"
#include <list>
#include <GL/glut.h>


class game_ship : public game_object
{
  protected:
    double angle;
    vector speed;
    double spini;
    double spinnit();
  public:

    virtual void die();
    virtual void move();
    double get_angle();
    game_ship(vector pos,vector sp);
    vector get_speed();
    bool isAlive();
    void set_speed(vector new_speed);
    std::list<game_object *> collisions(std::list<game_ship *> lst);
    vector get_pos();
    
};



class dummyship : public game_ship
{
  public:
    void draw();
    void die();
    dummyship(vector pos,vector sp);
};
class fire : public game_ship
{
  public:
    void move();
    void die();
    fire(vector posit,vector sp);
    void draw();
};
class fireUpgrade : public game_ship
{
  public:
    void die();
    void move();
    void draw();
    fireUpgrade(vector p);
};

class ship : public game_ship
{
    void upgradeWeapons();
    int WeaponLevel;
    circle* fireUpgradeCirc;
    void drawFUPArrow(game_ship * upgrade);
  public:
    void die();
    void collectFireUpgrades(std::list<game_ship *> upgrades);
    void draw();
    std::list<fire*> shoot();
    std::list<fire*> shoot(double ang);
    void drawFireUpgradeRing(std::list<game_ship *> fireUpgradeList);
    int getLife();
    ship();
};








#endif
