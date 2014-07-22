#include "controller.hh"
Controller::Controller(Ui::MainWindow* ui)
  :_ui(ui)
{
  _viewWidget = _ui->contentBar;
  _views.push_back(new Error(_viewWidget, this));
  _views.push_back(new CreateProtocole(_viewWidget, this));
  _views.push_back(new CreateSession(_viewWidget, this));
  _views.push_back(new CreateShape(_viewWidget, this));

  _indexTrial = -1;
  sessionInfo = new SessionInfo();
  _model = new Model(sessionInfo);
}

Controller::~Controller()
{
  // delete _createProtocole;
}

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
void 
Controller::_render(QString text)
{
  const char* name = NULL;
  name = text.toUtf8();
  std::cout << "name => " << name << std::endl;
  View *view = NULL;
  view = _getView(text);
  QWidget* parent = _ui->contentBar;
  
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

bool
Controller::trialExists()
{
  if (_indexTrial>=0){
    return (sessionInfo->trials.size() >= (unsigned int) _indexTrial) ? true : false;
  }
  return false;
}

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

void
Controller::addInComboBox(QString str)
{
  _ui->comboTrials->addItem(str);
}

void 
Controller::updateItemText(QString text)
{
  _ui->comboTrials->setItemText((_indexTrial+1), text);
}
