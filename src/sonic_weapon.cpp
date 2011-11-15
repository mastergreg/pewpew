/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sonic_weapon.cpp

* Purpose :

* Creation Date : 14-11-2011

* Last Modified : Mon 14 Nov 2011 10:52:25 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "sonic_weapon.h"

sonic::sonic(vector2D p,vector2D s)
:main_weapon(p,s)
{
  life = 50000;
  radius = 0.05;
  killStep = 2000;
  wfs=0.001;
  compileDraw();

}
void sonic::compileDraw()
{
  theShot = glGenLists(1);
  double i; //TODO optimize this
  glNewList(theShot,GL_COMPILE);
  glBegin(GL_POINTS);
  for(i=0;i<70;i++)
  {
    //glVertex3f(0.04*sin(i),0.008*cos(i),0);
    glVertex3f(0.08*sin(i*M_PI/180),0.05*cos(i*M_PI/180),0);
    glVertex3f(-0.08*sin(i*M_PI/180),0.05*cos(i*M_PI/180),0);
  }
  glEnd();
  glEndList();

}
void sonic::draw()
{

  double px = position.getX();
  double py = position.getY();

  glPushMatrix();
  GLfloat diff[] = {1.,0.,1};
  glColor3f(diff[0]*life/300.,diff[1]*life/300.,diff[2]*life/300.);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glRotatef(57.29578*angle-90, 0.0, 0.0, 1.0); 
  //angle+=0.05;
  glCallList(theShot);

  glPopMatrix(); 
}
