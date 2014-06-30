#ifndef SPHERE_HH_
# define SPHERE_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include "shape.hh"
# include "sphereshadow.hh"

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
  void CompParam(bool init=false);
  double z() { return _z->value; }
  string getAttrsToString();
  
protected:

  float _angleX;
  float _angleY;
  float _angleZ;

  float _initX;
  float _initY;
  float _initZ;

  float _angleV;
  float _moveV;
  float _orientV;
  float RotAxe[2];
  
  Variable* _randomX;
  Variable* _randomZ;

  Variable* _slices;
  Variable* _stacks;
  Variable* _radius;

  Variable* _z;

  SphereShadow* _shadow;

};


#endif
