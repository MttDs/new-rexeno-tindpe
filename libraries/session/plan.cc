#include "plan.hh"
#include "imageload.hh"

# include <GL/glut.h>
Plan::Plan(const ShapeInfo& si,
	   VariableManager& vm,
	   Trial* father)
{
  assert(si.attributes.size() == 8);
  _name = si.attributes[0];
  _id = 1;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_z = new Variable(0));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_width = new Variable(si.attributes[5]));
  vm.addVariable(_height = new Variable(si.attributes[6]));
  vm.addVariable(_repeat = new Variable(si.attributes[7]));
  _father = father;
}
Plan::~Plan(){

}

void Plan::Display(){

  if (this->IsTextured() == false){
    ImageLoad iload;
    iload.setFilename("damier.bmp");
    if(!(iload.load())){
      exit(1);
    }
    this->initTexture(iload.getSizeY(), iload.getSizeX(), iload.getData());
  }

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
Plan::getAttrsToString(){

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

