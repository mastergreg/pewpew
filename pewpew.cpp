#include <GL/glut.h>
#include <iostream>
#include "ships.h"
#include "vector.h"
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
void drawEnemyList(std::list<game_ship *> lst)
{
  std::list<game_ship*>::iterator p=lst.begin();
  while(p != lst.end())
  {  
    (*p)->draw();
    p++;
  }
}

void drawDrawableList(std::list<game_object *> lst)
{
  std::list<game_object *>::iterator p=lst.begin();
  while(p != lst.end())
  {  
    (*p)->draw();
    p++;
  }
}

void collisionDetect(std::list<game_ship *> bullets,std::list<game_ship *> enemies)
{
  std::list<game_ship *>::iterator enemy = enemies.begin();
  
  while (enemy !=enemies.end())
  {
    (*enemy)->collisions(bullets);
    enemy++;
  }
}

double shipMouseAngle()
{
  vector pos = mship.get_pos();
  double x = pos.getX();
  double y = pos.getY();
  x=mX-x;
  y=-mY-y;
  //std::cout <<" x y = --|#>> " << x << " " << y << std::endl;
  if(x>0) 
  {
    return atan(y/x);
  }
  else if (x<0)
  {
    return atan(y/x)+M_PI;
  }
  else if (y>0)
  {
    return M_PI/2;
  }
  else 
  {
    return -M_PI/2;
  }
}
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



void keyboardreleasefunction(unsigned char key,int x, int y)
{
  vector current_speed;
  current_speed.set_vector(mship.get_speed());
  switch (key)
  {
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
  
    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotate_reset();
      mship.set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
    
    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotate_reset();
      mship.set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(0.25,0.25,0.25);
      mship.set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(4,4,4);
      mship.set_speed(current_speed);
      break;
  }
}
void myMouseFunction(int x,int y)
{
  mX=3*((double(x)/WINDOW_SIZEX)-0.5);
  mY=2*((double(y)/WINDOW_SIZEY)-0.5);
}
void keyboardfunction(unsigned char key,int x,int y)
{
  vector current_speed;
  current_speed.set_vector(mship.get_speed());
  switch (key)
  {
    case 27:
      exit (0);
      break;
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.vincrease();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotatel();
      current_speed.scale(1.01,1.01,1.01);
      mship.set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.vdecrease();//scale(0.8,0.8,0.8);
      mship.set_speed(current_speed);
      break;
    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotater();
      current_speed.scale(1.01,1.01,1.01);
      mship.set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(4,4,4);
      mship.set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(0.25,0.25,0.25);
      mship.set_speed(current_speed);
      break;
  }
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
  glutKeyboardUpFunc(keyboardreleasefunction);
  glutKeyboardFunc(keyboardfunction);
  glutPassiveMotionFunc(myMouseFunction);
  glutMainLoop();

  return 0;
}

