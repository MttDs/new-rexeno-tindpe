#include "square.hh"

using boost::lexical_cast;
using boost::bad_lexical_cast;

Square::Square(const ShapeInfo& si,
               VariableManager& vm,
               Trial* father)
{
  assert(si.attributes.size() == 10);
  _name = si.attributes[0];
  _id = 1;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[8]));

  _father = father;
}

Square::~Square()
{

}

