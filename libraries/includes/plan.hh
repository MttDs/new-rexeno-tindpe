#ifndef PLAN_HH_
# define PLAN_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include <boost/lexical_cast.hpp>
# include "rectangle.hh"
using namespace boost;
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
