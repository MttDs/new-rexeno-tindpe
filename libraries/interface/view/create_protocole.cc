#include "create_protocole.hh"

CreateProtocole::CreateProtocole(QWidget *parent)
  : QWidget(parent)
{

  test = new QLabel(this);
  this->setStyleSheet("border: 2px solid red; border-radius: 10px;");
  test->setText("teeaaaqqqqqqqqqqqqqqqqqqqaa");
  resize(800, 500);
}

CreateProtocole::~CreateProtocole()
{

}

void 
CreateProtocole::display()
{
}
