/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sonic_weapon.cpp

* Purpose :

* Creation Date : 14-11-2011

* Last Modified : Wed 16 Nov 2011 02:26:01 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "sonic_weapon.h"

sonic::sonic(vector2D p,vector2D s)
    :main_weapon(p,s)
{
    life = 50000;
    internal_radius = 0.05;
    radius = internal_radius;
    killStep = 1000;
    wfs=0.001;

    compileDraw();

}
void sonic::compileDraw()
{
    theShot = glGenLists(1);
    double i; //TODO optimize this
    glNewList(theShot,GL_COMPILE);
    glBegin(GL_POINTS);
    for(i=0; i<70; i++)
    {
        //glVertex3f(0.04*sin(i),0.008*cos(i),0);
        glVertex3f(2*internal_radius*sin(i*M_PI/180),internal_radius*cos(i*M_PI/180),0);
        glVertex3f(-2*internal_radius*sin(i*M_PI/180),internal_radius*cos(i*M_PI/180),0);
    }
    glEnd();
    glEndList();

}
void sonic::move()
{
    double x = speed.getX()*wfs;
    double y = speed.getY()*wfs;
    int rd = speed.getRD();
    int ri = speed.getRI();
    double px = position.getX();
    double py = position.getY();
    if (px > (DIMENSION-internal_radius-0.2) || px < -(DIMENSION-internal_radius-0.2))
    {
        die();
    }
    else if (py > (DIMENSION-internal_radius-0.2) ||py < -(DIMENSION-internal_radius-0.2))
    {
        die();
    }
    vector2D bufspeed=(vector2D(x,y,rd,ri));
    position.increase_vector(speed);
    internal_radius+=0.005;
    radius = internal_radius;
    compileDraw();
    life-=killStep;
    if(life<1) die();
    spinnit();
}
void sonic::draw()
{

    double px = position.getX();
    double py = position.getY();

    glPushMatrix();
    GLfloat diff[] = {1.,0.,1};
    glColor3f(diff[0]*life/300.,diff[1]*life/300.,diff[2]*life/300.);
    glLineWidth(1);
    glTranslatef(px-internal_radius*cos(angle),py-internal_radius*sin(angle),0);
    glRotatef(57.29578*angle-90, 0.0, 0.0, 1.0);
    //angle+=0.05;
    glCallList(theShot);

    glPopMatrix();
}
