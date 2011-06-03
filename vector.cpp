#include "vector.h"
#include <iostream>
void vector::set_vector(vector v)
{
  x=v.x;
  y=v.y;
  z=v.z;
  remaining_deg=v.remaining_deg;
  remaining_inc=v.remaining_inc;
}
void vector::increase_vector(vector v)
{
  x+=v.x;
  y+=v.y;
  z+=v.z;
}
vector::vector()
{
  x=0;
  y=0;
  z=0;
  remaining_deg =0;
  remaining_inc = 0;
}
vector::vector(double a,double b,double c,int rd,int ri)
{
  x=a;
  y=b;
  z=c;
  remaining_deg = rd;
  remaining_inc = ri;
}
void vector::scale(double a,double b, double c)
{
  x=x*a;
  y=y*b;
  z=z*c;
}
void vector::vincrease()
{
  remaining_inc+=100;
}
void vector::vdecrease()
{
  remaining_inc-=100;
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
    scale(factor,factor,factor);
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
double vector::getZ()
{
  return z;
}
int vector::getRI()
{
  return remaining_inc;
}
int vector::getRD()
{
  return remaining_deg;
}
double vector::distance(vector b)
{
  double px=x-b.x;
  double py=y-b.y;
  return sqrt(px*px+py*py);
}
