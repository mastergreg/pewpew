/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu.h

* Purpose :

* Creation Date : 19-10-2011

* Last Modified : Thu 20 Oct 2011 04:54:06 PM EEST

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
//    int WINDOW_SIZEY;
//    int WINDOW_SIZEX;
    GLfloat nextX,nextY;
    void *font;
    void *tinyFont;
    std::vector<button *> options;
    int Mchoice;
  protected:
    void drawGrid();
  public:
    menu();
    void display();
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
