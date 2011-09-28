#include "vector.h"
#include <iostream>
void vector::set_vector(vector v)
{
  x=v.x;
  y=v.y;
  remaining_deg=v.remaining_deg;
  remaining_inc=v.remaining_inc;
}
void vector::increase_vector(vector v)
{
  x+=v.x;
  y+=v.y;
}
vector::vector()
{
  x=0;
  y=0;
  remaining_deg =0;
  remaining_inc = 0;
}
vector::vector(double a,double b,int rd,int ri)
{
  x=a;
  y=b;
  remaining_deg = rd;
  remaining_inc = ri;
}
void vector::scale(double a,double b)
{
  x=x*a;
  y=y*b;
}
void vector::vincrease()
{
  remaining_inc+=50;
}
void vector::vdecrease()
{
  remaining_inc-=50;
}
void vector::soft_scale()
{
  double factor=1;
  double fx = 100000*sqrt(x*x+y*y) ;
  if (fx<SPEED_MAX && fx>SPEED_MIN)
  {
    if (remaining_inc > 0)
    {
      factor = fabs(1+10/fx);
      remaining_inc--;
    }
    else if (remaining_inc < 0)
    {
      factor = fabs(1-10/fx);
      remaining_inc++;
    }
    scale(factor,factor);
  }
}
void vector::increase_reset()
{
  remaining_inc=0;
}
void vector::rotate_reset()
{
  remaining_deg=0;
}
void vector::soft_rotate()
{
  if (remaining_deg<0)
  {
    remaining_deg++;
    x=x*COS_THETA+y*SIN_THETA;
    y=-x*SIN_THETA+y*COS_THETA;
  }
  else if (remaining_deg>0)
  {
    remaining_deg--;
    x=x*COS_THETA-y*SIN_THETA;
    y=x*SIN_THETA+y*COS_THETA;
  }
}
void vector::rotater()
{
  remaining_deg-=100;
}
void vector::rotatel()
{
  remaining_deg+=100;
}

double vector::getX()
{
  return x;
}
double vector::getY()
{
  return y;
}
int vector::getRI()
{
  return remaining_inc;
}
int vector::getRD()
{
  return remaining_deg;
}
double vector::length()
{
  return sqrt(x*x+y*y);
}
double vector::distance(vector b)
{
  double px=x-b.x;
  double py=y-b.y;
  return sqrt(px*px+py*py);
}
