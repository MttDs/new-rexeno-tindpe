#include "trial.hh"
#include "window.hh"
#include <boost/lexical_cast.hpp>
#include <GL/glut.h>

using namespace boost;
class Trial;


/** 
 * Constructor : Attributes values to the Shape's variables
 * 
 * @param si : contains information that was extracted from the protocole's conf file.
 * @param vm : a structure that will manage all the variables in the current trial and make them available
 *             to the user through the various callbacks.
 * @param father : pointer to the current trial (a little ugly by useful).
 */
Window::Window(const ShapeInfo& si,
               VariableManager& vm,
               Trial* father)
{
  assert(si.attributes.size() == 11);
  assert(father);
  _name = si.attributes[0];
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(si.attributes[5]));
  vm.addVariable(_G = new Variable(si.attributes[6]));
  vm.addVariable(_B = new Variable(si.attributes[7]));
  vm.addVariable(_width = new Variable(si.attributes[8]));
  vm.addVariable(_height = new Variable(si.attributes[9]));

  _ttl = lexical_cast<int>(si.attributes[10]);
  _thickness = 0.01;

  _father = father;
}

/**
 * @file   window.cc
 * @author hadrien <hadrien@barbow>
 * @date   Mon Jul 15 22:53:17 2013
 * 
 * @brief  Initializes variables
 * 
 * 
 */
Window::Window()
{
  _thickness = 0.01;
  _subjectVisible = false;
}

/**
 * @file   window.cc
 * @author hadrien <hadrien@barbow>
 * @date   Mon Jul 15 22:54:29 2013
 * 
 * @brief  Displays nothing on the Subject Screen
 * 
 * 
 */
void
Window::Display()
{

}

/**
 * @file   window.cc
 * @author hadrien <hadrien@barbow>
 * @date   Mon Jul 15 22:54:52 2013
 * 
 * @brief  Displays the window for the Experimenter Screen
 * 
 * 
 */
void
Window::DisplayMonitor()
{
  double leftX = _xGL() - _demiHorizontal();
  double rightX = _xGL() + _demiHorizontal();
  double topY = _yGL() + _demiVertical();
  double bottomY = _yGL() - _demiVertical();
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, topY);
  glVertex2d(leftX + _thickness, topY);
  glVertex2d(leftX + _thickness, bottomY);
  glVertex2d(leftX, bottomY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(rightX, topY);
  glVertex2d(rightX - _thickness, topY);
  glVertex2d(rightX - _thickness, bottomY);
  glVertex2d(rightX, bottomY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, topY);
  glVertex2d(leftX,  topY - _thickness);
  glVertex2d(rightX,  topY - _thickness);
  glVertex2d(rightX, topY);
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);
  glVertex2d(leftX, bottomY);
  glVertex2d(leftX, _thickness + bottomY);
  glVertex2d(rightX, _thickness + bottomY);
  glVertex2d(rightX, bottomY);
  glEnd();
  glEnable(GL_LIGHTING);
}

/**
 * @file   window.cc
 * @author hadrien <hadrien@barbow>
 * @date   Mon Jul 15 22:55:20 2013
 * 
 * @brief  returns true if the point P(x, y) is inside the window
 * x and y are doubles and represent coordinates on the screen
 * 
 */
bool
Window::isIn(double x,
             double y)
{
  double leftX = *_x - (*_width / 2);
  double rightX = *_x + (*_width / 2);
  double bottomY = *_y - (*_height / 2);
  double topY = *_y + (*_height / 2);
  bool res = true;

  res &= (x > leftX) && (x < rightX);
  res &= (y > bottomY) && (y < topY);

  return (res);
}

