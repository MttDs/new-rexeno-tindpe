#include "shape.hh"
#include "controller.hh"

ShapeView::ShapeView(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Formes";
  _lastIndex = -1;

  _layout = new QVBoxLayout(this);

  _comboShapes = new QComboBox;
  _comboShapes->addItem("Choisir une forme");
  _comboShapes->addItem("Damier");
  _comboShapes->addItem("Sphere");
  _comboShapes->addItem("Square");

  _comboShapesEdit = new QComboBox;
  _comboShapesEdit->addItem(QString::fromUtf8("Selectionnez une forme de la session à éditer"));
  loadComboShapesEdit();

  _layout->addWidget(_comboShapes);
  _layout->addWidget(_comboShapesEdit);

  _formShapes.push_back(new FormPlan(this, c, _layout));
  _formShapes.push_back(new FormSphere(this, c, _layout));
  _formShapes.push_back(new FormSquare(this, c, _layout));
  resize(parent->size());
  _init();

}

ShapeView::~ShapeView()
{
  FormShape *fs = NULL;
  foreach(fs,  _formShapes)
    {
      delete fs;
    }
}
/**
   note: initialise les evenements relatifs a la vue
**/
void
ShapeView::_init()
{
  QObject::connect(_comboShapes, SIGNAL(activated(int)), this, SLOT(_resetIndex(int)));
  QObject::connect(_comboShapes, SIGNAL(activated(int)), this, SLOT(_showFormShape(int)));
  QObject::connect(_comboShapes, SIGNAL(currentIndexChanged(int)), this, SLOT(_hideFormShape(int)));
  QObject::connect(_comboShapesEdit, SIGNAL(activated(int)), this, SLOT(fillFormShape(int)));
  QObject::connect(_controller, SIGNAL(fillComboShapes()), this, SLOT(loadComboShapesEdit()));
}

/**
   @index: indice du formulaire demande

   note: affiche le formuaire et met a jour
   le dernier index
**/
void
ShapeView::_showFormShape(int index)
{
  index = index-1;
  if (index>=0)
    {

      FormShape *sf = NULL; 
      sf = _formShapes.at(index);

      std::cout << "show shape" << std::endl;

      _formShapes.at(index)->activate();
      std::cout << "current index => " << index << std::endl;
      _lastIndex = index;
    }
}

/**
   @index: indice du formulaire demande (non utilise)

   note: cache le dernier formulaire (_lastIndex)
   
**/
void
ShapeView::_hideFormShape(int index)
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
ShapeView::loadComboShapesEdit()
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
      for (ii= _comboShapesEdit->count(); ii!=0; --ii)
	{
	  std::cout << ii <<_comboShapesEdit->count() <<  std::endl;
	  _comboShapesEdit->removeItem(ii);
	}
      std::cout <<_comboShapesEdit->count() << std::endl;
      foreach (si, ti->shapes)
	{
	  str = si.attributes[0].c_str();
	  _comboShapesEdit->addItem(str);
	}
    }
}

/** 
    note: todo
**/
void
ShapeView::fillFormShape(int index)
{
  std::cout << index-1 << std::endl;
  if (index-1>=0){
    _comboShapes->setEnabled(false);
  }
    else
      {
	_comboShapes->setEnabled(true);
      }

  if ((index-1)>=0)
    {
  vector<ShapeInfo> shapes = _getCurrentTrial()->shapes;
  ShapeInfo* si = &shapes.at(index-1); 
  ShapeInfo siTmp;
  FormShape* fs = NULL;
  int ii=0;
  int posShape;
  int posFormShape;

  if (si!=NULL)
    {
      string s;
      foreach(fs,  _formShapes)
	{
	  s = fs->getType();
	  std::cout << "2 "<< si->name << " " << s << std::endl;
	  if (strcmp(si->name.c_str(), s.c_str())==0)
	    {
	      posFormShape =ii;
	      break;
	    }
	  ii++;
	}
      ii = 0;
      foreach(siTmp, shapes)
	{
	  s = siTmp.attributes[0];
	  std::cout << "1 "<< si->attributes[0]  << " " << s << std::endl;
	
	  if (strcmp(si->attributes[0].c_str(), s.c_str())==0)
	    {
	      posShape = ii;
	      //     break;
	    }
	  ii++;
	}
      std::cout << "position de la shape" << posShape <<" position du form=> "<< posFormShape <<  std::endl;
      fs->fillForm(si, posShape);
      _hideFormShape(_lastIndex);
      _showFormShape(posFormShape+1); // todo
    }
  else
    {
    std::cout << "impossible de trouver la forme demandé......." << std::endl;
    }
    }
}
/**
   note: charge les formes disponibles pour cet essai
**/
void
ShapeView::beforeDisplay()
{
  loadComboShapesEdit();
}
