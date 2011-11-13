/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : player_ships.cpp

* Purpose :

* Creation Date : 20-12-2008

* Last Modified : Mon 14 Nov 2011 12:32:23 AM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "player_ships.h"


//Main Ship. PlayerShip
//
  ship::ship()
:game_ship(vector2D(0,0,0,0),vector2D(0,0,0,0))
{
  GLfloat mycolor[]={0.,0.26,1.};
  UpgradeCirc = new circle(0.05,position,mycolor);
  WeaponLevel=1;
  life=5000;
  Ttime=0;
  radius = 0.04;
}
  ship::~ship()
{
  delete UpgradeCirc;
}
void ship::draw()
{
  double px = position.getX();
  double py = position.getY();

  speed.soft_scale();
  glPushMatrix();

  GLfloat  mycolor[]={0.54,0.16,0.86};
  glColor3fv(mycolor);
  glLineWidth(1);
  glTranslatef(px-0.02*cos(angle),py-0.02*sin(angle),0);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spini, 0.0, 0.0, 1.0); 
  glutWireCone(0.02,0.05,4,1);
  glutWireCone(0.03,0.02,4,1);

  glPopMatrix(); 
  for_each(tail.begin(),tail.end(),draw_all);
}
void ship::move()
{
  game_ship::move();
  GLfloat tailColor[3]={1,0.,0.};
  if(Ttime>12)
  {
    tail.push_back(new ship_tail(position,angle,tailColor));
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
}
void ship::downgradeWeapons()
{
  if(WeaponLevel>1) WeaponLevel--;
}
void ship::upgradeWeapons()
{
  if (WeaponLevel<=6)
    WeaponLevel++;
}
void ship::collectFireUpgrades(std::list<game_ship *> upgrades)
{
  std::list<game_ship *>::iterator it=upgrades.begin();
  while(it!=upgrades.end())
  {
    if( collides((game_object *)*it)) 
    {

      upgradeWeapons(); 
      (*it)->die();
    }
    it++;
  }

}
void ship::collectLifeUpgrades(std::list<game_ship *> upgrades)
{
  std::list<game_ship *>::iterator it=upgrades.begin();
  while(it!=upgrades.end())
  {
    if( collides((game_object *)*it)) 
    {

      life+=(*it)->get_life(); 
      (*it)->die();
    }
    it++;
  }

}
void ship::drawUPArrow(game_ship * upgrade,GLfloat color[])
{
  double UX=upgrade->get_pos().getX();
  double UY=upgrade->get_pos().getY();
  double X=position.getX();
  double Y=position.getY();
  glPushMatrix();
  GLfloat  mycolor[3];
  std::copy(color,color+3,mycolor);
  //GLfloat shiny[]={0.0};
  glColor3fv(mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mycolor);
  glLineWidth(1);
  //glTranslatef(0.02*cos(angle),0.02*sin(angle),0);
  //glTranslatef(X,Y,0);
  double upgradeShipAngle;
  double ax=(UX-X);
  double ay=(UY-Y);
  if(ax>0) 
  {
    upgradeShipAngle=atan(ay/ax);
  }
  else if (ax<0)
  {
    upgradeShipAngle=atan(ay/ax)+M_PI;
  }
  else if (ay>0)
  {
    upgradeShipAngle=M_PI/2;
  }
  else 
  {
    upgradeShipAngle=-M_PI/2;
  }
  glTranslatef(X,Y,0);
  glTranslatef(0.05*cos(upgradeShipAngle),0.05*sin(upgradeShipAngle),0);
  glRotatef(-90, 1.0, 0.0, 0.0);
  glRotatef(-57.29578*upgradeShipAngle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(45, 0.0, 0.0, 1.0); 
  glutWireCone(0.01,0.02,4,1);
  glPopMatrix(); 
}
void ship::drawUpgradeRing(std::list<game_ship *> fireUpgradeList,std::list<game_ship *> lifeUpgradeList)
{
  GLfloat  FUcolor[]={1.0,0.63,0.06};
  GLfloat  LUcolor[]={1.0,0.,0.};
  UpgradeCirc->draw(position);
  std::list<game_ship *>::iterator FUit=fireUpgradeList.begin();
  while(FUit!=fireUpgradeList.end())
  {
    drawUPArrow(*FUit,FUcolor);
    FUit++;
  }
  std::list<game_ship *>::iterator LUit=lifeUpgradeList.begin();
  while(LUit!=lifeUpgradeList.end())
  {
    drawUPArrow(*LUit,LUcolor);
    LUit++;
  }
}
std::list<main_weapon *> ship::shoot()
{
  return shoot(angle);
}
std::list<main_weapon *> ship::shoot(double ang)
{
  double firespeed=0.025;
  std::list<main_weapon *> rls;
  vector2D fspeed;
  vector2D fpos(position.getX()+0.05*cos(ang),position.getY()+0.05*sin(ang),0,0);
  double dang;
  switch (WeaponLevel)
  {
    case 1:
      fspeed=(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 2:
      dang=M_PI/16;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 3:
      dang=M_PI/6;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 4:
      dang=M_PI/6;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 5:
      dang=M_PI/12;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    default:
      dang=M_PI/12;
      firespeed*=4;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed=(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed=(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
  }
  return rls;
}



void ship::accelerate()
{
  speed.vincrease();
}
void ship::decelerate()
{
  speed.vdecrease();
}
void ship::release_acc()
{
  speed.increase_reset();
}
void ship::release_rot()
{
  speed.rotate_reset();
}
void ship::turn_right()
{
  speed.rotater();
  speed.scale(1.01,1.01); //reduce error of calc
}
void ship::turn_left()
{
  speed.rotatel();
  speed.scale(1.01,1.01); //reduce error of calc
}
void ship::turbo_boost()
{
  speed.scale(4,4);
}
void ship::e_brake()
{
  speed.scale(0.25,0.25);
}





