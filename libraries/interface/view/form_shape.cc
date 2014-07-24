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
  _buttonDelete = new QPushButton("Supprimer cette forme");
  _buttonDelete->hide();

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
  connect(_buttonDelete, SIGNAL(clicked()), this, SLOT(_deleteShape()));
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

void 
FormShape::_deleteShape()
{
  int indexTrial = _controller->getIndexTrial();  
  TrialInfo* ti =  &(_controller->sessionInfo->trials.at(indexTrial));
  vector<ShapeInfo>* shapes = &ti->shapes;
  ShapeInfo* si = &shapes->at(_index);
  ShapeInfo* lastSi = &shapes->back();
  int nbOfShape = shapes->size();

  std::cout << "delete index => " << _index << std::endl;
  if (_index!=-1)
    {
    if (nbOfShape==1 || si == lastSi)
      {
	  std::cout << 1 << std::endl;
	  shapes->erase(shapes->begin()+_index);
      }
    else
      {
	  std::cout << 2 << std::endl;
	  shapes->at(_index)= shapes->back();
	  shapes->erase(shapes->end()-1);
      }
    reset();
    afterSave();
  }
}
