#include "variable.hh"
#include <stdlib.h>
#include <iostream>

Variable::Variable() :
  name(""),
  value(0)
{
  
}

Variable::Variable(float v) : 
  name(""),
  value(v)
{

}

Variable::Variable(string n,
		   float v) :
  name(n),
  value(v)
{
}

Variable::Variable(string n) :
  name(n),
  value(0)
{
  if ((n.c_str()[0] == '-') || (isdigit(n.c_str()[0])))
  {
    value = (atof(n.c_str ()));
    name = "";
  }
}

bool
VariableManager::is_in(string n)
{
  set<Variable*>::iterator i;
  
  i = variables->begin();
  for (; i != variables->end(); ++i)
    {
      if ((*i)->name == n)
	return (true);
    }
  return (false);
}

void
VariableManager::printVariables()
{
  set<Variable*>::iterator i;
  
  i = variables->begin();
  for (; i != variables->end(); ++i)
    {
      cout << (*i)->name << " = " << (*i)->value << endl;
    }
}

Variable::operator double()
{
  return(value);
}

Variable::operator string()
{
  return(name);
}

VariableManager::VariableManager()
{
  variables = new set<Variable*>;
}

Variable*
VariableManager::addVariable(Variable* v)
{
  if (v == NULL)
    return NULL;
  if (v->name == "")
    return v;
  if (is_in(*v))
    {
      Variable* old_v = getVariable(v->name);
      if (v->value == 0)
	return old_v;
      else
	old_v->value = v->value;
      return old_v;
    }
  variables->insert(v);
  return v;
}

int
VariableManager::getValue(string n)
{
  set<Variable*>::iterator i;

  i = variables->begin();
  for(; i != variables->end(); ++i)
    {
      if ((*i)->name == n)
	return ((*i)->value);
    }
  return (-1);
}

Variable*
VariableManager::getVariable(string n)
{
  set<Variable*>::iterator i;

  i = variables->begin();
  for(; i != variables->end(); ++i)
    {
      if ((*i)->name == n)
	return ((*i));
    }
  return (NULL);
}
