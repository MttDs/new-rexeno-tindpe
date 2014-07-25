#include "view.hh"
#include <QFileDialog>
#include <wordexp.h>

//#include <boost/filesystem.hpp>
#include <math.h>       /* pow */
#include "controller.hh"
View::View(QWidget *parent)
  : QWidget(parent)
{
}

View::View(QWidget *parent, Controller *c)
  : QWidget(parent)
{
  _controller = c;
}

View::~View(){

}
/**
   note: retourne l'essai  selectionne.
**/
TrialInfo* 
View::_getCurrentTrial()
{
  if (_controller->trialExists())
    {
      return &(_controller->sessionInfo->trials.at(_controller->getIndexTrial()));
    }
  return NULL;
}


/**
   Execute une ou plusieurs tache(s)
   avant l'affichage de la vue
**/
void
View::beforeDisplay()
{

}
