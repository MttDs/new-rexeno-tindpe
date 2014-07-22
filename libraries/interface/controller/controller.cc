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

  _views.push_back(new Error(_ui->mainWidget, this));
  _views.push_back(new CreateProtocole(_ui->mainWidget, this));
  _views.push_back(new CreateSession(_ui->mainWidget, this));
  _views.push_back(new CreateShape(_ui->mainWidget, this));

  sessionInfo = new SessionInfo();
  _model = new Model(sessionInfo);
}

Controller::~Controller()
{
   delete _model;
   delete sessionInfo;
}

/**
   note: Connexion des differentes routes et 
   evenements relevant de la template
 **/
void
Controller::Init()
{

  QObject::connect(_ui->save, SIGNAL(triggered()), _model, SLOT(save()));

  QSignalMapper* signalMapper = new QSignalMapper(this);
  QObject::connect(_ui->showCreateSession, SIGNAL( triggered() ), signalMapper, SLOT(map()));
  QObject::connect(_ui->showCreateProtocole, SIGNAL( triggered() ), signalMapper, SLOT(map()));
 QObject::connect(_ui->showCreateShape, SIGNAL( triggered() ), signalMapper, SLOT(map()));
  signalMapper->setMapping(_ui->showCreateSession, _ui->showCreateSession->text());
  signalMapper->setMapping(_ui->showCreateProtocole, _ui->showCreateProtocole->text());
  signalMapper->setMapping(_ui->showCreateShape, _ui->showCreateShape->text());

  QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(_render(QString)));
  QObject::connect(_ui->comboTrials, SIGNAL(activated(int)), this, SLOT(_changeCurrentTrial(int)));
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
  if (index==0){
    _indexTrial = -1;
  }
  else{
    _indexTrial = (index-1);
     emit(fillSessionForm(_indexTrial));
  }

  std::cout << "index trial (from controller) =>" << index << " " << _indexTrial << std::endl;

}

/**
   @text:  Libelle de l'action (toolbar)

   note: La vue doit porter le meme nom que 
   l'action cliquee
 **/
void 
Controller::_render(QString text)
{
  const char* name = NULL;
  name = text.toUtf8();
  std::cout << "name => " << name << std::endl;
  View *view = NULL;
  view = _getView(text);
  QWidget* parent = _ui->mainWidget;
  
  if (parent!=0)
    {
      if (!view)
	{
	  view = _views[0];
	}
      view->setParent(parent);
      view->show();
    }
  else
    {
      std::cout << "ERROR!" << std::endl;
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
  std::cout << _views.size() << std::endl;
  for (it = _views.begin(); it != _views.end(); ++it)
    {
      std::cout << (*it)->name << std::endl;
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
  std::cout << "left bar updated" << std::endl;

}
/**
   @str: nom de la session:
   
   note: ajoute dans la liste des sessions 
   une nouvelle session
 **/
void
Controller::addInComboBox(QString str)
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
Controller::updateItemText(QString str)
{
  _ui->comboTrials->setItemText((_indexTrial+1), str);
}
