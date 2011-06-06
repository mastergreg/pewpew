#include "peripherals.h"
double shipMouseAngle()
{
  vector pos = mship.get_pos();
  double x = pos.getX();
  double y = pos.getY();
  x=mX-x;
  y=-mY-y;
  //std::cout <<" x y = --|#>> " << x << " " << y << std::endl;
  if(x>0) 
  {
    return atan(y/x);
  }
  else if (x<0)
  {
    return atan(y/x)+M_PI;
  }
  else if (y>0)
  {
    return M_PI/2;
  }
  else 
  {
    return -M_PI/2;
  }
}
void keyboardReleaseFunction(unsigned char key,int x, int y)
{
  vector current_speed;
  current_speed.set_vector(mship.get_speed());
  switch (key)
  {
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
  
    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotate_reset();
      mship.set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
    
    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotate_reset();
      mship.set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(0.25,0.25,0.25);
      mship.set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(4,4,4);
      mship.set_speed(current_speed);
      break;
  }
}
void myMouseFunction(int x,int y)
{
  mX=3*((double(x)/WINDOW_SIZEX)-0.5);
  mY=2*((double(y)/WINDOW_SIZEY)-0.5);
}
void keyboardFunction(unsigned char key,int x,int y)
{
  vector current_speed;
  current_speed.set_vector(mship.get_speed());
  switch (key)
  {
    case 27:
      exit (0);
      break;
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.vincrease();//scale(1.2,1.2,1.2);
      mship.set_speed(current_speed);
      break;
    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotatel();
      current_speed.scale(1.01,1.01,1.01);
      mship.set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.vdecrease();//scale(0.8,0.8,0.8);
      mship.set_speed(current_speed);
      break;
    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotater();
      current_speed.scale(1.01,1.01,1.01);
      mship.set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(4,4,4);
      mship.set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(0.25,0.25,0.25);
      mship.set_speed(current_speed);
      break;
    case 'r':
      mship = *(new ship);
      vector sp(0.001,0.005,0.005,0,0);
      mship.set_speed(sp);
      break;
  }
}

