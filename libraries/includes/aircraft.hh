#ifndef AIRCRAFT_HH_
# define AIRCRAFT_HH_

# include <GL/glut.h>

# include "shape.hh"
# include "3ds.hh"

class Aircraft : public Shape
{
public:
  Aircraft(const ShapeInfo& si,
	   VariableManager& vm,
	   Trial* t);
  ~Aircraft();

  void Display();
  string getAttrsToString();
  
protected:
  
  Variable* _z;
  Variable* _veloX;
  Variable* _dir;
  CLoad3DS _load3ds;
  C3DModel _model3ds;
  bool _isTextured;
};
#endif
