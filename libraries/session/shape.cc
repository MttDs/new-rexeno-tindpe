#include "shape.hh"
#include <GL/glut.h>
#include <boost/lexical_cast.hpp>
#include "session.hh"

#include "recorder.hh"
#include "trial.hh"
#include "setup.hh"

using boost::lexical_cast;

/** 
 * Displays the shape on the subject screen
 * 
 */
void
Shape::Display()
{
  double xGL = _xGL();
  double yGL = _yGL();
  double demi_horizontal = _demiHorizontal();
  double demi_vertical = _demiVertical();
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex3d(xGL-demi_horizontal, yGL-demi_vertical,0.f);
  glVertex3d(xGL+demi_horizontal, yGL-demi_vertical,0.f);
  glVertex3d(xGL+demi_horizontal, yGL+demi_vertical,0.f);
  glVertex3d(xGL-demi_horizontal, yGL+demi_vertical,0.f);
  glEnd();
  glEnable(GL_LIGHTING);
}

/** 
 * Displays the shape on the monitor screen (experimentator side)
 * 
 */
void
Shape::DisplayMonitor()
{
  Display();
}

/** 
 * Indicate if the shape should appear at the given frame
 * 
 * @param frameId : frame number. 0 for first frame
 * 
 * @return true if the shape should be displayed,
 * else 0
 */
bool
Shape::Displayable(int frameId)
{
  bool res = true;

  res &= (frameId >= frameStart()) || (frameStart() == -1);
  res &= (frameId <= frameEnd()) || (frameEnd() == -1);
  /*   std::cout << "shape "
	    << name() 
	    << " is displayable: " 
	    << res << " start " 
	    << frameStart() 
	    << " end " 
	    << frameEnd() 
	    << " frameId "
	    << frameId
	    << std::endl;*/

  return res;
}

/** 
 * Checks if the given shape won't appear on the
 * subjects (because of too large coodonates)
 * side if one attempts to display it on the monitor screen
 * 
 * 
 * @return true if is safe to draw,
 * else 0
 */
bool
Shape::MonitorDisplayable()
{
  return ((*_x + *_width / 2) < 1);
}

/** 
 * 
 * FOR OPENGL COORD USAGE :
 * returns the length of the vertical dimension
 * 
 * @return the opengl length adapted to the screen
 */
double
Shape::_demiVertical()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double demi_vertical = xRatio * *_width / 2;
  return (demi_vertical);
}

/** 
 * FOR OPENGL COORD USAGE :
 * returns the length of the vertical dimension
 * 
 * @return the opengl length adapted to the screen
 */
double
Shape::_demiHorizontal()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double demi_horizontal = yRatio * *_height / 2;
  return (demi_horizontal);
}

/** 
 * 
 * FOR OPENGL COORD USAGE
 * 
 * @return the x value adapted to the screen
 */
double
Shape::_xGL()
{
  Session* s = Session::getInstance();
  double xRatio = s->setup->xRatio();
  double xGL = *_x * xRatio / 2;
  return xGL;
}

/** 
 * 
 * FOR OPENGL COORD USAGE
 * 
 * @return the y value adapted to the screen
 */
double
Shape::_yGL()
{
  Session* s = Session::getInstance();
  double yRatio = s->setup->yRatio();
  double yGL = *_y * yRatio;
  return yGL;
}

/** 
 * This function represents the possibility to affect the outcome of
 * a trial according to what is in ds by changing mainly it's paramenters
 * 
 * @param s : the current status of the trial (WRONG, CORRECT, ...)
 * @param ds : (Eye) data extracted from the analog input
 * @param frameId : current frame we are on
 * @param displayTime : what date (in milliseconds) was the frame presented
 */
void
Shape::React2input(Status& s,
                   const datas& ds,
                   int frameId,
                   ms displayTime)
{

  Session* session = Session::getInstance();
  ostringstream ostr;

  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
    {
      // name time x y
      _logged = true;
      ostr << _name << " start "
	   << lexical_cast<string>(displayTime) 
	   << " " 
	   << _x->value 
	   << " " 
	   << _y->value;
      session->recorder->Save(ostr.str(), "events.txt");
    }
  // Saving of shape disparation
  if ((frameId == frameEnd()) && (!_loggedEnd))
    {
      ostr << _name << " end " 
	   << lexical_cast<string>(displayTime) 
	   << " "
	   << _x->value 
	   << " " 
	   << _y->value;
      session->recorder->Save(ostr.str(), "events.txt");
      _loggedEnd = true;
    }

  session->recorder->Save(_name + "\n" + lexical_cast<string>(this->_x->value) + "\n" + lexical_cast<string>(this->_y->value) + "\n" + lexical_cast<string>(displayTime), "square_targets.txt");

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
}

