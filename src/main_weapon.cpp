/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : main_weapon.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Mon 14 Nov 2011 10:24:39 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "main_weapon.h"

//Bullets for playership
  main_weapon::main_weapon(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=0;
  radius=0;
  killStep=0;
  wfs=1;
  compileDraw();
}
void main_weapon::compileDraw()
{
}
void main_weapon::move()
{
  double x = speed.getX()*wfs;
  double y = speed.getY()*wfs;
  int rd = speed.getRD(); 
  int ri = speed.getRI(); 
  double px = position.getX();
  double py = position.getY();
  if (px > (DIMENSION-radius-0.2) || px < -(DIMENSION-radius-0.2)) 
  {
    die(); 
  }
  else if (py > (DIMENSION-radius-0.2) ||py < -(DIMENSION-radius-0.2)) 
  {
    die();
  }
  vector2D bufspeed=(vector2D(x,y,rd,ri));
  position.increase_vector(speed);  
  life-=killStep;
  if(life<1) die();
  spinnit();
}
void main_weapon::draw()
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
