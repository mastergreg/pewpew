/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : pulse_weapon.cpp

* Purpose :

* Creation Date : 13-11-2011

* Last Modified : Mon 14 Nov 2011 12:28:02 AM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "pulse_weapon.h"

pulse::pulse(vector2D p,vector2D s)
:main_weapon(p,s)
{
  life = 500;
  radius = 0.05;
  compileDraw();

}
void pulse::compileDraw()
{
  theShot = glGenLists(1);
  int i; //TODO optimize this
  glNewList(theShot,GL_COMPILE);
  glBegin(GL_POINTS);
  for(i=0;i<=360;i++)
  {
    glVertex3f(0.06*sin(i),0.01*cos(i),0);
  }
  glEnd();
  glEndList();

}
void pulse::draw()
{

  double px = position.getX();
  double py = position.getY();

  glPushMatrix();
  GLfloat diff[] = {0.,1.,1};
  glColor3f(diff[0]*life/300.,diff[1]*life/300.,diff[2]*life/300.);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, diff);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glCallList(theShot);

  glPopMatrix(); 
}
