#include "create_shape.hh"
#include "controller.hh"

CreateShape::CreateShape(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Formes";
  _layout = new QVBoxLayout(this);

  _comboShapes = new QComboBox;
  _comboShapes->addItem("/");
  _comboShapes->addItem("Damier");
  _comboShapes->addItem("Sphere");
  _comboShapes->addItem("Square");

  _comboShapesEdit = new QComboBox;
  _comboShapesEdit->addItem("/");
  loadComboShapesEdit();

  _layout->addWidget(_comboShapes);
  _layout->addWidget(_comboShapesEdit);

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
/**
   note: initialise les evenements relatifs a la vue
 **/
void
CreateShape::Init()
{
  QObject::connect(_comboShapes, SIGNAL(activated(int)), this, SLOT(showFormShape(int)));
  QObject::connect(_comboShapes, SIGNAL(currentIndexChanged(int)), this, SLOT(hideFormShape(int)));
  QObject::connect(_comboShapesEdit, SIGNAL(activated(int)), this, SLOT(fillFormShape(int)));
}
/**
   @index: indice du formulaire demande

   note: affiche le formuaire et met a jour
   le dernier index
 **/
void
CreateShape::showFormShape(int index)
{
  FormShape *sf = NULL; 
  index = index-1;
  sf = _formShapes.at(index);

  std::cout << "show shape" << std::endl;

  _formShapes.at(index)->activate();
  std::cout << "current index => " << index << std::endl;
  _lastIndex = index;
}

/**
   @index: indice du formulaire demande (non utilise)

   note: cache le dernier formulaire (_lastIndex)
   
 **/
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
/**
   note: charge les formes disponible  de l'essai selectionne
   (_getCurrentTrial()) apres avoir remii a zero la liste des 
   formes (pour mise a jour) (_comboShapeEdit).
   
 **/
void
CreateShape::loadComboShapesEdit()
{
  
  if (_controller->trialExists())
    {
      std::cout << "index (from create shape) " <<  _controller->getIndexTrial()<< std::endl;
      TrialInfo* ti =_getCurrentTrial();
      ShapeInfo si;
      QString str;

      // Reset combo box
      int ii = 1;
      std::cout <<_comboShapesEdit->count() << std::endl;
      for (ii= _comboShapesEdit->count(); ii!=0; --ii){
	std::cout << ii <<_comboShapesEdit->count() <<  std::endl;
	_comboShapesEdit->removeItem(ii);
      }
      std::cout <<_comboShapesEdit->count() << std::endl;
      foreach (si, ti->shapes)
	{
	  str = si.name.c_str();
	  _comboShapesEdit->addItem(str);
	}
    }
}
/**
   note: retourne l'essai  selectionne.
 **/
TrialInfo* 
CreateShape::_getCurrentTrial()
{
  if (_controller->trialExists())
    {
      return &(_controller->sessionInfo->trials.at(_controller->getIndexTrial()));
    }
  return NULL;
}
/** 
    note: todo
**/
void
CreateShape::fillFormShape(int index)
{
  std::cout << index << std::endl;
  TrialInfo* si = _getCurrentTrial();
  if (si!=NULL)
    {
          hideFormShape(_lastIndex);
          showFormShape(index);
    }
}

