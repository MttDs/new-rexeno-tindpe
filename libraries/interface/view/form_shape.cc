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
  _frameStart = new QLabel(QString::fromUtf8("Frame de départ:"));
  _frameEnd = new QLabel("Frame de fin:");

  _nameField = new QLineEdit("");
  _frameStartField = new QLineEdit("0");
  _frameEndField = new QLineEdit("0");

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

bool
FormShape::shapeValid()
{
  if (_index>=0)
    {
      return true;
    }
  return false;
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

  if (shapeValid())
    {
    if (nbOfShape==1 || si == lastSi)
      {
	  shapes->erase(shapes->begin()+_index);
      }
    else
      {
	  shapes->at(_index)= shapes->back();
	  shapes->erase(shapes->end()-1);
      }

    _controller->setMessage("Forme supprimée!");
    reset();
    afterSave();
  }
}
