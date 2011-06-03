#include <GL/glut.h>
#include <iostream>
#include "ships.h"
#include "peripherals.h"
#include "drawFunctions.h"
#define DT 0.01

//accumulator buffer
using namespace std;
      ship mship;
      vector sp(0.001,0.005,0.005,0,0);

      vector esp(0.001,0.005,0.005,0,0);
      vector pos(-0.5,0,0.5,0,0);
      list<game_ship *> fireList;
      list<game_ship *> enemyList;
      list<game_object *> drawableList;
      int WINDOW_SIZEX;
      int WINDOW_SIZEY;
      double mX,mY;



void display()
{
  static int time = 0;
  static int ftime=0;
  glClearColor(0,0,0,0);
  {
    GLfloat  mycolor[]={0.0,1.0,0.0};
    GLfloat shiny[]={200.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  }
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  glLineWidth(5);
  {
    GLfloat  mycolor[]={1.0,0.0,0.0};
    GLfloat shiny[]={200.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  }
  glutWireCube(1.5);
  //draw life rectangle
  glDisable(GL_LINE_STIPPLE);

  if (mship.isAlive()) 
  {
  glLineWidth(10);
  int mlife = mship.getLife();
  glBegin(GL_LINES);
    GLfloat  my1color[]={0.0,1.0,0.0};
    GLfloat shiny[]={200.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,my1color);
  glVertex3f(-0.9,0.8,0);  
    GLfloat  mycolor[]={1.0,0.0,0.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glVertex3f(mlife/20000.0-0.9,0.8,0);  
  glEnd();
    mship.collisions(enemyList);
    mship.draw();
    if (ftime==10)
    {
      ftime=0;
      double firespeed=0.015;
      double angle = shipMouseAngle();
      vector fspeed(firespeed*cos(angle),firespeed*sin(angle),0,0,0);
      fire * bullet = new fire(mship.get_pos(),fspeed);
      drawableList.push_back(bullet);
      fireList.push_back(bullet);
    }
  }
  collisionDetect(fireList,enemyList);
  drawDrawableList(drawableList);
  drawEnemyList(enemyList);
  glutSwapBuffers();
  usleep(10000);
  time++;
  ftime++;
  if (time==100)
  {
    time=0;
    enemyList.push_back(new dummyship(pos,esp));
  }
}
void reshape(int w,int h)
{
  GLsizei minSize=w>h ? (GLsizei) h : (GLsizei) w;
  
  GLsizei startX=((w-h)/2.0);
  if (startX>0)
  {
    glViewport(startX,0,minSize,minSize);
  }
  else
  {
    glViewport(0,-startX,minSize,minSize);
  }
  gluOrtho2D(-1.0,1.0,-1.0,1.0);
  WINDOW_SIZEX=w;
  WINDOW_SIZEY=h;
}



int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(800,600);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutCreateWindow("A sample OpenGL application");
  WINDOW_SIZEX=800;
  WINDOW_SIZEY=600;
  mship.set_speed(sp);
  //insert enemy to enemy list
  //for collision detection
  //  glMatrixMode(GL_PROJECTION);
  //
  //  gluOrtho2D(-3,3,-3,3);

  glEnable(GL_LIGHTING);
  //glEnable(GL_BLEND);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHT0);
  GLfloat specular[] = {1.0f, 1.0f, 1.0f , 0.5f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  GLfloat diff[] = {0.9,0.9,0.9,0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  /*  glLightfv(GL_LIGHT0,GL_POSITION,);
      glLightfv(GL_LIGHT0,GL_);
      glLightfv(GL_LIGHT0,GL_);
      glLightfv(GL_LIGHT0,GL_);
      glLightfv(GL_LIGHT0,GL_);
      */
  //glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
  //glEnable(GL_COLOR_MATERIAL);
  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  //glEnable(GL_LINE_SMOOTH);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(glutPostRedisplay);
  glutKeyboardUpFunc(keyboardReleaseFunction);
  glutKeyboardFunc(keyboardFunction);
  glutPassiveMotionFunc(myMouseFunction);
  glutMainLoop();

  return 0;
}

