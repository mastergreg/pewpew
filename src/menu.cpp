/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : menu.cpp

 * Purpose :

 * Creation Date : 19-10-2011

 * Last Modified : Thu 03 Nov 2011 08:16:06 PM EET

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
  playStick();
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
void menu::add_option(std::string txt_on,void (*action_on)(void),std::string txt_off,void (*action_off)(void))
{
  options.push_back(new toogle_button(nextX,nextY,txt_on,action_on,txt_off,action_off));
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
      back();
//      exit(0);
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
void menu::idleMouseFunction(int x,int y)
{
  GLdouble farea,rem;
  unsigned int area;

  GLint viewport[4];
  GLdouble mvmatrix[16], projmatrix[16];
  GLint realy;  /*  OpenGL y coordinate position  */
  GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */

  glGetIntegerv (GL_VIEWPORT, viewport);
  glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
  glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
  /*  note viewport[3] is height of window in pixels  */
  realy = viewport[3] - (GLint) y - 1;
  gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0,
      mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
  farea = DIMENSION/2 - 1 -  wy;
  area = (unsigned int) farea;
  rem = farea - area;
  if (rem > 0.6)
  {

    Mchoice = area < options.size()-1 ? area : options.size()-1;
  }
}
void menu::mouseFunction(int butn,int state,int x,int y)
{
  GLdouble farea,rem;
  unsigned int area;
  unsigned int Bchoice;

  GLint viewport[4];
  GLdouble mvmatrix[16], projmatrix[16];
  GLint realy;  /*  OpenGL y coordinate position  */
  GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */

  glGetIntegerv (GL_VIEWPORT, viewport);
  glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
  glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
  /*  note viewport[3] is height of window in pixels  */
  realy = viewport[3] - (GLint) y - 1;
  gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0,
      mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
  farea = DIMENSION/2 - 1 -  wy;
  area = (unsigned int) farea;
  rem = farea - area;

  if (rem > 0.6)
  {
  Bchoice = area < options.size()-1 ? area : options.size()-1;
  if (Bchoice == Mchoice)
  {
    if (state == GLUT_DOWN)
    {
      options[Mchoice]->activate();
    }

  }
  else
  {
    if (state == GLUT_DOWN)
    {
      Mchoice = Bchoice;
    }
  }
  }
}
void menu::reshape(int w,int h)
  /*  note viewport[3] is height of window in pixels  */
{
  GLsizei minSize=w>h ? (GLsizei) h : (GLsizei) w;
  minSize-=50;

  GLsizei startX=((w-h)/2-100);
  if (startX>0)
  {
    glViewport(startX,0,minSize,minSize);
  }
  else
  {
    glViewport(0,-startX,minSize,minSize);
  }
  WINDOW_SIZEX=w;
  WINDOW_SIZEY=h;
}


void menu::playStick()
{
  wwvi_js_event *js_state = new wwvi_js_event;
  memset(js_state,0,sizeof(wwvi_js_event));
  if (get_joystick_status(js_state)==0)
  {
    if (js_state->button[5]>0)
    {
      Mchoice = (Mchoice+1)%options.size();
    }
    else if (js_state->button[4]>0)
    {
      Mchoice = (Mchoice-1)%options.size();
    }
    else if (js_state->button[2]>0)
    {
      options[Mchoice]->activate();
    }
  }
}

infoscreen::infoscreen(std::string t)
{
  tinyFont = GLUT_BITMAP_9_BY_15;
  text = t;
  nextY = -DIMENSION/4.;
}
void infoscreen::display()
{
  //drawGrid();
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
  drawMenu(0);
}


//void infoscreen::myIdleMouseFunction(int x,int y)
//{
//}
//void infoscreen::myMouseFunction(int btn,int state,int x,int y)
//{
//}
//void infoscreen::keyboardFunction(unsigned char key,int x,int y)
//{
//  switch (key)
//  {
//    case 27:
//      options[0]->activate();
//      break;
//    case 13:
//      options[0]->activate();
//      break;
//  }
//}
//void infoscreen::specialKeyboardFunction(int key,int x, int y)
//{
//}
