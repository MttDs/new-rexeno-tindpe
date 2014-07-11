#include "error.hh"

Error::Error(QWidget *parent)
  : View(parent)
{
  name = "error",
  _error = new QLabel("Impossible d'atteindre la page demandée...", this);
  // show();
}

Error::~Error()
{

}
