/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu.h

* Purpose :

* Creation Date : 19-10-2011

* Last Modified : Mon 24 Oct 2011 04:08:59 PM EEST

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
    void *font;
    void *tinyFont;
    void playStick();
  protected:
    GLfloat nextX,nextY;
    void drawMenu(int choice);
    std::vector<button *> options;
    unsigned int Mchoice;
    void drawGrid();
  public:
    menu();
    virtual void display();
    void reshape(int w,int h);
    virtual void myIdleMouseFunction(int x,int y);
    virtual void myMouseFunction(int btn,int state,int x,int y);
    virtual void keyboardFunction(unsigned char key,int x, int y);
    virtual void specialKeyboardFunction(int key,int x, int y);
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
    void myIdleMouseFunction(int x,int y);
    void myMouseFunction(int btn,int state,int x,int y);
    void keyboardFunction(unsigned char key,int x, int y);
    void specialKeyboardFunction(int key,int x, int y);
};



#endif //MENU
