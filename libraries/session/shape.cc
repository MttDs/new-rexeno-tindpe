
# include <GL/glew.h>
# include <GL/freeglut.h>

# include <boost/lexical_cast.hpp>
# include "session.hh"
# include "imageload.hh"
# include "recorder.hh"
# include "trial.hh"
# include "setup.hh"
# include "shape.hh"

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
  double demi_horizontal =  _demiHorizontal();
  double demi_vertical = _demiVertical();

  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
  glColor4ub(*_R,*_G,*_B, (int)(*_opacity*255));
  glVertex3d(xGL-demi_horizontal, yGL-demi_vertical, *_z);
  glVertex3d(xGL+demi_horizontal, yGL-demi_vertical, *_z);
  glVertex3d(xGL+demi_horizontal, yGL+demi_vertical, *_z);
  glVertex3d(xGL-demi_horizontal, yGL+demi_vertical, *_z);
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
  double ratio = _session->setup->ratio();
  double demi_vertical = ratio * *_width / 2;
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
  double ratio = _session->setup->ratio();
  double demi_horizontal = ratio * *_height / 2;
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
  double ratio = _session->setup->ratio();
  double xGL = *_x * ratio / 2 ;
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
  double ratio = _session->setup->ratio();
  double yGL = (*_y * ratio/2)+(*_height/2.0*ratio);
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
  /*  if (_session==NULL){
    _session = _father->session();
    }*/
  ostringstream ostr;
 
  // Saving of shape apparition
  if ((frameId == frameStart()) && (!_logged))
    {      // name time frameId
      _displayStart = displayTime;
      _logged = true;
      ostr << _name << " start "
	   << lexical_cast<string>(displayTime)
	   << " " 
	   << frameId
	   << " " ;
      _session->recorder->Save(ostr.str(), "events.txt");
    }
  // Saving of shape disparation

  if ((frameId == frameEnd()) && (!_loggedEnd))
    {
      // name time frameId

      ostr << _name << " end " 
	   << lexical_cast<string>(displayTime) 
	   << " " << lexical_cast<string>(_displayStart+_displayPeriod)
	   << " " << frameId
	   << " ";
      _session->recorder->Save(ostr.str(), "events.txt");
      _loggedEnd = true;
    }

  if (frameId > frameEnd())
    s[RUNNING] |= false;
  else
    s[RUNNING] = true;

  _session->recorder->Save(_name + " " + lexical_cast<string>(displayTime) + " display", "logger.txt");
}

void
Shape::initTexture()
{

  if (_textureName!=""){
    ImageLoad iload;
    iload.setFilename(_textureName.c_str());
    if(!(iload.load()))
      {
	exit(1);
      }
  
    glGenTextures(1, &_texture[0]); // Donne numero de texture
    glBindTexture(GL_TEXTURE_2D, _texture[0]); //Selectionne la texture

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
    glTexImage2D(
		 GL_TEXTURE_2D,		//Type de texture
		 0,			//Mipmap : aucun
		 3,		        //Couleurs: 4
		 iload.getSizeY(),	//Largeur: 2
		 iload.getSizeX(),	//Hauteur: 2
		 0,			//Largeur des bords: 0
		 GL_RGB,			//RGBA format
		 GL_UNSIGNED_BYTE,	//Type des couleurs
		 iload.getData()	        //Adresse de l'image
		 );

    if (_texture[0] == 0)
      {
	std::cout << "Impossible d'appliquer la texture de la forme " << _name << std::endl;
	exit(0);
      }
  }
}

void
Shape::Reset()
{
 
  _logged = false;
  _loggedEnd = false;

  _frameStart->value = _initFrameStart;
  int value = ((float)(_initFrameEnd) * _gainD);

  _frameEnd->value = lexical_cast<int>(value);

  _adaptFrame();
  _setDisplayTime();
}

void
Shape::_setDisplayTime()
{
  int fps = (_session->setup)->refreshRate();
  
  if (_frameEnd->value>=0){
  _displayPeriod = (_frameEnd->value - _frameStart->value)/fps*1000;
  // std::cout << _displayPeriod << std::endl;
  }
}

string
Shape::toString()
{
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

  return floor((nb*res)+0.5)/res;
}


int
Shape::random2params(int min, int max){

  std::ostringstream oss;
  oss << rand();

  unsigned int sum, ii;

  std::string result = oss.str();

  const char* chars = result.c_str();

  for(ii=0; ii < strlen(chars); ii++)
    {
      sum += (int) chars[ii]*2;
    }

  int seed = (int) (std::time(0)+sum);
  srand(seed);   

  if (max-min>0)
    {
      return rand()%((max+1) - min) + min;
    }
  if (max-min>0)
    {
      return rand()%((max+1) - min) + min;
    }
  return 0;
}

float 
Shape::_getRandomNumber(float pos, float nb)
{
  std::ostringstream oss;

  oss << rand();
  std::string result = oss.str();
  const char* chars = result.c_str();

  unsigned int i = 0, sum = 0, tmp = 0;
  int seed = 0;
  float min = (float) (pos-(nb));
  float max = (float) (pos+(nb));
  float newPos = 0.0;

  if (max<min)
    {
      tmp = max;
      max = min;
      min = tmp;
    }

  for(i=0; i < strlen(chars); i++)
    {
      sum += (int) chars[i]*2;
    }

  seed = (int)(std::time(0)+sum);
  srand(seed);

  newPos = (rand() * (max - min) / RAND_MAX) + min;
  newPos = newPos;

  return RoundNdecimal(3,newPos);
}

/*
  Add adapts in "k" (k = pAdapts (Trial::DisplayFrame))
*/
void
Shape::setAdapts(vector<Adapt*>*k)
{
  vector<Adapt*>::iterator it;
  for (it = _adapts.begin(); it!= _adapts.end(); it++){
    (*k).push_back(*it);
  }
}

void 
Shape::updateVelo(double coef)
{
  _gainV = _gainV * (coef); 
}

void
Shape::updateDuration(double coef)
{
  _gainD = _gainD * (coef);
}

void
Shape::_adaptFrame()
{
  if (_frameEnd->value>=0){
  int frame = random2params(lexical_cast<int>(_minStart->value),
			    lexical_cast<int>(_maxStart->value)); 

  _frameStart->value = lexical_cast<int>(_frameStart->value)+frame;
  _frameEnd->value = lexical_cast<int>(_frameEnd->value)+frame;
  }
}

/**
 * Abstract Constructor : inits some bool values
 *
 */
Shape::Shape()
{
  _id = 0;
  _texture[1] = 0;
  _logged = false;
  _loggedEnd = false;
  _subjectVisible = true;
  _start = false;
  _opacity = new Variable(1);
}


