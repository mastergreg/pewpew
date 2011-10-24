#include "level.h"

extern level lv;

//Generic game_ship

  game_ship::game_ship(vector2D pos,vector2D sp)
:game_object(pos)
{
  spini=0;
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
  speed.set_vector(vector2D(x,y,rd,ri));
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
bool game_ship::isAlive()
{
  return life>1;
}
vector2D game_ship::get_pos()
{
  return position;
}

//DummyShips "Meteor" type
void dummyship::draw()
{
  double px = position.getX();
  double py = position.getY();

  glPushMatrix();
  GLfloat mycolor[] = {0.0,1.0,0.0}; 
  glColor3fv(mycolor);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,0);
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spini,spini , spini, 1.0); 
  glutWireSphere(0.04,4,3);
  glPopMatrix(); 
}
  dummyship::dummyship(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=1000;
  radius = 0.04;
}

void dummyship::die()
{
  game_ship::die();
  lv.insertScoreTag(position,1000);
}

//Main Ship. PlayerShip
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
  if (WeaponLevel<6)
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
std::list<fire *> ship::shoot()
{
  return shoot(angle);
}
std::list<fire *> ship::shoot(double ang)
{
  double firespeed=0.025;
  std::list<fire *> rls;
  vector2D fspeed;
  vector2D fpos(position.getX()+0.05*cos(ang),position.getY()+0.05*sin(ang),0,0);
  double dang;
  switch (WeaponLevel)
  {
    case 1:
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 2:
      dang=M_PI/16;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 3:
      dang=M_PI/6;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 4:
      dang=M_PI/6;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 5:
      dang=M_PI/12;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      break;
    case 6:
      dang=M_PI/12;
      firespeed*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      break;
    default:
      dang=M_PI/12;
      firespeed*=8;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      dang*=2;
      fspeed.set_vector(vector2D(firespeed*cos(ang-dang),firespeed*sin(ang-dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang+dang),firespeed*sin(ang+dang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      fspeed.set_vector(vector2D(firespeed*cos(ang),firespeed*sin(ang),0,0));
      rls.push_back(new fire(fpos,fspeed));
      rls.push_back(new fire(fpos,fspeed));
      break;
  }
  return rls;
}








//SpiralShip enemy


spiralShip::spiralShip(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=100000;
  radius = 0.2;
  Ttime=0;
  rot=true;

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
  lv.insertScoreTag(position,10000);
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




//Upgrades to playership
  fireUpgrade::fireUpgrade(vector2D pos)
:game_ship(pos,vector2D())
{
  life=500;
}
void fireUpgrade::draw()
{

  double px = position.getX();
  double py = position.getY();
  glPushMatrix();
  GLfloat mycolor[] = {1,0.63,0.06}; 
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


//Bullets for playership
  fire::fire(vector2D pos,vector2D sp)
:game_ship(pos,sp)
{
  life=300;
  radius=0.02;
}
void fire::move()
{
  double x = speed.getX();
  double y = speed.getY();
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
  speed.set_vector(vector2D(x,y,rd,ri));
  position.increase_vector(speed);  
  life--;
  if(life<1) die();
  spinnit();
}
void fire::draw()
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
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spini, 0.0, 0.0, 1.0);
  glutWireCone(0.01,0.03,2,1);
  glPopMatrix(); 
}