void
Shape::initTexture(int sizeX, int sizeY, char * data){

  glGenTextures(1, &this->_texture[0]);// Donne numero de texture
  glBindTexture(GL_TEXTURE_2D, this->_texture[0]); //Selectionne la texture

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(
	       GL_TEXTURE_2D,		//Type de texture
	       0,					//Mipmap : aucun
	       3,					//Couleurs: 4
	       sizeY,					//Largeur: 2
	       sizeX,					//Hauteur: 2
	       0,					//Largeur des bords: 0
	       GL_RGB,			//RGBA format
	       GL_UNSIGNED_BYTE,	//Type des couleurs
	       data			//Adresse de l'image
	       );

  if (_texture[0] != 0){
    _istexured = true;
  }
  else{
    printf("ERROR ! Impossible d'appliquer la texture!");
    exit(0);
  }
}

void
Shape::Reset(){
 
  _logged = false;
  _loggedEnd = false;

  _frameStart->value = _initFrameStart;
  int value = ((float)(_initFrameEnd) * _gainD);

  _frameEnd->value = lexical_cast<int>(value);

  int frameAdapt = random2params(lexical_cast<int>(_minStart->value),
				 lexical_cast<int>(_maxStart->value)); 
  _adaptFrame(frameAdapt);


}


string
Shape::getAttrsToString(){
  string s;
  ostringstream ostr;
  ostr << _name << ": Width "<< *_width <<" Height "<<*_height << " Pos ["<< *_x <<", "<< *_y <<"] RGB ["<<*_R<<", "<<*_G<<", "<<*_B<<"]";
  s = ostr.str();
  return s;
}

double
Shape::RoundNdecimal(int n, float nb){
  int i, res = 1;

  for (i=0;i<n;i++){
    res *= 10;
  }

  return floor((nb*res+0.5)/res*100)/100;
}


int
Shape::random2params(int min, int max){
  /* 
  std::ostringstream oss;

  oss << rand();
  unsigned int sum, ii;
  std::string result = oss.str();
  const char* chars = result.c_str();

  for(ii=0; ii < strlen(chars); ii++){
	sum += (int) chars[ii]*2;
  }
  */
  int seed = (int) (std::time(0)); //(std::time(0)+sum);
  srand(seed);
  
  if (max-min>0){
    return rand()%((max+1) - min) + min;
  }
  
  return 0;
}

float 
Shape::_getRandomNumber(float pos, float nb){
  std::ostringstream oss;

  oss << rand();
  std::string result = oss.str();
  const char* chars = result.c_str();

  unsigned int i = 0, sum = 0, tmp = 0;
  int seed = 0;
  float min = (float) (pos-(nb));
  float max = (float) (pos+(nb));
  float newPos = 0.0;

  if (max<min){
    tmp = max;
    max = min;
    min = tmp;
  }

  for(i=0; i < strlen(chars); i++){
    sum += (int) chars[i]*2;
  }

  seed = (int)(std::time(0)+sum);
  srand(seed);

  newPos = (rand() * (max - min) / RAND_MAX) + min;
  newPos = newPos;

  return RoundNdecimal(2,newPos);
}

/*
Add adapts in "k" (k = pAdapts (Trial::DisplayFrame))
 */
void
Shape::setAdapts(vector<Adapt*>*k){
  vector<Adapt*>::iterator it;
  for (it = _adapts.begin(); it!= _adapts.end(); it++){
    (*k).push_back(*it);
  }
}

void 
Shape::updateVelo(double coef){
  _gainV = _gainV * (coef); 
}

void
Shape::updateDuration(double coef){
  _gainD = _gainD * (coef);
}

void
Shape::_adaptFrame(int frame){
  _frameStart->value = lexical_cast<int>(_frameStart->value)+frame;
  _frameEnd->value = lexical_cast<int>(_frameEnd->value)+frame;
}

/**
 * Abstract Constructor : inits some bool values
 *
 */
Shape::Shape()
{
  _id = 0;
  _texture[1] = 0;
  _istexured = false;
  _logged = false;
  _loggedEnd = false;
  _subjectVisible = true;
  _start = false;
}


