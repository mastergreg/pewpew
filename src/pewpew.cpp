/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : pewpew.cpp

 * Purpose :

 * Creation Date : 20-12-2008

 * Last Modified : Wed 26 Oct 2011 04:56:11 PM EEST

 * Created By : Greg Liras <gregliras@gmail.com>

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "pewpew.h"

level lv;
menu mn;
menu opt;
infoscreen info("Press P to start, use WASD to move the ship, Q for turbo boost, E for e-break and Esc to exit");
game_state gs;


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



  opt.add_option(std::string("BACK"),(&back));
  opt.add_option(std::string("SOUNDS ON"),(&sound_off),std::string("SOUNDS OFF"),(&sound_on));


  info.add_option(std::string("BACK"),(&back));

  //GLfloat filter[11] = {0.3,0.28,0.26,0.24,0.22,0.20,0.22,0.24,0.26,0.28,0.3};	//GOOD
  //glSeparableFilter2D(GL_SEPARABLE_2D, GL_LUMINANCE, 11, 11, GL_LUMINANCE, GL_FLOAT, filter,filter); //<< segfault !!!

  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  //glutIdleFunc(mytimer);
  glutTimerFunc(100,mytimer,1);

  glutKeyboardUpFunc(kbRelF);
  glutSpecialFunc(skbF);
  glutKeyboardFunc(kbF);
  glutPassiveMotionFunc(mIdleF);
  glutMouseFunc(mF);
  glutMainLoop();

  return 0;
}
static void mytimer(int v)
{
  glutPostRedisplay();
  glutTimerFunc(20,mytimer,1);
}
void display()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.display();
    }
    else if(gs.menu_page == 1)
    {
      info.display();
    }
    else if(gs.menu_page == 2)
    {
      opt.display();
    }
  }
  else 
  {
    lv.display();
  }
  glutSwapBuffers();
}
void reshape(int w,int h)
{
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.reshape(w,h);
    }
    else if(gs.menu_page == 1)
    {
      info.reshape(w,h);
    }
    else if(gs.menu_page == 2)
    {
      opt.reshape(w,h);
    }
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
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.keyboardFunction(key,x,y);
    }
    else if(gs.menu_page == 1)
    {
      info.keyboardFunction(key,x,y);
    }
    else if(gs.menu_page == 2)
    {
      opt.keyboardFunction(key,x,y);
    }
  }
  else 
  {
    lv.keyboardFunction(key,x,y);
  }
}
void skbF(int key, int x, int y)
{
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.specialKeyboardFunction(key,x,y);
    }
    else if(gs.menu_page == 1)
    {
      info.specialKeyboardFunction(key,x,y);
    }
    else if(gs.menu_page == 2)
    {
      opt.specialKeyboardFunction(key,x,y);
    }
  }
  else 
  {
    lv.specialKeyboardFunction(key,x,y);
  }
}
void mIdleF(int x, int y)
{
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.myIdleMouseFunction(x,y);
    }
    else if(gs.menu_page == 1)
    {
      info.myIdleMouseFunction(x,y);
    }
    else if(gs.menu_page == 2)
    {
      opt.myIdleMouseFunction(x,y);
    }
  }
  else 
  {
    lv.myMouseFunction(x,y);
  }
}
void mF(int btn,int state,int x, int y)
{
  if (gs.paused)
  {
    if(gs.menu_page == 0)
    {
      mn.myMouseFunction(btn,state,x,y);
    }
    else if(gs.menu_page == 1)
    {
      info.myMouseFunction(btn,state,x,y);
    }
    else if(gs.menu_page == 2)
    {
      opt.myMouseFunction(btn,state,x,y);
    }
  }
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
  gs.gs_run();
  lv.reset();
}
void run(void)
{
  gs.gs_run();
}
void gpause(void)
{
  gs.gs_pause();
}

void back(void)
{
  gs.gs_back();
}
void info_action(void)
{
  gs.gs_info_action();
}
void option_action(void)
{
  gs.gs_option_action();
}
void sound_off(void)
{
  gs.gs_sound_off();
}
void sound_on(void)
{
  gs.gs_sound_on();
}
