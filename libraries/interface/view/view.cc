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
  _controller->hello();
}

View::~View(){

}

