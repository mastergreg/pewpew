/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : pulse_weapon.cpp

* Purpose :

* Creation Date : 13-11-2011

* Last Modified : Mon 14 Nov 2011 10:27:24 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "pulse_weapon.h"

pulse::pulse(vector2D p,vector2D s)
    :main_weapon(p,s)
{
    life = 5000;
    radius = 0.05;
    killStep = 150;
    wfs=0.2;
    compileDraw();

}
void pulse::compileDraw()
{
    theShot = glGenLists(1);
    int i; //TODO optimize this
    glNewList(theShot,GL_COMPILE);
    glBegin(GL_POINTS);
    for(i=0; i<=90; i++)
    {
        glVertex3f(0.04*sin(i),0.008*cos(i),0);
        glVertex3f(-0.04*sin(i),0.008*cos(i),0);
        glVertex3f(0.04*sin(i),-0.008*cos(i),0);
        glVertex3f(-0.04*sin(i),-0.008*cos(i),0);
    }
    glEnd();
    glEndList();

}
void pulse::draw()
{

    double px = position.getX();
    double py = position.getY();

    glPushMatrix();
    GLfloat diff[] = {0.,1.,1};
    glColor3f(diff[0]*life/300.,diff[1]*life/300.,diff[2]*life/300.);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, diff);
    glLineWidth(1);
    glTranslatef(px,py,0);
    glRotatef(-57.29578*angle, 0.0, 0.0, 1.0);
    angle+=0.05;
    glCallList(theShot);

    glPopMatrix();
}
