/**
 * @file   cross.cc
 * @author hadrien <hadrien@barbow>
 * @date   Sun Jun 30 01:09:11 2013
 * 
 * @brief  Implementation of the Cross class
 * 
 * 
 */

#include "cross.hh"
#include <GL/glut.h>
#include "trial.hh"

/** 
 * Constructor : Attributes values to the Shape's variables
 * 
 * @param si : contains information that was extracted from the protocole's conf file.
 * @param vm : a structure that will manage all the variables in the current trial and make them available
 *             to the user through the various callbacks.
 * @param father : pointer to the current trial (a little ugly by useful).
 */
Cross::Cross(const ShapeInfo& si,
             VariableManager& vm,
             Trial* father)
{
  assert(si.attributes.size() == 9);
  _name = si.attributes[0];
  _id = 2;
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

/** 
 * Destructor : TODO free variables ?
 * 
 */
void
Cross::Display()
{

}

/** 
 * Display appearing on the monitor screen (not visible by subject)
 * 
 */
void
Cross::DisplayMonitor()
{
  double xGL = _xGL();
  double yGL = _yGL();

  double demi_horizontal = _demiHorizontal();
  double demi_vertical = _demiVertical();

  double bar_width_horizontal = demi_horizontal / 20;
  double bar_width_vertical = demi_vertical / 20;
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
  glColor3ub(*_R,*_G,*_B);    
  glVertex2d(xGL-demi_horizontal, yGL-bar_width_vertical);
  glVertex2d(xGL+demi_horizontal, yGL-bar_width_vertical);
  glVertex2d(xGL+demi_horizontal, yGL+bar_width_vertical);
  glVertex2d(xGL-demi_horizontal, yGL+bar_width_vertical);
  glEnd();

  // Barre horizontale

  glBegin(GL_QUADS);
  glVertex2d(xGL-(bar_width_horizontal),yGL-demi_vertical);
  glVertex2d(xGL+(bar_width_horizontal),yGL-demi_vertical);
  glVertex2d(xGL+(bar_width_horizontal),yGL+demi_vertical);
  glVertex2d(xGL-(bar_width_horizontal),yGL+demi_vertical);
  glEnd();
  glEnable(GL_LIGHTING);
}

/** 
 * Changes the trial's state according to what was recorded in ds
 * 
 * @param s current state of the Trial
 * @param ds what was obtained from the nidaq card
 * @param frameId what frame is currently being displayed (0 if it is the first one)
 * @param ms 
 */
void
Cross::React2input(Status& s,
                   const datas& ds,
                   int frameId,
                   ms)
{
  datas::iterator it;

  _x->value = ds[0][0].volt;
  _y->value = -ds[1][0].volt;
  //PDEBUG("Cross::React2input", " x " << _x->value << " y " << _y->value);
  // for (it = ds.begin(); it != ds.end(); ++it)
  // {
  //   _x->value = (*ds.begin())[0].volt;
  //   _y->value = - (*ds.begin())[1].volt;
  // }
}


