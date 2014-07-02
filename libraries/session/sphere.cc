# include <GL/glew.h>
# include <GL/freeglut.h>

#include "sphere.hh"
#include "imageload.hh"
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

  assert(si.attributes.size() == 14);

  _name = si.attributes[0];
  _id = 7;
  vm.addVariable(_minStart = new Variable(si.attributes[1]));
  vm.addVariable(_maxStart = new Variable(si.attributes[2]));
  vm.addVariable(_x = new Variable(si.attributes[3]));
  vm.addVariable(_y = new Variable(0));
  vm.addVariable(_z = new Variable(si.attributes[4]));
  vm.addVariable(_randomX = new Variable(si.attributes[5]));
  vm.addVariable(_randomZ = new Variable(si.attributes[6])); 
  vm.addVariable(_frameStart = new Variable(si.attributes[7]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[8]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_stacks = new Variable(si.attributes[9]));
  vm.addVariable(_slices = new Variable(si.attributes[10]));
  vm.addVariable(_radius = new Variable(si.attributes[11]));
  vm.addVariable(_veloX = new Variable(si.attributes[12]));
  vm.addVariable(_veloZ = new Variable(si.attributes[13]));
  
  vm.addVariable(_veloY = new Variable(0));

  _initFrameStart = _frameStart->value;
  _initFrameEnd = _frameEnd->value;

  Adapt* adapt;
  for (unsigned int it = 0; it< si.listeners.size();it++){
    adapt = new Adapt(vm,
		      this,
		      si.listeners[it].key, 
		      si.listeners[it].coef, 
		      si.listeners[it].gain);
    _adapts.push_back(adapt);
  }
  _session = NULL;

  _angleX = 0.0f;
  _angleV = 0.0f;
  _angleY = 0.0f;
  _angleZ = 0.0f;

  _moveV = 0.0f;
  _orientV = 0.0f;

  _initX = *_x;
  _initY = *_y;
  _initZ = *_z;
  
  _gainV = 1.0;
  _gainD = 1.0;

  _father = father;

  SphereShadow* s = new SphereShadow(*_radius, *_z, *_stacks, true);
  _shadow = s;

  _textureName = "sphere.bmp";
  RandomPosXZ();
  CompParam(1);

  _session = NULL;
}

Sphere::~Sphere()
{
  gluDeleteQuadric(_params);
  delete _shadow;
}

void Sphere::CompParam(bool init)
{
  if (_session == NULL){
    _session = _father->session();
  }

  if (init==0)
    {
      int fps = (_session->setup)->refreshRate();

      float veloV = _gainV * sqrt((*_veloX)*(*_veloX)+(*_veloZ)*(*_veloZ));
      _moveV = veloV/fps;
      
      float temp = _angleV+_moveV/ *_radius*180.0 / M_PI;
      if (temp>360.0){
	_angleV = temp - _angleV;
      }
      else{
	_angleV = temp;
      }
    }
  
  _orientV=atan2((*_veloZ),(*_veloX));

  float OrientRot=_orientV-(M_PI/2.0);

  RotAxe[0]=cos(OrientRot);
  RotAxe[1]=sin(OrientRot);
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
  int fps = (_session->setup)->refreshRate();

  //  printf("Orient V: %f\t moveV: %f\t angleV: %f\t RotAxe: [%f,%f]\n",OrientV,moveV,_angleV,RotAxe[0],RotAxe[1]);

  ostringstream ostr;

  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
  {
      float move = *_veloX/fps;
      float angleX = (move / *_radius*180.0 / M_PI);
      move = *_veloZ/fps;
      float angleZ = (move / *_radius*180.0 / M_PI);

      _logged = true;
      // name 'start' time frameStart x z angleX angleZ angleV veloX veloZ gainV gainD 

      ostr << _name 
	   << " start " << lexical_cast<string>(displayTime) 
	   << " " << _frameStart->value
	   << " " << RoundNdecimal(4, _x->value)
	   << " " << RoundNdecimal(4, _z->value)
	   << " " << angleX
	   << " " << angleZ
	   << " " << RoundNdecimal(2,_angleV)
	   << " " << *_veloX
	   << " " << *_veloZ
	   << " " << _gainV
	   << " " << _gainD;
  
      _session->recorder->Save(ostr.str(), "events.txt");
   
    }

  // Saving of shape disparation
  if ((frameId == frameEnd()) && (!_loggedEnd))
    {
      // end name time frameEnd x z

      ostr << _name 
	   << " end " << lexical_cast<string>(displayTime) 
	   << " " << _frameEnd->value
	   << " " << RoundNdecimal(4, _x->value)
	   << " " << RoundNdecimal(4, _z->value)
	   << " " << _angleV;

      _session->recorder->Save(ostr.str(), "events.txt");
      _loggedEnd = true;
    }

  _session->recorder->Save(_name + "\n" + lexical_cast<string>(_x->value) + "\n" + lexical_cast<string>(_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

  _session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");

  CompParam(0);

  _x->value = _x->value+(_moveV*cos(_orientV));
  _z->value = _z->value+(_moveV*sin(_orientV));

}

void 
Sphere::initTexture(){
  
  Shape::initTexture();

  int spec[4] = {1,1,0,1};
  int light[4] = {0,0,4,0};
  
  glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 2);
  glLightiv(GL_LIGHT0, GL_POSITION, light);

  _params = gluNewQuadric();
  gluQuadricDrawStyle(_params,GLU_FILL);
  gluQuadricTexture(_params ,GL_TRUE);
}
void
Sphere::Display()
{
  glPushMatrix();

  glEnable(GL_TEXTURE_2D);

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

  Shape::Reset();
}

void
Sphere::DisplayMonitor()
{

}

string
Sphere::toString(){

  if (_session == NULL){
    _session = _father->session();
  }

  double fps = (_session->setup)->refreshRate();
  float move = *_veloX/fps;
  float angleX = (move / *_radius*180.0 / M_PI);
  move = *_veloZ/fps;
  float angleZ = (move / *_radius*180.0 / M_PI);

  ostringstream ostr;

  ostr <<  _name << ": "
       << "Pos["
       << _x->value << ", "
       << _z->value 
       << "] Radius ["
       << *_radius << "] Velocity [" 
       << *_veloX << ", " 
       << *_veloZ <<"] Angle ["
       << RoundNdecimal(2,angleX)
       << ", "
       << RoundNdecimal(2,angleZ) 
       <<"]"
       << " Frame start "
       << _frameStart->value
       << " Frame end " 
       << _frameEnd->value
       << " Random apparition ["
       << _minStart->value
       << ", "
       << _maxStart->value
       << "]";

  return  ostr.str();
}


void 
Sphere::RandomPosXZ(){
   if (_randomX->value != 0){
   _x->value =  _getRandomNumber(_initX, _randomX->value);
  }
  if (_randomZ->value != 0){
    _z->value = _getRandomNumber(_initZ, _randomZ->value);
  }
  _angleV = ((float) rand()/RAND_MAX)*360.0;
}
