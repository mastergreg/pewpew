#ifndef LEVEL_H
#define LEVEL_H
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <algorithm>
#include <time.h>

#include "ships.h"
#include "joystick.h"
#define DT 0.01
#define DIMENSION 6
class level
{
    void *font;
    void *tinyFont;
    int WINDOW_SIZEX;
    int WINDOW_SIZEY;
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
    vector startingSpeed;
    int windowX;
    int windowY;
    int ZoomLevel;
    bool paused;
    bool drawInfo;
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
    void reset();
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
    void ScoreBasedEvents();
    void TimeBasedEvents();
    void drawScene();
    void launchAction(int choice);
    void play();
    void drawMenu(int choice);
    void drawInfoScreen();
    void ZooMStart();
    void shipExplode(vector position);
  public:
    level();
    void insertScoreTag(vector position, int points);
    void increaseScore(int points);
    void display();
    void keyboardReleaseFunction(unsigned char key,int x, int y);
    void specialKeyboardFunction(int key,int x,int y);
    void keyboardFunction(unsigned char key,int x,int y);
    void myMouseFunction(int x,int y);
    void reshape(int w,int h);
};
#endif
