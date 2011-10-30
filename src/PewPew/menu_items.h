/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu_items.h

* Purpose :

* Creation Date : 20-10-2011

* Last Modified : Sun 23 Oct 2011 05:51:57 PM EEST

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
    void (*btn_action)(void);
  protected:
    bool hoover;
    GLfloat X,Y,sizeX,sizeY;
    void *font;
    GLuint theButton;
  public:
    button();
    button(GLfloat x,GLfloat y,std::string txt,void (*action)(void),GLfloat sizex = 4.4,GLfloat sizey = 0.4);
    virtual void draw();
    void onhoover();
    void unhoover();
    virtual void activate();

};
class toogle_button: public button
{
  private:
    std::string text_on;
    std::string text_off;
    bool on;
    void (*btn_action_on)(void);
    void (*btn_action_off)(void);

  public:
    toogle_button(GLfloat x,GLfloat y,std::string txt_on,void (*action_on)(void),std::string txt_off,void (*action_off)(void),GLfloat sizex = 4.4,GLfloat sizey = 0.4);
    void draw();
    void activate();
};



#endif //MENU_ITEMS_H
