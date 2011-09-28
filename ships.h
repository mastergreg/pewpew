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
    vector2D speed;
    double spini;
    double spinnit();
  public:
    virtual void die();
    virtual void move();
    double get_angle();
    void set_angle(double newAngle);
    game_ship(vector2D pos,vector2D sp);
    vector2D get_speed();
    bool isAlive();
    void set_speed(vector2D new_speed);
    std::list<game_object *> collisions(std::list<game_ship *> lst);
    vector2D get_pos();
};



class dummyship : public game_ship
{
  public:
    void draw();
    void die();
    dummyship(vector2D pos,vector2D sp);
};
class spiralShip : public game_ship
{
  private:
    std::list<vector2D *> pattern;
    std::list<game_object *> tail;
    int Ttime;
    bool rot;
  public:
    void draw();
    void die();
    void move();
    spiralShip(vector2D pos,vector2D sp);
};
class fire : public game_ship
{
  public:
    void move();
    fire(vector2D posit,vector2D sp);
    void draw();
};
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

class ship : public game_ship
{
    void upgradeWeapons();
    int WeaponLevel;
    circle* UpgradeCirc;
    void drawUPArrow(game_ship * upgrade,GLfloat color[3]);
    std::list<game_object *> tail;
    int Ttime;
  public:
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
