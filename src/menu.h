/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu.h

* Purpose :

* Creation Date : 19-10-2011

* Last Modified : Sat 18 Aug 2012 02:25:22 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef MENU
#define MENU
#include "level.h"
#include "menu_items.h"
#include "screen_handler.h"
#include "high_score_handler.h"
#include <vector>
#include <GL/glut.h>
#include <string>
class menu : public screen_handler
{
protected:
    GLfloat nextX,nextY;
    void drawMenu(int choice);
    std::vector<button *> options;
    unsigned int Mchoice;
    void drawGrid();
    void playStick();
public:
    menu();
    virtual void display();
    void reshape(int w,int h);
    void idleMouseFunction(int x,int y);
    void mouseFunction(int btn,int state,int x,int y);
    void keyboardFunction(unsigned char key,int x, int y);
    void specialKeyboardFunction(int key,int x, int y);
    void add_option(std::string txt,void (*action)(void));
    void add_option(std::string txt_on,void (*action_on)(void),std::string txt_off,void (*action_off)(void));
};
class infoscreen:public menu
{
private:
    void *tinyFont;
    std::string text;
public:
    infoscreen(std::string t);
    void display();
};

class scorescreen:public menu
{
private:
    void *tinyFont;
    high_score_handler hs;
    std::vector<std::string *> hscores;
public:
    scorescreen();
    void display();
};



#endif //MENU
