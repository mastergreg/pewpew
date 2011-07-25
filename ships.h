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
class spiralShip : public game_ship
{
  private:
    std::list<vector *> pattern;
    std::list<game_object *> tail;
  public:
    void draw();
    void die();
    void move();
    spiralShip(vector pos,vector sp);
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
class lifeUpgrade : public game_ship
{
  public:
    void die();
    void move();
    void draw();
    lifeUpgrade(vector p);
};

class ship : public game_ship
{
    void upgradeWeapons();
    int WeaponLevel;
    circle* UpgradeCirc;
    void drawUPArrow(game_ship * upgrade,GLfloat color[3]);
  public:
    void die();
    void collectFireUpgrades(std::list<game_ship *> upgrades);
    void collectLifeUpgrades(std::list<game_ship *> upgrades);
    void draw();
    void downgradeWeapons();
    std::list<fire*> shoot();
    std::list<fire*> shoot(double ang);
    void drawUpgradeRing(std::list<game_ship *> fireUpgradeList,std::list<game_ship *> lifeUpgradeList);
    ship();
};







#endif
