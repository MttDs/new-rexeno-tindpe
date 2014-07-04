/*
 * SphereShadow.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: xeno1
 */

#include "sphereshadow.hh"

#include <math.h>
#include <stdio.h>

SphereShadow::SphereShadow(float rdius, float ps, int stcks, bool actve)
  : 
  _active(actve),
  _stacks(stcks),
  _radius(rdius),
  _pos(ps) 
{

}
SphereShadow::~SphereShadow()
{

}

void 
SphereShadow::Display()
{

  if (active()){

    glPushMatrix();

    float angh = 2*M_PI/_stacks;
    float prec[3] = {_radius, 0, 0};
    int ii=0;

    glTranslated(_x,0,_z);

    glDisable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);

    for (ii=0; ii<=_stacks; ii++){

      float pts[3] = {_radius*cos(angh*ii), _radius*sin(angh*ii), 0};
      glColor4f(0.0f,0.0f,0.0f,0.9f);
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(pts[0],0.0f,pts[1]);
      glVertex3f(prec[0],0.0f, prec[1]);

      prec[0] = pts[0];
      prec[1] = pts[1];
      prec[2] = pts[2];

    }

    glEnd();

    glEnable(GL_LIGHTING); 
    glPopMatrix();
  }
}

void 
SphereShadow::setRadius(float rdius)
{
  _radius = rdius;
}
void 
SphereShadow::setPos(float x, float y, float z)
{
  _x = x;
  _y = y;
  _z = z;
}
void
SphereShadow::setStacks(int stcks)
{
  _stacks = stcks;
}

void
SphereShadow::setActive(bool b)
{
  _active = b;
}

bool
SphereShadow::active()
{
  return _active;
}


