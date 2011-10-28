/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : menu_items.cpp

* Purpose :

* Creation Date : 20-10-2011

* Last Modified : Sun 23 Oct 2011 05:59:20 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/


#include "menu_items.h"

button::button()
{

}

button::button(GLfloat x,GLfloat y,std::string txt,void (*action)(void),GLfloat sx,GLfloat sy)
{
  sizeX = sx;
  sizeY = sy;
  X = x-sizeX/2;
  Y = y;
  hoover  = false;
  btn_action = action;
  text = txt;
  font = GLUT_BITMAP_9_BY_15;
  theButton = glGenLists(1);
  glNewList(theButton,GL_COMPILE);
  glBegin(GL_LINE_STRIP);
    glVertex2f(X,Y);
    glVertex2f(X,Y-sizeY/2);
    glVertex2f(X+sizeY/2,Y-sizeY);
    glVertex2f(X+sizeX,Y-sizeY);
    glVertex2f(X+sizeX,Y-sizeY/2);
    glVertex2f(X+(sizeX-sizeY/2),Y);
    glVertex2f(X,Y);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glVertex2f(X,Y);
    glVertex2f(X,Y-sizeY/2-sizeY/8);
    glVertex2f(X+sizeY/2,Y-sizeY-sizeY/8);
    glVertex2f(X+sizeX,Y-sizeY-sizeY/8);
    glVertex2f(X+sizeX,Y-sizeY);
  glEnd();
  glEndList();

}

void button::draw()
{
  unsigned int i;
  glPushMatrix();
  if (hoover)
  {
    glColor3f(1,0,0);
    glLineWidth(2);
  }
  else
  {
    glColor3f(0,1,0);
    glLineWidth(1);
  }
  glCallList(theButton);
  glRasterPos2f(X+sizeX/4, Y-sizeY/2);
  for (i=0;i<text.size();i++)
  {
    glutBitmapCharacter(font,text[i]);
  }
  glTranslatef(X,Y,0);
  glPopMatrix();
}
void button::onhoover()
{
  hoover = true;
}
void button::unhoover()
{
  hoover = false;
}
void button::activate()
{
  (*btn_action)();
}


toogle_button::toogle_button(GLfloat x,GLfloat y,std::string txt_on,void (*action_on)(void),std::string txt_off,void (*action_off)(void),GLfloat sx ,GLfloat sy )
{
  sizeX = sx;
  sizeY = sy;
  X = x-sizeX/2;
  Y = y;
  hoover  = false;
  on = true;
  btn_action_on = action_on;
  btn_action_off = action_off;
  text_on = txt_on;
  text_off = txt_off;
  font = GLUT_BITMAP_9_BY_15;
  theButton = glGenLists(1);
  glNewList(theButton,GL_COMPILE);
  glBegin(GL_LINE_STRIP);
    glVertex2f(X,Y);
    glVertex2f(X,Y-sizeY/2);
    glVertex2f(X+sizeY/2,Y-sizeY);
    glVertex2f(X+sizeX,Y-sizeY);
    glVertex2f(X+sizeX,Y-sizeY/2);
    glVertex2f(X+(sizeX-sizeY/2),Y);
    glVertex2f(X,Y);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glVertex2f(X,Y);
    glVertex2f(X,Y-sizeY/2-sizeY/8);
    glVertex2f(X+sizeY/2,Y-sizeY-sizeY/8);
    glVertex2f(X+sizeX,Y-sizeY-sizeY/8);
    glVertex2f(X+sizeX,Y-sizeY);
  glEnd();
  glEndList();
}
void toogle_button::draw()
{
  unsigned int i;
  std::string text;
  if (on)
  {
    text = text_on;
  }
  else
  {
    text = text_off;
  }
  glPushMatrix();
  if (hoover)
  {
    glColor3f(1,0,0);
    glLineWidth(2);
  }
  else
  {
    glColor3f(0,1,0);
    glLineWidth(1);
  }
  glCallList(theButton);
  glRasterPos2f(X+sizeX/4, Y-sizeY/2);
  for (i=0;i<text.size();i++)
  {
    glutBitmapCharacter(font,text[i]);
  }
  glTranslatef(X,Y,0);
  glPopMatrix();
}
void toogle_button::activate()
{
  if (on)
  {
    (*btn_action_on)();
  }
  else
  {
    (*btn_action_off)();
  }
  on = !on;

}
