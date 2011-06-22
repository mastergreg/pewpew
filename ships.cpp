#include "ships.h"
#include "level.h"

extern level lv;

  game_ship::game_ship(vector pos,vector sp)
:game_object(pos)
{
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
      std::cout << *current << std::endl;
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


void game_ship::move()
{
  speed.soft_rotate();
  double x = speed.getX();
  double y = speed.getY();
  double z = speed.getZ();
  int rd = speed.getRD(); 
  int ri = speed.getRI();
  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();
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
  if (px > 0.7 ||px < -0.7) 
  {
    x*=-1;
  }
  if (py > 0.7 ||py < -0.7) 
  {
    y*=-1;
  }
  if (pz > 0.7 ||pz < -0.7) 
  {
    z*=-1;
  }
  speed.set_vector(vector(x,y,z,rd,ri));
  position.increase_vector(speed);  

}
vector game_ship::get_speed()
{
  return speed;
}
void game_ship::set_speed(vector new_speed)
{
  double x = new_speed.getX();
  double y = new_speed.getY();
  speed.set_vector(new_speed);
  if(x>=0) 
  {
    angle=atan(y/x);
  }
  else
  {
    angle=atan(y/x)+M_PI;
  }
}
void dummyship::draw()
{
  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();

  move();
  glPushMatrix();
  GLfloat mycolor[] = {0.0,1.0,0.0}; 
  GLfloat shiny[]={200.0};
  GLfloat diff[] = {0.9,0.9,0.9,0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,pz);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spinnit(),spini , spini, 1.0); 

  glutWireSphere(0.04,4,3);
  glPopMatrix(); 
}
void dummyship::die()
{
  life=-1;
}




  dummyship::dummyship(vector pos,vector sp)
:game_ship(pos,sp)
{
  life=1000;
  radius = 0.04;
}






bool game_ship::isAlive()
{
  return life>1;
}
void ship::die()
{
  lv.shipExplode(position);
}
  ship::ship()
:game_ship(vector(0,0,0,0,0),vector(0,0,0,0,0))
{
  life=50000;
  radius = 0.04;
}
vector ship::get_pos()
{
  return position;
}
void ship::draw()
{
  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();

  move();
  speed.soft_scale();
  glPushMatrix();

  GLfloat  mycolor[]={0.0,0.5,1.0};
  GLfloat shiny[]={200.0};
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,pz);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spinnit(), 0.0, 0.0, 1.0); 
  glutWireCone(0.02,0.05,4,1);
  glLineWidth(1);
  //  glColor3ub(255,255,0);
  glutWireCone(0.03,0.02,4,1);

  glPopMatrix(); 
}
int ship::getLife()
{
  return life;
}





  fire::fire(vector pos,vector sp)
:game_ship(pos,sp)
{
  life=100;
  radius=0.02;
}
void fire::move()
{
  double x = speed.getX();
  double y = speed.getY();
  double z = speed.getZ();
  int rd = speed.getRD(); 
  int ri = speed.getRI(); 
  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();
  if (px > 0.7 || px < -0.7) 
  {
    die(); 
  }
  else if (py > 0.7 ||py < -0.7) 
  {
    die();
  }
  else if (pz > 0.7 ||pz < -0.7) 
  {
    die();
  }
  speed.set_vector(vector(x,y,z,rd,ri));
  position.increase_vector(speed);  
  life--;
  if(life<1) die();
}
void fire::draw()
{

  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();

  move();
  glPushMatrix();
  GLfloat  mycolor[]={1.0,0.5,1.0};
  GLfloat shiny[]={256.0};
  GLfloat diff[] = {0.9,0.9,0.9,0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,pz);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spinnit(), 0.0, 0.0, 1.0); 
  glutWireCone(0.01,0.03,2,1);
  glPopMatrix(); 
}




void fire::die()
{
  life=-1;
}


