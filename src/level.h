#ifndef LEVEL_H
#define LEVEL_H
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <algorithm>
#include <time.h>

#include "sounds.h"
#include "ships.h"
#include "pewpew.h"
#include "joystick.h"
#include "screen_handler.h"
#define DT 0.01
#define DIMENSION 6


class level : public screen_handler
{
    int enemies_before;
    int enemies_after;
    int enemies_killed;
    int score;
    int dtime;
    int ftime;
    int lifeDraw;
    int MenuChoice;
    double mX,mY,jX,jY;
    ship *playerShip;
    vector2D startingSpeed;
    int windowX;
    int windowY;
    int ZoomLevel;
    bool firstLaunch;
    bool xploded;
    std::list<game_ship *> fireList;
    std::list<game_ship *> enemyList;
    std::list<game_ship *> fireUpgradeList;
    std::list<game_ship *> lifeUpgradeList;
    std::list<game_object *> drawableList;
    double shipMouseAngle();
    void start();
    void playStick();
    void pauseResume();
    void clipArroundShip();
    void insertDummyShip();
    void insertFireUpgrade();
    void insertLifeUpgrade();
    void insertSpiralShip();
    void drawGrid();
    void show_score(double x,double y,int score);
    void displayLife();
    void collisionDetect(std::list<game_ship *> bullets,std::list<game_ship *> enemies);
    void globalCollisions();
    void clearDead();
    void moveAll();
    void drawAll();
    void clean_dead(std::list<game_ship *>*);
    void clean_dead(std::list<game_object *>*);
    void ScoreBasedEvents();
    void TimeBasedEvents();
    void drawScene();
    void launchAction(int choice);
    void play();
    void drawMenu(int choice);
    void drawInfoScreen();
    void ZooMStart();
    void shipExplode(vector2D position);
    sound_player sndp;
  public:
    level();
    void reset();
    void insertScoreTag(vector2D position, int points);
    void increaseScore(int points);
    void display();
    void keyboardReleaseFunction(unsigned char key,int x, int y);
    void specialKeyboardFunction(int key,int x,int y);
    void keyboardFunction(unsigned char key,int x,int y);
    void idleMouseFunction(int x,int y);
    void reshape(int w,int h);
};
#endif
