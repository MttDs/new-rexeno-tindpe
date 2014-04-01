
#include "sphere.hh"
#include "imageload.hh"
#include <GL/glut.h>
#include <trial.hh>

#include "recorder.hh"
#include "setup.hh"

using boost::lexical_cast;
using boost::bad_lexical_cast;
class Trial;

Sphere::Sphere(const ShapeInfo& si,
	       VariableManager& vm,
	       Trial* father)
{
  assert(si.attributes.size() == 18);

  _name = si.attributes[0];
  _id = 7;

  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_z = new Variable(si.attributes[3]));
  vm.addVariable(_randomX = new Variable(si.attributes[4]));
  vm.addVariable(_randomZ = new Variable(si.attributes[5])); 
  vm.addVariable(_frameStart = new Variable(si.attributes[6]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[7]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_stacks = new Variable(si.attributes[8]));
  vm.addVariable(_slices = new Variable(si.attributes[9]));
  vm.addVariable(_radius = new Variable(si.attributes[10]));
  vm.addVariable(_veloX = new Variable(si.attributes[11]));
  vm.addVariable(_veloY = new Variable(si.attributes[12]));
  vm.addVariable(_veloZ = new Variable(si.attributes[13]));
  vm.addVariable(_key = new Variable(si.attributes[14]));
  vm.addVariable(_gain = new Variable(si.attributes[15]));
  vm.addVariable(_action = new Variable(si.attributes[16]));
  vm.addVariable(_lead = new Variable(si.attributes[17]));

  _session = NULL;

  _angleX = 0.0f;
  _angleV = 0.0f;
  _angleY = 0.0f;
  _angleZ = 0.0f;

  _initX = *_x;
  _initY = *_y;
  _initZ = *_z;

  _father = father;

  SphereShadow* s = new SphereShadow(*_radius, *_z, *_stacks, true);
  _shadow = s;

  RandomPosXZ();
}

Sphere::~Sphere()
{
  gluDeleteQuadric(_params);
  delete _shadow;
}

void
Sphere::React2input(Status& s,
		    const datas& ds,
		    int frameId,
		    ms displayTime)
{
  if (_session == NULL){
    _session = _father->session();
  }
  int fps = _session->getFrequency();
  string str;
  ostringstream ostr;

  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
    {
      _logged = true;

      ostr << _name << " start " << lexical_cast<string>(displayTime) << " Pos [" << RoundNdecimal(2,_x->value) << ", " << RoundNdecimal(2,_y->value) << ", " << RoundNdecimal(2,_z->value) <<"]";
      str = ostr.str();
      _session->recorder->Save(str, "events.txt");
    }

  // Saving of shape disparation
  if ((frameId == frameEnd()) && (!_loggedEnd))
    {
      ostr << _name << " end " << lexical_cast<string>(displayTime) << " Pos [" << RoundNdecimal(2,_x->value) << ", " << RoundNdecimal(2,_y->value) << ", " << RoundNdecimal(2,_z->value) <<"]";
      str = ostr.str();
      _session->recorder->Save(str, "events.txt");
      _loggedEnd = true;
    }
  _session->recorder->Save(_name + "\n" + lexical_cast<string>(_x->value) + "\n" + lexical_cast<string>(_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  _session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
 
  float veloV = sqrt((*_veloX)*(*_veloX)+(*_veloZ)*(*_veloZ));
  float moveV = veloV/fps;

  _angleV+= moveV/ *_radius*180.0 / M_PI;

  float OrientV=atan2((*_veloZ),(*_veloX));
  float OrientRot=OrientV-(M_PI/2.0);
  
  RotAxe[0]=cos(OrientRot);
  RotAxe[1]=sin(OrientRot);

  //  printf("Orient V: %f\t moveV: %f\t angleV: %f\t RotAxe: [%f,%f]\n",OrientV,moveV,_angleV,RotAxe[0],RotAxe[1]);

  *_x = *_x+(moveV*cos(OrientV));
  *_z = *_z+(moveV*sin(OrientV));
}

void
Sphere::Display()
{

  if (this->IsTextured() == false){
    ImageLoad iload;
    iload.setFilename("sphere.bmp");
    if(!(iload.load())){
      exit(1);
    }

    this->initTexture(iload.getSizeY(), iload.getSizeX(), iload.getData());

    int spec[4] = {1,1,0,1};
    int light[4] = {0,0,4,0};

    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 2);
    glLightiv(GL_LIGHT0, GL_POSITION, light);

    _params = gluNewQuadric();
    gluQuadricDrawStyle(_params,GLU_FILL);
    gluQuadricTexture(_params ,GL_TRUE);
  }

  glPushMatrix();

  glEnable( GL_TEXTURE_2D );

  glBindTexture(GL_TEXTURE_2D, _texture[0]);
  
  glTranslatef(*_x,*_radius+*_y,*_z);
  glRotatef(_angleV,RotAxe[0],0,RotAxe[1]);
  
  glRotated(90.0f,1,0,0);
  gluSphere(_params, *_radius, *_stacks, *_slices);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable( GL_TEXTURE_2D );

  glPopMatrix();

  _shadow->setPos(*_x, *_y, *_z);
  _shadow->Display();
}

void
Sphere::Reset(){

  _angleX = 0.0;
  _angleY = 0.0;
  _angleZ = 0.0;

  *_x = _initX;
  *_y = _initY;
  *_z = _initZ;

  RandomPosXZ();

  _logged = false;
  _loggedEnd = false;

}

void
Sphere::DisplayMonitor()
{

}

string
Sphere::getAttrsToString(){
  if (_session == NULL){
    _session = _father->session();
  }
  string str;
  int fps = _session->getFrequency();
  float move = *_veloX/fps;
  float angleX = (move / *_radius*180.0 / M_PI);
  move = *_veloY/fps;
  float angleY = (move / *_radius*180.0 / M_PI);
  move = *_veloZ/fps;
  float angleZ = (move / *_radius*180.0 / M_PI);
  ostringstream ostr;
  ostr <<  _name << ": Radius ["
       << *_radius << "] Velocity [" << *_veloX << ", " << *_veloY <<", " << *_veloZ <<"] Angle ["
       <<RoundNdecimal(2,angleX)
       <<", "
       <<RoundNdecimal(2,angleY)
       <<", "
       <<RoundNdecimal(2,angleZ) <<"]";
  str = ostr.str();
  return str;
}


void 
Sphere::RandomPosXZ(){
   if (_randomX->value != 0){
   _x->value =  _getRandomNumber(_initX, _randomX->value);
  }
  if (_randomZ->value != 0){
    _z->value = _getRandomNumber(_initZ, _randomZ->value);
  }
}
