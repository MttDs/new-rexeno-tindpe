#ifndef ADAPT_HH_
# define ADAPT_HH_


# include <GL/glew.h>
# include <GL/freeglut.h>

# include <string>
# include <string.h>
# include "parser.hh"
# include "variable.hh"
# include "trial.hh"
# include "adapt.hh"
using namespace std;
using namespace configuration;

class Adapt
{
public:
  Adapt(VariableManager& vm,
	Shape* father,
	int key, 
	float coef,
	std::string gain);
  ~Adapt();
  Variable* key(){return _key;}
  Variable* coef(){return _coef;}
  string action(){return _action;}
  Shape* parent(){return _parent;}
  string getAttrsToString();
private:
  Shape* _parent;
  Variable* _parentName;
  Variable* _key;
  Variable* _coef;
  string _action;
};


#endif
