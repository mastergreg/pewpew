/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu.h

* Purpose :

* Creation Date : 19-10-2011

* Last Modified : Fri 21 Oct 2011 05:05:23 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef MENU
#define MENU
#include "level.h"
#include "menu_items.h"
#include <vector>
#include <GL/glut.h>
class menu
{
  private:
    int WINDOW_SIZEY;
    int WINDOW_SIZEX;
    GLfloat nextX,nextY;
    void *font;
    void *tinyFont;
    std::vector<button *> options;
    int Mchoice;
    void playStick();
  protected:
    void drawGrid();
  public:
    menu();
    void display();
    void reshape(int w,int h);
    void myIdleMouseFunction(int x,int y);
    void myMouseFunction(int btn,int state,int x,int y);
    void keyboardFunction(unsigned char key,int x, int y);
    void specialKeyboardFunction(int key,int x, int y);
    void drawMenu(int choice);
    void add_option(std::string txt,void (*action)(void));
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



#endif //MENU
