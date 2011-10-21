/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : pewpew.cpp

 * Purpose :

 * Creation Date : 20-12-2008

 * Last Modified : Fri 21 Oct 2011 04:59:35 PM EEST

 * Created By : Greg Liras <gregliras@gmail.com>

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "pewpew.h"

level lv;
menu mn;
infoscreen info("Press P to start, use WASD to move the ship, Q for turbo boost, E for e-break and Esc to exit");
int paused = 1;

void display()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  if (paused == 1)
  {
    mn.display();
  }
  else if (paused == 0)
  {
    lv.display();
  }
  else if (paused == 2)
  {
    info.display();
  }
  usleep(10000);
  glutSwapBuffers();
}
void reshape(int w,int h)
{

  if (paused == 1)
  {
    mn.reshape(w,h);
  }
  else
  {
    lv.reshape(w,h);
  }
}
void kbRelF(unsigned char key, int x, int y)
{
  lv.keyboardReleaseFunction(key,x,y);
}
void kbF(unsigned char key, int x, int y)
{
  if (paused == 1)
  {
    mn.keyboardFunction(key,x,y);
  }
  else
  {
    lv.keyboardFunction(key,x,y);
  }
}
void skbF(int key, int x, int y)
{
  if (paused == 1)
  {
    mn.specialKeyboardFunction(key,x,y);
  }
  else
  {
    lv.specialKeyboardFunction(key,x,y);
  }
}
void mIdleF(int x, int y)
{
  if (paused == 1)
  {
    mn.myIdleMouseFunction(x,y);
  }
  else
  {
    lv.myMouseFunction(x,y);
  }
}
void mF(int btn,int state,int x, int y)
{
  if (paused == 1)
  {
    mn.myMouseFunction(btn,state,x,y);
  }
}



int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(800,600);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutCreateWindow("PewPew");
  //glEnable(GL_LIGHTING);
  glEnable(GL_BLEND);
  //glShadeModel(GL_SMOOTH);
  //glEnable(GL_LIGHT0);
  glMatrixMode(GL_PROJECTION);

  open_joystick();

  mn.add_option(std::string("INFO"),(&info_action));
  mn.add_option(std::string("PLAY"),(&run));
  //mn.add_option(std::string("OPTIONS"),(&end));
  //mn.add_option(std::string("OPTIONS"),(&end));
  mn.add_option(std::string("QUIT"),(&end_0));

  //GLfloat filter[11] = {0.3,0.28,0.26,0.24,0.22,0.20,0.22,0.24,0.26,0.28,0.3};	//GOOD
  //glSeparableFilter2D(GL_SEPARABLE_2D, GL_LUMINANCE, 11, 11, GL_LUMINANCE, GL_FLOAT, filter,filter); //<< segfault !!!

  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(glutPostRedisplay);
  glutKeyboardUpFunc(kbRelF);
  glutSpecialFunc(skbF);
  glutKeyboardFunc(kbF);
  glutPassiveMotionFunc(mIdleF);
  glutMouseFunc(mF);
  glutMainLoop();

  return 0;
}

void end(void)
{
  exit(1);
}
void end_0(void)
{
  close_joystick();
  exit(0);
}
void run(void)
{
  paused = 0;
}
void gpause(void)
{
  paused = 1;
}
void info_action(void)
{
  paused = 2;
}