CorrectWindow::CorrectWindow(const ShapeInfo& si,
                             VariableManager& vm,
                             Trial* father)
{
  assert(si.attributes.size() == 9);
  assert(father);
  _name = si.attributes[0];
  _id = 4;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(0));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(0));
  vm.addVariable(_width = new Variable(si.attributes[5]));
  vm.addVariable(_height = new Variable(si.attributes[6]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[7]));

  _ttl = lexical_cast<int>(si.attributes[8]);

  _father = father;
  _startValidationFrame = -1;
  _type = CORRECT;
  _outsideValue = 0;
}

WrongWindow::WrongWindow(const ShapeInfo& si,
                         VariableManager& vm,
                         Trial* father)
{
  assert(si.attributes.size() == 9);
  assert(father);
  _name = si.attributes[0];
  _id = 3;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(0));
  vm.addVariable(_B = new Variable(0));
  vm.addVariable(_width = new Variable(si.attributes[5]));
  vm.addVariable(_height = new Variable(si.attributes[6]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[7]));

  _ttl = lexical_cast<int>(si.attributes[8]);

  _father = father;
  _startValidationFrame = -1;
  _type = WRONG_NEXT;
  _outsideValue = 0;
}

FixationWindow::FixationWindow(const ShapeInfo& si,
                               VariableManager& vm,
                               Trial* father)
{
  assert(si.attributes.size() == 9);
  assert(father);
  _name = si.attributes[0];
  _id = 6;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(0));
  vm.addVariable(_G = new Variable(128));
  vm.addVariable(_B = new Variable(128));
  vm.addVariable(_width = new Variable(si.attributes[5]));
  vm.addVariable(_height = new Variable(si.attributes[6]));
  vm.addVariable(_validationNbFrame = new Variable(si.attributes[7]));

  _ttl = lexical_cast<int>(si.attributes[8]);

  _father = father;
  _startValidationFrame = -1;
  _type = WAITING_FIXATION;
  _outsideValue = PAUSE;
}

// Small design flaw here : neutral window
// has a _validationNbFrame field inherited from Window but doesn't use it . . .
// sorry about that !
NeutralWindow::NeutralWindow(const ShapeInfo& si,
                             VariableManager& vm,
                             Trial* father)
{
  assert(si.attributes.size() == 8);
  assert(father);
  _name = si.attributes[0];
  _id = 5;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_frameStart = new Variable(si.attributes[3]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[4]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(0));
  vm.addVariable(_width = new Variable(si.attributes[5]));
  vm.addVariable(_height = new Variable(si.attributes[6]));
  vm.addVariable(_validationNbFrame = new Variable(0));

  _ttl = lexical_cast<int>(si.attributes[7]);

  _father = father;
  _startValidationFrame = -1;
  _type = NEUTRAL;
  _outsideValue = 0;
}

// TODO x and y should iterate over their 20 channel values !
void
Window::React2input(Status& s,
                    const datas& ds,
                    int n,
                    ms displayTime)
{
  datas::const_iterator datasIt;
  channel::const_iterator channelIt;

/*
  double x = ds[0][0].volt;
  double y = ds[1][0].volt;*/
// int *rep = &ds[0][0].rep;

/*  if (ds[0][0].rep != (-1)){
	  printf("J'ai une réponse! => %d \n", ds[0][0].rep);
	  s[CORRECT] = true;
//	  ds[0][0].rep = false;
	//  *rep = false;
  }*/
/*  if (isIn(x, y))
  {
    if (_startValidationFrame == -1)
    {
      if (n - _startValidationFrame > _validationNbFrame->value)
        // s[_type] is set by constructor and depends of the
        // window type
      {
        s[_type] = true;

    	  //   PDEBUG("Window::React2input", " " << name() << " activated");
      }
    }
    else
      _startValidationFrame = n;
  }
  else
  {
 //   PDEBUG("Window::React2input", " outside " << name());
    if (_outsideValue)
      s[_outsideValue] = true;
    _startValidationFrame = -1;
  }
*/
  Shape::React2input(s, ds, n, displayTime);
}

// void
// Window::Reset()
// {
//   _status[_type] = false;
// }
