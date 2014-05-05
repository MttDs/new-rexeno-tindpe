#ifndef PLAN_HH_
# define PLAN_HH_

# include <GL/glut.h>

# include "rectangle.hh"

class Plan : public Rectangle
{
public:
  Plan(const ShapeInfo& si,
       VariableManager& vm,
       Trial* t);
  ~Plan();
  void Display();
  void Reset();
  string getAttrsToString();
protected:
  Variable* _repeat; // texture
  Variable* _z;
};
#endif
