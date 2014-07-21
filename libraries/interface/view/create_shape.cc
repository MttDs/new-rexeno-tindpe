#include "create_shape.hh"
#include "controller.hh"

CreateShape::CreateShape(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Ajouter une forme";
  _layout = new QVBoxLayout(this);
   _comboShapes = new QComboBox;
   _comboShapes->addItem("/");
   _comboShapes->addItem("Damier");
   _comboShapes->addItem("Sphere");
   _comboShapes->addItem("Square");


   _layout->addWidget(_comboShapes);

   _formShapes.push_back(new FormPlan(this, c, _layout));
   _formShapes.push_back(new FormSphere(this, c, _layout));
   _formShapes.push_back(new FormSquare(this, c, _layout));
   resize(parent->size());
   Init();

   _lastIndex = -1;
}

CreateShape::~CreateShape()
{

}

void
CreateShape::Init()
{
  QObject::connect(_comboShapes, SIGNAL(activated(int)), this, SLOT(showFormShape(int)));
  QObject::connect(_comboShapes, SIGNAL(currentIndexChanged(int)), this, SLOT(hideFormShape(int)));
}

void
CreateShape::showFormShape(int index)
{
  FormShape *sf = NULL; 
  index = index-1;
  sf = _formShapes.at(index);

  std::cout << "show shape" << std::endl;

  //  sf->setVisible(true);
  // sf->show();
   _formShapes.at(index)->activate();
  std::cout << "current index => " << index << std::endl;
  _lastIndex = index;

  // _layout->addWidget(sf, 0);
}

void
CreateShape::hideFormShape(int index)
{
  if (_lastIndex>=0)
    {
  FormShape *sf = NULL; 
  sf = _formShapes.at(_lastIndex);
  _formShapes.at(_lastIndex)->inactivate();

std::cout << "last => " << _lastIndex << " current => " << index << std::endl;
  }
}

