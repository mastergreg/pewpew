/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : main_weapon.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Mon 14 Nov 2011 12:23:05 AM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "fire_weapon.h"

//Bullets for playership
  fire::fire(vector2D pos,vector2D sp)
:main_weapon(pos,sp)
{
  life=300;
  radius=0.02;
  compileDraw();
}
void fire::compileDraw()
{
  theShot = glGenLists(1);
  glNewList(theShot,GL_COMPILE);
  glRotatef(-90, 1.0, 0.0, 0.0); 

  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  //glRotatef(spini, 0.0, 0.0, 1.0);
  glutWireCone(0.01,0.03,2,1);
  glEndList();

}
//void fire::move()
//{
//  double x = speed.getX();
//  double y = speed.getY();
//  int rd = speed.getRD(); 
//  int ri = speed.getRI(); 
//  double px = position.getX();
//  double py = position.getY();
//  if (px > (DIMENSION-radius-0.2) || px < -(DIMENSION-radius-0.2)) 
//  {
//    die(); 
//  }
//  else if (py > (DIMENSION-radius-0.2) ||py < -(DIMENSION-radius-0.2)) 
//  {
//    die();
//  }
//  speed=(vector2D(x,y,rd,ri));
//  position.increase_vector(speed);  
//  life--;
//  if(life<1) die();
//  spinnit();
//}
void fire::draw()
{

  double px = position.getX();
  double py = position.getY();

  glPushMatrix();
  GLfloat diff[] = {1.,1.,0};
  glColor3f(diff[0]*life/300.,diff[1]*life/300.,diff[2]*life/300.);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, diff);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glCallList(theShot);

  glPopMatrix(); 
}
