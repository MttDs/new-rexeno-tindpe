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
  void RandomDir();

  double z() { return _z->value; }

  string getAttrsToString();

protected:
  float _anglePos; /* deg */

  float _angleX;
  float _angleY;
  float _angleZ;

  float _initX;
  float _initY;
  float _initZ;

  bool _randomDir;

  Variable* _slices;
  Variable* _stacks;
  Variable* _radius;

  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;

  Variable* _z;
  Variable* _dirX;
  Variable* _dirZ;
  SphereShadow* _shadow;

};


#endif
