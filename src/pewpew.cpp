/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : pewpew.cpp

 * Purpose :

 * Creation Date : 20-12-2008

 * Last Modified : Wed 02 Nov 2011 10:04:11 PM EET

 * Created By : Greg Liras <gregliras@gmail.com>

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "pewpew.h"


level lv;
menu mn;
menu opt;
infoscreen info("Press P to start, use WASD to move the ship, Q for turbo boost, E for e-break and Esc to exit");
game_state gs;
std::stack<screen_handler *> menu_pages;
static void mytimer(int v)
{
  glutPostRedisplay();
  glutTimerFunc(20,mytimer,1);
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
  mn.add_option(std::string("NEW GAME"),(&new_game));
  mn.add_option(std::string("OPTIONS"),(&option_action));
  mn.add_option(std::string("QUIT"),(&end_0));
  menu_pages.push(&mn);



  opt.add_option(std::string("BACK"),(&back));
  opt.add_option(std::string("SOUNDS ON"),(&sound_off),std::string("SOUNDS OFF"),(&sound_on));


  info.add_option(std::string("BACK"),(&back));

  //GLfloat filter[11] = {0.3,0.28,0.26,0.24,0.22,0.20,0.22,0.24,0.26,0.28,0.3};	//GOOD
  //glSeparableFilter2D(GL_SEPARABLE_2D, GL_LUMINANCE, 11, 11, GL_LUMINANCE, GL_FLOAT, filter,filter); //<< segfault !!!

  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  //glutIdleFunc(mytimer);
  glutTimerFunc(20,mytimer,1);

  glutIgnoreKeyRepeat(1);
  glutKeyboardUpFunc(kbRelF);
  glutSpecialFunc(skbF);
  glutKeyboardFunc(kbF);
  glutPassiveMotionFunc(mIdleF);
  glutMouseFunc(mF);
  glutMainLoop();

  return 0;
}
void display()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  menu_pages.top()->display();
  glutSwapBuffers();
}
void reshape(int w,int h)
{
  menu_pages.top()->reshape(w,h);
}
void kbRelF(unsigned char key, int x, int y)
{
  menu_pages.top()->keyboardReleaseFunction(key,x,y);

}
void kbF(unsigned char key, int x, int y)
{
  menu_pages.top()->keyboardFunction(key,x,y);
}
void skbF(int key, int x, int y)
{
  menu_pages.top()->specialKeyboardFunction(key,x,y);
}
void mIdleF(int x, int y)
{
  menu_pages.top()->idleMouseFunction(x,y);
}
void mF(int btn,int state,int x, int y)
{
  menu_pages.top()->mouseFunction(btn,state,x,y);
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
void new_game(void)
{
  menu_pages.push(&lv);
  lv.reset();
}
void run(void)
{
  menu_pages.push(&lv);
}
void gpause(void)
{
  menu_pages.pop();
}

void back(void)
{
  menu_pages.pop();
}
void info_action(void)
{
  menu_pages.push(&info);
}
void option_action(void)
{
  menu_pages.push(&opt);
}
void sound_off(void)
{
  gs.gs_sound_off();
}
void sound_on(void)
{
  gs.gs_sound_on();
}
