/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : upgrades.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Mon 14 Nov 2011 09:51:53 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "upgrades.h"


//Upgrades to playership
  fireUpgrade::fireUpgrade(vector2D pos,int wT)
:game_ship(pos,vector2D())
{
  life=500;
  WeaponType = wT;
}
void fireUpgrade::draw()
{

  double px = position.getX();
  double py = position.getY();
  glPushMatrix();
  GLfloat mycolor[3];
  GLfloat color1[3]={1,0.63,0.06};
  GLfloat color2[3]={0,1,1};
  GLfloat color3[3]={1,0,1};
  switch (WeaponType)
  {  
    case 0:
      std::copy(color1,color1+3,mycolor);
      break;
    case 1:
      std::copy(color2,color2+3,mycolor);
      break;
    case 2:
      std::copy(color3,color3+3,mycolor);
      break;
    default:
      std::copy(color1,color1+3,mycolor);
      break;
  }
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
int fireUpgrade::getType()
{
  return WeaponType;
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


