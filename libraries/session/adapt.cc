#include "adapt.hh"

Adapt::Adapt(VariableManager& vm, Shape* father, int key, float coef, std::string action)
{

  vm.addVariable(_key = new Variable(key));
  vm.addVariable(_coef = new Variable(coef));

  _action = action;
  _parent = father;
}

Adapt::~Adapt(){

}

string 
Adapt::toString()
{
   ostringstream ostr;
   ostr << "Adapt " 
	<< _parent->name() 
	<< " key " 
	<< _key->value 
	<< " coef " 
	<< _coef->value 
	<< " action " 
	<< _action;
   
   return ostr.str();
}
