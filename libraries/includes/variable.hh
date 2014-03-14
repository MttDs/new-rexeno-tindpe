#ifndef VARIABLE_HH_
# define VARIABLE_HH_

#include <vector>
#include <set>
#include <string>
using namespace std;

class Variable
{
public:
  Variable();
  Variable(string name,
	   float value);
  Variable(float value);
  Variable(string n);
  operator double ();
  operator string ();
  string name;
  double value;
};

class VariableManager
{
public:
  VariableManager();
  int getValue(string name);
  Variable* getVariable(string name);
  void printVariables();
  Variable* addVariable(Variable* v);
  bool is_in(string name);
private:
  set<Variable*>* variables;
};



#endif

