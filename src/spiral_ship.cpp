/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : spiral_ship.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sun 06 Nov 2011 07:11:23 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#include "spiral_ship.h"
//SpiralShip enemy


spiralShip::spiralShip(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=10000;
  radius = 0.2;
  Ttime=0;
  rot=true;
  points = 10000;

  /*
  double r = 1;
  double angleStep=2*M_PI/256.;
  double x[256],y[256];
  for(int i=0;i<32;i++)
  {
    //Define points in first quadrant
    x[i]=r*cos(i*angleStep);
    y[i]=r*sin(i*angleStep);
    x[64-1-i]=y[i];
    y[64-1-i]=x[i];
    
    //Define points in second quadrant

    x[64+i]=-y[i];
    y[64+i]=x[i];
    x[2*64-1-i]=-x[i];
    y[2*64-1-i]=y[i];
    //Define points in third quadrant
    x[2*64+i]=-x[i];
    y[2*64+i]=-y[i];
    x[3*64-1-i]=-y[i];
    y[3*64-1-i]=-x[i];
    //Define points in fourth quadrant
    x[3*64+i]=y[i];
    y[3*64+i]=-x[i];

    x[4*64-1-i]=x[i];
    y[4*64-1-i]=-y[i];
   } 
   for(int i=0;i<255;i++)
   {
     pattern.push_back(new vector2D(x[i+1]-x[i],y[i+1]-y[i],0,0,0));
   }
   */

}
void spiralShip::die()
{
  life=-1;
}

void spiralShip::draw()
{
  glPushMatrix();
  glLineWidth(1);
  GLfloat spiralShipColor[]={1,0,0};
  glColor3fv(spiralShipColor);
  glTranslatef(position.getX(),position.getY(),0);
  glRotatef(57.29578*angle-90, 0.0, 0.0, 1.0); 
  glRotatef(spini, 0.0, 1.0, 0.0); 
  glBegin(GL_LINE_LOOP);
    glVertex3f(0,0.2,0);
    glVertex3f(-0.2,-0.2,0.2);
    glVertex3f(0,0,0.1);
    glVertex3f(0.2,-0.2,0.2);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glVertex3f(0,0.2,0);
    glVertex3f(-0.2,-0.2,-0.2);
    glVertex3f(0,0,-0.01);
    glVertex3f(0.2,-0.2,-0.2);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glVertex3f(0.2,-0.2,0.2);
    glVertex3f(0.1,0,0);
    glVertex3f(0.2,-0.2,-0.2);
  glEnd();
  glBegin(GL_LINE_STRIP);
    glVertex3f(-0.2,-0.2,0.2);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.2,-0.2,-0.2);
  glEnd();
  glPopMatrix();
  for_each(tail.begin(),tail.end(),draw_all);


}


void spiralShip::move()
{
  GLfloat tailColor[3]={0,0.5,0.1};
  if(Ttime>10)
  {
    tail.push_back(new big_ship_tail(position,angle,tailColor));
    Ttime=0;
  }
  Ttime++;
  std::list<game_object *>::iterator iter = tail.begin();
  for(;iter!=tail.end();iter++)
  {
    if ((*iter)->get_life()<0)
    {
      delete *iter;
      *iter = NULL;
    }
  }
  tail.remove(NULL);
  for_each(tail.begin(),tail.end(),move_all);
  game_ship::move();
  speed.rotate_reset();
  if(rot)
  {
    speed.rotater();
    rot=false;
  }
  else
  {
    rot=true;
  }
  double sx=speed.getX();
  double sy=speed.getY();
  if((sx*sx+sy*sy)<0.001)
  {
    speed.scale(3,2);
  }
}
