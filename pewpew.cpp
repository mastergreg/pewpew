#include "level.h"
//accumulator buffer
level lv;
void display()
{
  lv.play();
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
  glutInitWindowPosition(50,50);
  glutInitWindowSize(800,600);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutCreateWindow("PewPew");
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHT0);
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

