/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu_items.h

* Purpose :

* Creation Date : 20-10-2011

* Last Modified : Thu 20 Oct 2011 03:50:48 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H
#include <string>
#include <GL/glut.h>
class button
{
  private:
    std::string text;
    bool hoover;
    void (*btn_action)(void);
    GLfloat X,Y,sizeX,sizeY;
    void *font;

  public:
    button(GLfloat x,GLfloat y,std::string txt,void (*action)(void),GLfloat sizex = 4.4,GLfloat sizey = 0.4);
    void draw();
    void onhoover();
    void unhoover();
    void activate();

};



#endif //MENU_ITEMS_H
