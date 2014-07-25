#include "error.hh"

ErrorView::ErrorView(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "error",
  _error = new QLabel("Impossible d'atteindre la page demandée...", this);
  // show();
}

ErrorView::~ErrorView()
{

}
