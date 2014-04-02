#include "adapt.hh"

Adapt::Adapt(const ShapeInfo& si,
	     VariableManager& vm,
	     Shape* father){
  assert(si.attributes.size() == 4);

  vm.addVariable(_parentName = new Variable(si.attributes[0]));
  vm.addVariable(_key = new Variable(si.attributes[1]));
  vm.addVariable(_coef = new Variable(si.attributes[2]));
  vm.addVariable(_action = new Variable(si.attributes[3]));
  _parent = father;
}

Adapt::~Adapt(){

}
