#include "form_shape.hh"
#include "controller.hh"

FormShape::FormShape(QWidget *parent, Controller *c, QVBoxLayout *parentLayout)
  : View(parent, c)
{

  _parentLayout = parentLayout;
  _parentWidget = new QWidget;

  _layout = new QGridLayout(_parentWidget);

  _type = new QString("");
  _name = new QLabel("Nom de la forme:");
  _frameStart = new QLabel("Frame de départ:");
  _frameEnd = new QLabel("Frame de fin:");

  _nameField = new QLineEdit("");
  _frameStartField = new QLineEdit("0");
  _frameEndField = new QLineEdit("");

  _submit = new QPushButton("Enregistrer la forme");

  _layout->addWidget(_name,0,0);
  _layout->addWidget(_nameField,0,1);
  _layout->addWidget(_frameStart,1,0);
  _layout->addWidget(_frameStartField,1,1) ;
  _layout->addWidget(_frameEnd,2,0);
  _layout->addWidget(_frameEndField,2,1);

  _parentLayout->addWidget(_parentWidget);

  _parentWidget->hide();
  //resize(parent->size());
  Init();
}

FormShape::~FormShape()
{

}
void 
FormShape::activate()
{
  _parentWidget->show();
}

void
FormShape::inactivate()
{
  _parentWidget->hide();
}
void
FormShape::Init()
{
}
