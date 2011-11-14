/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : game_ship.cpp

* Purpose :

* Creation Date : 05-11-2011

* Last Modified : Sun 06 Nov 2011 07:08:07 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#include "game_ship.h"

  game_ship::game_ship(vector2D pos,vector2D sp)
:game_object(pos)
{
  spini=0;
  points = 0;
  set_speed(sp);
}
double game_ship::spinnit()
{
  spini = spini + 4.0;
  if (spini > 360.0) spini = spini - 360.0;
  return spini;
}

void game_ship::die()
{
  life=-1;
}
std::list<game_object *> game_ship::collisions(std::list<game_ship *> lst)
{
  std::list<game_object *> newDrawableList;
  std::list<game_ship *>::iterator current = lst.begin();
  while(current != lst.end())
  {
    if (collides(*current))
    { 
      life=life-(*current)->get_life(); 
      if (life>1)
      {
        (*current)->die();
      }
      else
      {
        (*current)->set_life(-life);
        die();
      }
      newDrawableList.push_back(new chink(position));
    }
    current++;
  }
  return newDrawableList;
}

double game_ship::get_angle()
{
  return angle;
}

void game_ship::set_angle(double newAngle)
{
  double length = speed.length();
  double newX = length*cos(newAngle);
  double newY = length*sin(newAngle);
  speed = vector2D(newX,newY,speed.getRD(),speed.getRI());
  angle = newAngle;
}


void game_ship::move()
{
  speed.soft_scale();
  speed.soft_rotate();
  double x = speed.getX();
  double y = speed.getY();
  int rd = speed.getRD(); 
  int ri = speed.getRI();
  double px = position.getX();
  double py = position.getY();
  if(x>0) 
  {
    angle=atan(y/x);
  }
  else if (x<0)
  {
    angle=atan(y/x)+M_PI;
  }
  else
  {
    angle=0;
  }
  if (px > (DIMENSION-radius-0.2) ||px < -(DIMENSION-radius-0.2)) 
  {
    x*=-1;
  }
  if (py > (DIMENSION-radius-0.2) ||py < -(DIMENSION-radius-0.2)) 
  {
    y*=-1;
  }
  speed=vector2D(x,y,rd,ri);
  position.increase_vector(speed);  
  spinnit();

}
vector2D game_ship::get_speed()
{
  return speed;
}
void game_ship::set_speed(vector2D new_speed)
{
  double x = new_speed.getX();
  double y = new_speed.getY();
  speed=(new_speed);
  if(x>=0) 
  {
    angle=atan(y/x);
  }
  else
  {
    angle=atan(y/x)+M_PI;
  }
}
bool game_ship::isAlive()
{
  return life>1;
}
vector2D game_ship::get_pos()
{
  return position;
}

int game_ship::get_points()
{
  return points;
}
