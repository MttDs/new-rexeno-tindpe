#include "controller.hh"
#include "recorder.hh"
Controller::Controller(Ui::MainWindow* ui)
  :_ui(ui)
{
  _viewWidget = _ui->contentBar;
  _views.push_back(new Error(_viewWidget, this));
  _views.push_back(new CreateProtocole(_viewWidget, this));
  _views.push_back(new CreateSession(_viewWidget, this));

  _recorder = NULL;

  sessionInfo = new SessionInfo();
}

Controller::~Controller()
{
  // delete _createProtocole;
}

void
Controller::Init()
{

  QObject::connect(_ui->save, SIGNAL(triggered()), this, SLOT(_save()));

  QSignalMapper* signalMapper = new QSignalMapper(this);
  QObject::connect(_ui->showCreateSession, SIGNAL( triggered() ), signalMapper, SLOT(map()));
  QObject::connect(_ui->showCreateProtocole, SIGNAL( triggered() ), signalMapper, SLOT(map()));

  signalMapper->setMapping(_ui->showCreateSession, _ui->showCreateSession->text());
  signalMapper->setMapping(_ui->showCreateProtocole, _ui->showCreateProtocole->text());

  QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(_render(QString)));

  //_views[1]->setController();
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


void
Controller::_save()
{
  std::cout << "save!" << std::endl;
  _recorder = new Recorder("../../files/", 0);
  _recorder->AddFile("test.txt");

  std::cout << sessionInfo << " " << lexical_cast<string>(sessionInfo->frequency) << std::endl;
  _recorder->Save("frequency= "+ lexical_cast<string>(sessionInfo->frequency), "test.txt");
  _recorder->Save("width= "+ lexical_cast<string>(sessionInfo->width), "test.txt");
  _recorder->Save("height= "+ lexical_cast<string>(sessionInfo->height), "test.txt");
  _recorder->Save("nb_screens= "+ lexical_cast<string>(sessionInfo->nb_screens), "test.txt");
  _recorder->Save("nb_trials= "+ lexical_cast<string>(sessionInfo->nb_trials), "test.txt");
  _recorder->Save("shuffle= "+ lexical_cast<string>(sessionInfo->shuffle), "test.txt");
  _recorder->Save("save= " + sessionInfo->save, "test.txt");

  TrialInfo ti;
  foreach (ti, sessionInfo->trials)
    {
      _recorder->Save("| "+
		      ti.name+" "+
		      ti.attributes[0]+" "+
		      ti.attributes[1]+" "+
		      ti.attributes[2]+" "+
		      ti.attributes[3]+" "+
		      ti.attributes[4]+" "+
		      ti.attributes[5]+" "+
		      ti.attributes[6]+" "+
		      ti.attributes[7]+" "+
		      ti.attributes[8]
		      , "test.txt");
      _recorder->Save(";", "test.txt");
    }
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
