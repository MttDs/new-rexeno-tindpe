#include "controller.hh"

Controller::Controller(Ui::MainWindow* ui)
  :_ui(ui)
{
  _viewWidget = _ui->contentBar;
  _views.push_back(new Error(_viewWidget));
  _views.push_back(new CreateProtocole(_viewWidget));
  _views.push_back(new CreateSession(_viewWidget));

}

Controller::~Controller()
{
  // delete _createProtocole;
}

void
Controller::Init()
{
  QSignalMapper* signalMapper = new QSignalMapper(this);
  QObject::connect(_ui->showCreateSession, SIGNAL( triggered() ), signalMapper, SLOT(map()));
  QObject::connect(_ui->showCreateProtocole, SIGNAL( triggered() ), signalMapper, SLOT(map()));
  signalMapper->setMapping(_ui->showCreateSession, _ui->showCreateSession->text());
  signalMapper->setMapping(_ui->showCreateProtocole, _ui->showCreateProtocole->text());

  QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(_render(QString)));
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
