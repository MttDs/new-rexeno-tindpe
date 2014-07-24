#include "form_shape.hh"
#include "controller.hh"

FormShape::FormShape(QWidget *parent, Controller *c, QVBoxLayout *parentLayout)
  : View(parent, c)
{
  _index = -1;

  _parentLayout = parentLayout;
  _parentWidget = new QWidget;

  _layout = new QGridLayout(_parentWidget);

  _type = new QString("");
  _name = new QLabel("Nom de la forme:");
  _frameStart = new QLabel("Frame de départ:");
  _frameEnd = new QLabel("Frame de fin:");

  _nameField = new QLineEdit("Shape");
  _frameStartField = new QLineEdit("0");
  _frameEndField = new QLineEdit("60");

  _submit = new QPushButton("Enregistrer la forme");

  _parentLayout->addWidget(_parentWidget);

  _parentWidget->hide();
  Init();
  //resize(parent->size());
}


FormShape::~FormShape()
{

}

void 
FormShape::_save(){
  _index = -1;
  emit(afterSave());
}

void
FormShape::Init()
{
  connect(this, SIGNAL(afterSave()), parent(), SLOT(loadComboShapesEdit()));
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
