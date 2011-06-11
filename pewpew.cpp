#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include "ships.h"
#include "peripherals.h"
#include "drawFunctions.h"
#define DT 0.01

//accumulator buffer
using namespace std;
ship mship;
vector sp(0.001,0.005,0.005,0,0);
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

vector esp(0.001,0.005,0.005,0,0);
vector pos(-0.5,0,0.5,0,0);
list<game_ship *> fireList;
list<game_ship *> enemyList;
list<game_object *> drawableList;
int WINDOW_SIZEX;
int WINDOW_SIZEY;
double mX,mY;

void output(double x, double y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) 
  {
    glutBitmapCharacter(font, string[i]);
  }
}


void show_score(int score)
{
  char c_score[20];
  sprintf(c_score,"%d",score);
  output(0.8,0.9,c_score);
}

void display()
{
  int enemie_before;
  int enemie_after;
  static int enemie_killed =0 ;
  static int score = 0;
  static int time = 0;
  static int ftime=0;
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  //glPushMatrix();

  glLineWidth(5);
  GLfloat  mycolor[]={1.0,0.0,0.0};
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glutWireCube(1.5);
  //draw life rectangle
  glDisable(GL_LINE_STIPPLE);

  enemie_before = (int) enemyList.size();
  collisionDetect(fireList,enemyList);
  enemie_after = (int) enemyList.size();
  enemie_killed+=enemie_before-enemie_after;
  if (enemie_killed > 1)
  {
    enemie_killed = 0;
    mship.set_life(mship.get_life()+50);
    score+=10;
  }
  show_score(score);
  if (mship.isAlive()) 
  {
    glLineWidth(10);
    int mlife = mship.getLife();
    glBegin(GL_LINES);
    GLfloat  my1color[]={0.0,1.0,0.0};
    GLfloat shiny[]={100.0};
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
  else 
  {
    enemie_killed =0 ;
    score = 0;           
    time = 0;
    ftime=0;     
  }
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
  //GLfloat specular[] = {1.0f, 1.0f, 1.0f , 0.5f};
  //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  //GLfloat diff[] = {0.9,0.9,0.9,0};
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
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

