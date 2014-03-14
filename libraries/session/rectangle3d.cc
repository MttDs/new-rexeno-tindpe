#include "rectangle3d.hh"
#include <boost/lexical_cast.hpp>
#include "imageload.hh"

#include <GL/glut.h>
using namespace boost;

Rectangle3d::Rectangle3d(const ShapeInfo& si,
			 VariableManager& vm,
			 Trial* father)
{
  assert(si.attributes.size() == 13);
  assert(father);
  _name = si.attributes[0];
  //vm.addVariable(_id = new Variable(2));
  //std::cout << id() << endl;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_z = new Variable(si.attributes[3]));
  vm.addVariable(_frameStart = new Variable(si.attributes[4]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[5]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_width = new Variable(si.attributes[6]));
  vm.addVariable(_height = new Variable(si.attributes[7]));
  vm.addVariable(_deep = new Variable(si.attributes[8]));
  vm.addVariable(_velo = new Variable(si.attributes[9]));
  vm.addVariable(_repeat = new Variable(si.attributes[10]));
  vm.addVariable(_dir = new Variable(si.attributes[11]));
  vm.addVariable(_pos = new Variable(si.attributes[12]));
  _ttl = lexical_cast<int>(si.attributes[10]);

  _father = father;

  _initX = *_x;
  _initY = *_y;
  _initZ = *_z;

}

void
Rectangle3d::Display(){

  double move;
  switch((int)*_dir){
  case 1 :
    move = *_velo/60;
    _x->value = (_x->value+move);
    break;
  case 2 :
    move = *_velo/60;
    _x->value = (_x->value-move);
    break;
  case 3 :
    move = *_velo/60;
    _z->value = (_z->value-move);
    break;
  case 4 :
    move = *_velo/60;
    _z->value = (_z->value-move);
    break;
  default:
    move = *_velo/60;
    _x->value = (_x->value+move);
    break;

  }

  switch((int)*_pos){
  case 1 :
    glRotated(45,0,1,0);
    break;
  case 2 :

    break;
  default:
    break;
  }

  float x = *_height;
  float y = *_deep;
  float z = *_width;

  glTranslated(_x->value,_y->value+y,_z->value);
  if (this->IsTextured() == false){

    ImageLoad iload;

    iload.setFilename("caisse.bmp");
    if(!(iload.load())){
      exit(1);
    }
    this->initTexture(iload.getSizeY(), iload.getSizeX(), iload.getData());
  }

  glEnable( GL_TEXTURE_2D );
  glBindTexture(GL_TEXTURE_2D, _texture[0]);

  glBegin(GL_QUADS);

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(x   , y   , z  );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(x   , y   , -z );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(-x  , y   , -z  );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(-x  , y   , z  );

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(x  , -y  , z  );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(x  , -y  , -z );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(x  , y    , -z );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(x  , y    , z  );

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(-x  , -y   , z );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(-x  , -y   , -z );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(x   , -y   , -z );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(x   , -y   , z  );

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(-x  , y   , z );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(-x  , y   , -z );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(-x   , -y   , -z );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(-x   , -y   , z  );

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(x  , y   , -z  );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(x  , -y   , -z  );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(-x   , -y   , -z  );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(-x   , y   , z   );

  glNormal3f(0.0f,0.0f,1.0f);

  glTexCoord2i(0.0f,0.0f);          glVertex3f(x  , -y   , z );
  glTexCoord2i(*_repeat,0.0f);      glVertex3f(x  , y   , z );
  glTexCoord2i(*_repeat,*_repeat);  glVertex3f(-x   , y   , z );
  glTexCoord2i(0.0f,*_repeat);      glVertex3f(-x   , -y   , z  );
  
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable( GL_TEXTURE_2D );
}
void
Rectangle3d::DisplayMonitor(){

}
void
Rectangle3d::React2input(Status& s,
			 datas& ds,
			 int frameId,
			 ms displayTime)
{
  Shape::React2input(s, ds, frameId, displayTime);
}

void
Rectangle3d::Reset(){
  _x->value = _initX;
  _y->value = _initY;
  _z->value = _initZ;

  _logged = false;
  _loggedEnd = false;
}
Rectangle3d::~Rectangle3d()
{

}
