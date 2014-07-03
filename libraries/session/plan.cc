#include "plan.hh"

# include <GL/glew.h>
# include <GL/freeglut.h>

Plan::Plan(const ShapeInfo& si,
	   VariableManager& vm,
	   Trial* father)
{

  assert(si.attributes.size() == 10);
  _name = si.attributes[0];
  _id = 1;
  vm.addVariable(_minStart = new Variable(si.attributes[1]));
  vm.addVariable(_maxStart = new Variable(si.attributes[2]));
  vm.addVariable(_x = new Variable(si.attributes[3]));
  vm.addVariable(_y = new Variable(si.attributes[4]));
  vm.addVariable(_z = new Variable(0));
  vm.addVariable(_frameStart = new Variable(si.attributes[5]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[6]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_width = new Variable(si.attributes[7]));
  vm.addVariable(_height = new Variable(si.attributes[8]));
  vm.addVariable(_repeat = new Variable(si.attributes[9]));
  _father = father;

  _initFrameStart = _frameStart->value;
  _initFrameEnd = _frameEnd->value;

  _gainD = 1.0;
  _gainV = 1.0;

  _textureName = "damier.bmp";

  _session = NULL;
}

Plan::~Plan(){

}

void Plan::Display(){

  glEnable( GL_TEXTURE_2D );
  glBindTexture(GL_TEXTURE_2D, _texture[0]);
  glTranslated(_x->value,(_y->value-0.01),_z->value);
  glBegin(GL_QUADS);

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);glVertex3f(-*_height,0.0f, -*_width);
  glTexCoord2i(*_repeat,0.0f);glVertex3f(*_height,0.0f, -*_width);
  glTexCoord2i(*_repeat,*_repeat);glVertex3f(*_height,0.0f, *_width);
  glTexCoord2i(0.0f,*_repeat);glVertex3f(-*_height,0.0f, *_width);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable( GL_TEXTURE_2D );

}
string
Plan::toString(){
  ostringstream ostr;
  ostr << _name 
       << ": Width "
       << _width->value 
       << " Height "
       << _height->value << " Pos ["
       << _x->value 
       << ", "
       << _y->value 
       << "] Repeat Texture "
       << _repeat->value;
  return ostr.str();
}

void
Plan::Reset(){
  Shape::Reset();
}
