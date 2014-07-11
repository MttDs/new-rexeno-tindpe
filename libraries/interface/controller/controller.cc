#include "controller.hh"

#include "ui_mainwindow.hh"

Controller::Controller( Ui::MainWindow* ui)
 :_ui(ui)
{

}

Controller::~Controller()
{

}

void
Controller::Init(){
  QObject::connect(_ui->button1, SIGNAL(clicked()), this, SLOT(render()));
}

void 
Controller::render(){

  CreateProtocole* view = NULL;

  QWidget* parent = _ui->contentBar;
  if (parent!=0){
    view = new CreateProtocole(parent);
    view->show();
  }
  else{
    std::cout << "ERROR!" << std::endl;
  }
}
