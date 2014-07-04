 /*
  * SphereShadow.h
  *
  *  Created on: Dec 17, 2013
  *      Author: xeno1
  */

#ifndef SPHERESHADOW_H_
#define SPHERESHADOW_H_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include <string>
# include <iostream>
class SphereShadow{
public:
  SphereShadow(float rdius, float ps, int stcks, bool actve);
  ~SphereShadow();
  void Display();
  void initTexture();

  void setStacks(int stcks);
  void setRadius(float rdius);
  void setPos(float x, float y, float z);
  void setActive(bool b);

  bool active();
private:

  bool _active;

  int _stacks;

  float _radius;
  float _pos;

  double _x;
  double _y;
  double _z;

};


#endif /* SPHERESHADOW_H_ */
