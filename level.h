#ifndef LEVEL_H
#define LEVEL_H
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <list>
#include "ships.h"
#include "drawFunctions.h"
#define DT 0.01
class level
{
  public:
    void *font;
    vector esp;
    vector pos;
    int WINDOW_SIZEX;
    int WINDOW_SIZEY;
    double mX,mY;
    std::list<game_ship *> fireList;
    std::list<game_ship *> enemyList;
    std::list<game_object *> drawableList;
    level();
    void output(double x, double y, char *string);
    void reshape(int w,int h);
    void show_score(int score);
    void keyboardReleaseFunction(unsigned char key,int x, int y);
    void keyboardFunction(unsigned char key,int x,int y);
    void myMouseFunction(int x,int y);
    double shipMouseAngle();
    int enemie_before;
    int enemie_after;
    int enemie_killed;
    int score;
    int time;
    int ftime;
    void start();
    void play();
    void drawScene();
    ship playerShip;
    vector startingSpeed;
    int windowX;
    int windowY;
};
#endif
