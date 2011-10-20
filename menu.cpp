/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : menu.cpp

 * Purpose :

 * Creation Date : 19-10-2011

 * Last Modified : Thu 20 Oct 2011 04:55:10 PM EEST

 * Created By : Greg Liras <gregliras@gmail.com>

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "menu.h"
menu::menu()
{
  //WINDOW_SIZEX=800;
  //WINDOW_SIZEY=600;
  Mchoice = 0;
  font = GLUT_BITMAP_TIMES_ROMAN_24;
  tinyFont = GLUT_BITMAP_8_BY_13;
  nextX=0;
  nextY= (GLfloat) DIMENSION/2-1;
}

void menu::display()
{
  drawMenu(Mchoice);
}
void menu::drawMenu(int choice)
{
  drawGrid();
  glLoadIdentity();
  glOrtho(-DIMENSION/2,DIMENSION/2,-DIMENSION/2,DIMENSION/2,-5,5);
  std::vector<button *>::iterator p;
  p = options.begin();
  while(p!=options.end())
  {
    (*p)->unhoover();
    p++;
  }
  options[choice]->onhoover();
  p = options.begin();
  while(p!=options.end())
  {
    (*p)->draw();
    p++;
  }
}
void menu::add_option(std::string txt,void (*action)())
{
  options.push_back(new button(nextX,nextY,txt,action));
  nextY -= 1.0;
}
void menu::drawGrid()
{
  double i;
  GLfloat  gridColor[]={0.,0.25,0.5};
  GLfloat  borderColor[]={0.66,0.0,0.0};
  for(i=-DIMENSION+0.2;i<DIMENSION;i+=0.2)
  {
    glPushMatrix();
    glLineWidth(1);
    glColor3fv(gridColor);
    glBegin(GL_LINES);
    glVertex3f(i,-DIMENSION,0);
    glVertex3f(i,DIMENSION,0);
    glVertex3f(-DIMENSION,i,0);
    glVertex3f(DIMENSION,i,0);
    glEnd();
    glPopMatrix();
  }
  glLineWidth(5);
  glColor3fv(borderColor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glBegin(GL_LINES);

  glVertex3f(DIMENSION-0.2,-DIMENSION,0);
  glVertex3f(DIMENSION-0.2,DIMENSION,0);

  glVertex3f(-DIMENSION+0.2,-DIMENSION,0);
  glVertex3f(-DIMENSION+0.2,DIMENSION,0);

  glVertex3f(-DIMENSION,DIMENSION-0.2,0);
  glVertex3f(DIMENSION,DIMENSION-0.2,0);

  glVertex3f(-DIMENSION,-DIMENSION+0.2,0);
  glVertex3f(DIMENSION,-DIMENSION+0.2,0);

  glEnd();

}
void menu::keyboardFunction(unsigned char key,int x,int y)
{
  switch (key)
  {
    case 27:
      exit(0);
      break;
    case 'w':
      Mchoice = (Mchoice-1)%options.size();
      break;
    case 'a':
      break;
    case 's':
      Mchoice = (Mchoice+1)%options.size();
      break;
    case 'd':
      break;
    case 'q':
      exit(0);
      break;
    case 13:
      options[Mchoice]->activate();
      break;
  }
}
void menu::specialKeyboardFunction(int key,int x, int y)
{

  switch (key)
  {
    case GLUT_KEY_DOWN:
      Mchoice = (Mchoice+1)%options.size();
      break;
    case GLUT_KEY_UP:
      Mchoice = (Mchoice-1)%options.size();
      break;
  }
}



infoscreen::infoscreen(std::string t)
{
  tinyFont = GLUT_BITMAP_9_BY_15;
  text = t;
}
void infoscreen::display()
{
  drawGrid();
  glLoadIdentity();
  glOrtho(-DIMENSION/3.,DIMENSION/3.,-DIMENSION/3.,DIMENSION/3.,-5,5);
  unsigned int i,j;
  for (j=0;j<text.size();)
  {
    glRasterPos2f(-DIMENSION/4.,DIMENSION/4.-j/50.);
    for (i=0;i<50 && j<text.size();j++,i++)
    {
      glutBitmapCharacter(tinyFont,text[j]);
    }
  }
}


