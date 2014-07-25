#include "event.hh"
#include "controller.hh"

EventView::EventView(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Événement";
  _currentShape = -1;

  _layout = new QVBoxLayout(this);

  _comboShapes = new QComboBox;
  _comboShapes->addItem(QString::fromUtf8("Pas de forme selectionnée"));

  _comboEvents = new QComboBox;
  _comboEvents->addItem(QString::fromUtf8("Selectionner l'événement à supprimer"));

  _parentForm = new QGridLayout;

  _title = new QLabel(QString::fromUtf8("Ajouter un événement"));
  _key = new QLabel("Touche du clavier");
  _coef = new QLabel("Coefficient multiplicateur");
  _type = new QLabel(QString::fromUtf8("durée (d) - vitesse (v)"));

  _keyField = new QLineEdit("");
  _coefField = new QLineEdit("");
  _comboType = new QComboBox;
  _comboType->addItem("d");
  _comboType->addItem("v");

  _submit = new QPushButton("Ajouter");

  _parentForm->addWidget(_key,1,0);
  _parentForm->addWidget(_keyField,1,1);
  _parentForm->addWidget(_coef,2,0);
  _parentForm->addWidget(_coefField,2,1);
  _parentForm->addWidget(_type,3,0);
  _parentForm->addWidget(_comboType,3,1);
  _parentForm->addWidget(_submit,4,0,1,2);

  _layout->addWidget(_comboShapes);
  _layout->addWidget(_comboEvents);
  _layout->addLayout(_parentForm);

  resize(parent->size());

  _init();
}

EventView::~EventView()
{

}

void 
EventView::_init()
{
  connect(_comboEvents, SIGNAL(activated(int)), this, SLOT(_deleteEvent(int)));
  connect(_controller, SIGNAL(fillComboShapes()), this, SLOT(loadComboShapes()));
  connect(_comboShapes, SIGNAL(activated(int)), this, SLOT(_loadEventsFromShape(int)));
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
}

void
EventView::_deleteEvent(int index)
{
  int nbEvent = index-1;

  TrialInfo* ti = _getCurrentTrial();
  ShapeInfo* si = &ti->shapes.at(_currentShape);
  vector<ShapeListener>* listeners = &si->listeners;
  ShapeListener* sl = &listeners->at(nbEvent);
  ShapeListener* end = &listeners->back();

  int nbOfListeners =  listeners->size();
  std::cout << "nbindex => "<< nbEvent << std::endl;
  if (nbEvent>=0)
    {
 
      if (nbOfListeners==1 || sl == end)
	{
	  std::cout << "suppresion event premier ou dernier" << std::endl;
	  si->listeners.erase(listeners->begin()+nbEvent);
	}
      else
	{
	  std::cout << "suppresion event milieu" << std::endl;
	  listeners->at(nbEvent)=  listeners->back();
	  listeners->erase( listeners->end()-1);
	}
      _loadEventsFromShape(_currentShape+1);

    }
  else{
    std::cout << "rien a supprimer" << std::endl;
  }

}
void
EventView::_loadEventsFromShape(int index)
{
  _currentShape = index-1;

  TrialInfo* ti = _getCurrentTrial();
  ShapeInfo* si = &ti->shapes.at(_currentShape);
  ShapeListener sl;
  int ii = 1;

  for (ii= _comboEvents->count(); ii!=0; --ii)
    {
      _comboEvents->removeItem(ii);
    }
  foreach(sl, si->listeners)
    {
 
      //  str = si.attributes[0].c_str();
      _comboEvents->addItem("test");
	
    }
}
void
EventView::_save()
{
  std::cout << "Je dois enregistrer " << _currentShape <<std::endl;
  TrialInfo* ti = _getCurrentTrial();
  ShapeInfo* si = &ti->shapes.at(_currentShape);
  ShapeListener sl;
  sl.key = _keyField->text().toInt();
  sl.coef = _coefField->text().toFloat();
  sl.gain = _comboType->itemText(_comboType->currentIndex()).toUtf8().constData();

  si->listeners.push_back(sl);
  _loadEventsFromShape(_currentShape+1);
  _reset();
}

void
EventView::loadComboShapes()
{
  
  if (_controller->trialExists())
    {
      std::cout << "index (from create shape) " <<  _controller->getIndexTrial()<< std::endl;
      TrialInfo* ti =_getCurrentTrial();
      ShapeInfo si;
      QString str;

      // Reset combo box
      int ii = 1;
      std::cout <<_comboShapes->count() << std::endl;
      for (ii= _comboShapes->count(); ii!=0; --ii){
	std::cout << ii <<_comboShapes->count() <<  std::endl;
	_comboShapes->removeItem(ii);
      }
      std::cout <<_comboShapes->count() << std::endl;
      foreach (si, ti->shapes)
	{
	  str = si.attributes[0].c_str();
	  _comboShapes->addItem(str);
	}
    }
}
void 
EventView::beforeDisplay()
{
  loadComboShapes();
  _reset();
}

void 
EventView::_reset()
{
  _keyField->setText("");
  _coefField->setText("");
}
