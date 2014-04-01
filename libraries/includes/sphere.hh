#ifndef SPHERE_HH_
# define SPHERE_HH_

# include "shape.hh"
# include "sphereshadow.hh"

#include <GL/glut.h>
class Sphere : public Shape
{
public:
   Sphere(const ShapeInfo& si,
         VariableManager& vm,
         Trial* father);
  ~Sphere();

  void React2input(Status&,
                   const datas&,
                   int,
                   ms);

  void Display();
  void DisplayMonitor();
  void Reset();
  void RandomPosXZ();
  double z() { return _z->value; }
  float lead(){ return _lead->value;}
  string getAttrsToString();

protected:

  float _angleX;
  float _angleY;
  float _angleZ;

  float _initX;
  float _initY;
  float _initZ;

  float _angleV; 
  float RotAxe[2];
  
  Variable* _randomX;
  Variable* _randomZ;

  Variable* _slices;
  Variable* _stacks;
  Variable* _radius;

  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;

  Variable* _z;
  
  Variable* _key;
  Variable* _gain;
  Variable* _action;
  Variable* _lead;
  SphereShadow* _shadow;

};


#endif
