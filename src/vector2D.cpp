#include "vector2D.h"
#include <iostream>


void vector2D::increase_vector(vector2D v)
{
  x+=v.x;
  y+=v.y;
}
void vector2D::decrease_vector(vector2D v)
{
  x-=v.x;
  y-=v.y;
}
vector2D::vector2D()
{
  x=0;
  y=0;
  remaining_deg =0;
  remaining_inc = 0;
}
vector2D::vector2D(double a,double b,int rd,int ri)
{
  x=a;
  y=b;
  remaining_deg = rd;
  remaining_inc = ri;
}
void vector2D::scale(double a,double b)
{
  x=x*a;
  y=y*b;
}
void vector2D::vincrease()
{
  remaining_inc=+50;
}
void vector2D::vdecrease()
{
  remaining_inc=-50;
}
void vector2D::soft_scale()
{
  double factor=1;
  double fx = 100000*sqrt(x*x+y*y) ;
  if (fx > SPEED_MAX)
  {
    fx = SPEED_MAX-128;
  }
  else  if (fx < SPEED_MIN)
  {
    fx = SPEED_MIN+128;
  }
    if (remaining_inc > 0)
    {
      factor = fabs(1+10/fx);
    }
    else if (remaining_inc < 0)
    {
      factor = fabs(1-10/fx);
    }
  scale(factor,factor);
}
void vector2D::increase_reset()
{
  remaining_inc=0;
}
void vector2D::rotate_reset()
{
  remaining_deg=0;
}
void vector2D::soft_rotate()
{
  if (remaining_deg<0)
  {
    x=x*COS_THETA+y*SIN_THETA;
    y=-x*SIN_THETA+y*COS_THETA;
  }
  else if (remaining_deg>0)
  {
    x=x*COS_THETA-y*SIN_THETA;
    y=x*SIN_THETA+y*COS_THETA;
  }
}
void vector2D::rotater()
{
  remaining_deg=-100;
}
void vector2D::rotatel()
{
  remaining_deg=+100;
}

double vector2D::getX()
{
  return x;
}
double vector2D::getY()
{
  return y;
}
int vector2D::getRI()
{
  return remaining_inc;
}
int vector2D::getRD()
{
  return remaining_deg;
}
double vector2D::length()
{
  return sqrt(x*x+y*y);
}
double vector2D::distance(vector2D b)
{
  double px=x-b.x;
  double py=y-b.y;
  return sqrt(px*px+py*py);
}
