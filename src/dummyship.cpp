/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : dummyship.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sun 06 Nov 2011 07:10:33 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "dummyship.h"

//DummyShips "Meteor" type
void dummyship::draw()
{
  double px = position.getX();
  double py = position.getY();

  glPushMatrix();
  GLfloat mycolor[] = {0.0,1.0,0.0}; 
  glColor3fv(mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spini,spini , spini, 1.0); 
  glutWireSphere(0.04,4,3);
  glPopMatrix(); 
}
  dummyship::dummyship(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=1000;
  radius = 0.04;
  points = 1000;
}

void dummyship::die()
{
  game_ship::die();
  //lv.insertScoreTag(position,1000);
}

