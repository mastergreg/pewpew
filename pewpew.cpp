#include "level.h"

level lv;

void display()
{
  //Draw();
  lv.display();
}
void reshape(int w,int h)
{
  lv.reshape(w,h);
}
void kbRelF(unsigned char key, int x, int y)
{
  lv.keyboardReleaseFunction(key,x,y);
}
void kbF(unsigned char key, int x, int y)
{
  lv.keyboardFunction(key,x,y);
}
void mF(int x, int y)
{
  lv.myMouseFunction(x,y);
}


int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1024,768);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutCreateWindow("PewPew");
  //glEnable(GL_LIGHTING);
  glEnable(GL_BLEND);
  //glShadeModel(GL_SMOOTH);
  //glEnable(GL_LIGHT0);
  glMatrixMode(GL_PROJECTION);

  //GLfloat filter[11] = {0.3,0.28,0.26,0.24,0.22,0.20,0.22,0.24,0.26,0.28,0.3};	//GOOD
  //glSeparableFilter2D(GL_SEPARABLE_2D, GL_LUMINANCE, 11, 11, GL_LUMINANCE, GL_FLOAT, filter,filter); //<< segfault !!!

  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(glutPostRedisplay);
  glutKeyboardUpFunc(kbRelF);
  glutKeyboardFunc(kbF);
  glutPassiveMotionFunc(mF);
  glutMainLoop();

  return 0;
}

