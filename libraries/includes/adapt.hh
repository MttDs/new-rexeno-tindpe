#ifndef ADAPT_HH_
# define ADAPT_HH_

# include <string>
# include <string.h>
# include "parser.hh"
# include "variable.hh"
# include "trial.hh"
# include "adapt.hh"
# include <GL/glut.h>

using namespace std;
using namespace configuration;

class Adapt
{
public:
  Adapt(const ShapeInfo& si,
	VariableManager& vm,
	Shape* father);
  ~Adapt();
  Variable* key(){return _key;}
  Variable* coef(){return _coef;}
  Variable* action(){return _action;}
  Shape* parent(){return _parent;}
  
private:
  Shape* _parent;
  Variable* _parentName;
  Variable* _key;
  Variable* _coef;
  Variable* _action;
};


#endif
