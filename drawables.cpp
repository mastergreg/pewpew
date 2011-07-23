#include "drawables.h"



chink::chink(vector pos)
:game_object(pos)
{
  life=10;
  radius = 0.01;  
}




void chink::move()
{
  if(radius>0.03) die();
  radius +=0.0005;
}

void chink::die()
{
  life=-1;
}

void chink::draw()
{
  double x = position.getX();
  double y = position.getY();
  double z = position.getZ();
  int i=0;
  glPushMatrix();
  glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  glBegin(GL_TRIANGLE_FAN);
  GLfloat  mycolor[]={1.0,0.0,0.0};
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glVertex3f(x,y,z);
  for (;i<=360;i+=45)
  {
    glVertex3f(x+sin(i*M_PI/180)*radius,y+cos(i*M_PI/180)*radius,z);
  }
  glEnd();
  glPopMatrix();
}

  xplosion::xplosion(vector pos)
:game_object(pos)
{
  life=10;
  radius = 0.02;
}
void xplosion::move()
{
  if(radius>0.5) 
  {
    die();
  }
  radius+=0.002;
}
void xplosion::die()
{
  life=-1;
}
double xplosion::spinnit()
{
  spini = spini + 4.0;
  if (spini > 360.0) spini = spini - 360.0;
  return spini;
}
void xplosion::draw()
{
  double px = position.getX();
  double py = position.getY();
  double pz = position.getZ();

  glPushMatrix();
  GLfloat mycolor[] = {0.6,0.0,0.0}; 
  GLfloat shiny[]={200.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mycolor);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mycolor);
  glLineWidth(1);
  glTranslatef(px,py,pz);
  //glRotatef(-90, 1.0, 0.0, 0.0); 
  //glRotatef(-57.29578*angle, 0.0, 1.0, 0.0); 
  glRotatef(90, 0.0, 1.0, 0.0); 
  glRotatef(spinnit(),spini , spini, 1.0); 

  glutWireSphere(radius,8,6);
  glPopMatrix(); 
}




circle::circle(double r, vector pos,GLfloat mycolor[3])
{
  radius = r;
  position.set_vector(pos);
  color[0]=mycolor[0];
  color[1]=mycolor[1];
  color[2]=mycolor[2];
  angleStep=2*M_PI/256.;
  for(int i=0;i<32;i++)
  {
    //Define points in first quadrant
    x[i]=radius*cos(i*angleStep);
    y[i]=radius*sin(i*angleStep);
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
  
}

void circle::draw(vector pos)
{
  position.set_vector(pos);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,color);
  glTranslatef(position.getX(),position.getY(),position.getZ());
  glBegin(GL_LINE_LOOP);
  for (int i=0;i<256;i++)
  {
    glVertex3f(x[i],y[i],0);
  }
  glEnd();
  glPopMatrix();

}
void circle::move()
{
}
