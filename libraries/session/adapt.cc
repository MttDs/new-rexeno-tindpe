#include "adapt.hh"

Adapt::Adapt(VariableManager& vm,
	     Shape* father,
	     int key, 
	     float coef,
	     std::string gain){

  vm.addVariable(_key = new Variable(key));
  vm.addVariable(_coef = new Variable(coef));
  vm.addVariable(_action = new Variable(gain));
  _parent = father;
}

Adapt::~Adapt(){

}
