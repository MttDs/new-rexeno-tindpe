#include "controller.hh"

/**
   @ui: template de la fenetre

   note: Creation des vues et mise en place de celles-ci 
   dans un vector.
**/
Controller::Controller(Ui::MainWindow* ui)
  :_ui(ui)
{
  _indexTrial = -1;

  sessionInfo = new SessionInfo();
 
  _views.push_back(new ErrorView(_ui->mainWidget, this));
  _views.push_back(new ProtocoleView(_ui->mainWidget, this));
  _views.push_back(new SessionView(_ui->mainWidget, this));
  _views.push_back(new ShapeView(_ui->mainWidget, this));
  _views.push_back(new EventView(_ui->mainWidget, this));

  _ui->showShape->setEnabled(false);
  _ui->showEvent->setEnabled(false);

  _model = new Model(sessionInfo);
  _init();
}

Controller::~Controller()
{
  View *v = NULL;
  foreach(v, _views)
    {
      delete v;
    }

  delete _model;
  delete sessionInfo;
}

/**
   note: Connexion des differentes routes et 
   evenements relevant de la template
**/
void
Controller::_init()
{  
  QObject::connect(_ui->save, SIGNAL(triggered()), _model, SLOT(checkAndSave()));
  QObject::connect(_ui->save2, SIGNAL(triggered()), _model, SLOT(save()));

  QSignalMapper* signalMapper = new QSignalMapper(this);

  QObject::connect(_ui->showSession, SIGNAL(triggered()), signalMapper, SLOT(map()));
  QObject::connect(_ui->showProtocole, SIGNAL(triggered()), signalMapper, SLOT(map()));
  QObject::connect(_ui->showShape, SIGNAL(triggered()), signalMapper, SLOT(map()));
  QObject::connect(_ui->showEvent, SIGNAL(triggered()), signalMapper, SLOT(map()));

  signalMapper->setMapping(_ui->showSession, _ui->showSession->text());
  signalMapper->setMapping(_ui->showProtocole, _ui->showProtocole->text());
  signalMapper->setMapping(_ui->showShape, _ui->showShape->text());
  signalMapper->setMapping(_ui->showEvent, _ui->showEvent->text());
  
  QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(_render(QString)));
  QObject::connect(_ui->comboTrials, SIGNAL(activated(int)), this, SLOT(_changeCurrentTrial(int)));

  QObject::connect(_ui->loadFile, SIGNAL(triggered()), this, SLOT(_loadFile()));
  QObject::connect(_ui->newDef, SIGNAL(triggered()), this, SLOT(_reset()));
}

/**
   @index: Numero du champs dans la liste "comboTrials"

   note: On retire 1 a l'index pour ne pas prendre en
   compte de signe "/" (premier element)
   Si l'index est != de 0 alors, on rempli le formulaire
   de la session a l'index (_indexTrial)
**/
void 
Controller::_changeCurrentTrial(int index){
  _indexTrial = (index-1);
  if (_indexTrial>=0)
    {
      emit(fillSessionForm(_indexTrial));
      emit(fillComboShapes());
    
      _ui->showShape->setEnabled(true);
      _ui->showEvent->setEnabled(true);

      setMessage("Session selectionnée");
    }
  else
    {
      _ui->showShape->setEnabled(false);
      _ui->showEvent->setEnabled(false);
      emit(resetIndexTrial());
    }

}

/**
   @text:  Libelle de l'action (toolbar)

   note: La vue doit porter le meme nom que 
   l'action cliquee
**/
void 
Controller::_render(QString text)
{
  View *view = NULL;
  QWidget* parent = _ui->mainWidget;

  view = _getView(text);
  if (parent!=0)
    {
      if (!view)
	{
	  view = _views[0];
	}
      view->setParent(parent);
      view->beforeDisplay();
      view->show();
    }
}

/**
   @text: Libelle de l'action (toolbar)

   note: retourne la vue correspondant au
   libelle
**/
View*
Controller::_getView(QString text)
{
  View* view = NULL;
  vector<View*>::iterator it;
  
  for (it = _views.begin(); it != _views.end(); ++it)
    {
      if (strcmp((*it)->name,(text.toUtf8()))==0)
	{
	  view = (*it);	  
	}
      (*it)->hide();
      (*it)->setParent(0);
    }
  if (view==NULL)
    {
      view = false;
    }
  return view;
}

/**
   note: verifie si _indexTrial est un index
   valide du vecteur "trials"
**/
bool
Controller::trialExists()
{
  if (_indexTrial>=0){
    return (sessionInfo->trials.size() >= (unsigned int) _indexTrial) ? true : false;
  }
  return false;
}
/**
   note: mise a jour de la bar de gauche
**/
void
Controller::_updateLeftBar()
{
  _ui->frequencyField->setText(lexical_cast<string>(sessionInfo->frequency).c_str());
  _ui->screenWidthField->setText(lexical_cast<string>(sessionInfo->width).c_str());
  _ui->screenHeightField->setText(lexical_cast<string>(sessionInfo->height).c_str());
  _ui->nbScreensField->setText(lexical_cast<string>(sessionInfo->nb_screens).c_str());
  _ui->nbTrialsField->setText(lexical_cast<string>(sessionInfo->nb_trials).c_str());
  _ui->shuffleField->setText(lexical_cast<string>(sessionInfo->shuffle).c_str());
  _ui->saveField->setText(lexical_cast<string>(sessionInfo->save).c_str());
  _ui->nbSessionsField->setText(lexical_cast<string>(sessionInfo->trials.size()).c_str());
 
  //Reset view

  _ui->comboTrials->setCurrentIndex(0);
  _changeCurrentTrial(0);
}
/**
   @str: nom de la session:
   
   note: ajoute dans la liste des sessions 
   une nouvelle session
**/
void
Controller::addItem(QString str)
{
  _ui->comboTrials->addItem(str);
}

/**
   @str: nom de la session

   note: replace dans la liste des sessions
   la session modifiee (+1 pour prendre en 
   compte le "/" (premier element)
**/
void 
Controller::updateItem(QString str)
{
  _ui->comboTrials->setItemText((_indexTrial+1), str);
}


/**
   note: supprime l'item a l'indice "_indexTrial+1"
**/

void
Controller::deleteItem()
{
  _ui->comboTrials->removeItem(_indexTrial+1);
}

/**
   @str = libelle du message

   note: affiche un message dans la 'statusBar'
 **/
void 
Controller::setMessage(const char* str)
{
  _ui->statusBar->showMessage(QString::fromUtf8(str), 8000);
}



/**
   note: charge un ficher de definition et rempli 
   la structure sessionInfo
**/

void 
Controller::_loadFile()
{

  QString filename = QFileDialog::getOpenFileName(
						  0,
						  tr("Open File"),
						  "protocoles/"
						  "Text File (*.txt)"
						  );


   _reset();
  bool r = configuration::CreateConfiguration(filename.toUtf8().constData(), *sessionInfo);
  // bool r = configuration::CreateConfiguration("definition", conf);
  if (r)
    {
      
      TrialInfo ti;
      QString str;
      foreach (ti, sessionInfo->trials)
	{
	  str = QString(ti.name.c_str());
	  addItem(str);
	}
      _updateLeftBar();
    }

}

/**
   note: Remet a zero la session et vide la liste des sessions
   disponible
 **/
void 
Controller::_reset()
{
  sessionInfo->trials.clear();
  int ii;

  for(ii=_ui->comboTrials->count(); ii>0 ; --ii)
    {
      _ui->comboTrials->removeItem(ii);
    }

   _updateLeftBar();
}
