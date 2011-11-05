/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : upgrades.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sat 05 Nov 2011 08:12:57 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "upgrades.h"


//Upgrades to playership
  fireUpgrade::fireUpgrade(vector2D pos)
:game_ship(pos,vector2D())
{
  life=500;
}
void fireUpgrade::draw()
{

  double px = position.getX();
  double py = position.getY();
  glPushMatrix();
  GLfloat mycolor[] = {1,0.63,0.06}; 
  glColor3fv(mycolor);
  //GLfloat diff[] = {0.,0.,0.}; 
  //GLfloat shiny[]={0.0};
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glRotatef(45, 1.0, 1.0, 0.0); 
  glRotatef(spini,0,1, 1.0); 
  glutWireSphere(0.02,4,3);
  glPopMatrix(); 
}
void fireUpgrade::move()

{
  spinnit();
  life--;
}

  lifeUpgrade::lifeUpgrade(vector2D pos)
:game_ship(pos,vector2D())
{
  life=500;
}
void lifeUpgrade::draw()
{

  double px = position.getX();
  double py = position.getY();
  glPushMatrix();
  GLfloat mycolor[] = {1,0.,0.}; 
  glColor3fv(mycolor);
  //GLfloat diff[] = {0.,0.,0.}; 
  //GLfloat shiny[]={0.0};
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glRotatef(45, 1.0, 1.0, 0.0); 
  glRotatef(spini,0,1, 1.0); 
  glutWireSphere(0.02,4,3);
  glPopMatrix(); 
}
void lifeUpgrade::move()

{
  spinnit();
}



