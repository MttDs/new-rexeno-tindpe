#include "create_session.hh"
#include "controller.hh"

CreateSession::CreateSession(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Nouvelle session"; 

  _gridForm = new QGridLayout(this);
  _submit = new QPushButton("Creer une session");
  
  _name = new QLabel("Nom de la session");
  _veloCameraX = new QLabel("Vitesse de la camera en X");
  _veloCameraY = new QLabel("Vitesse de la camera en Y"); 
  _veloCameraZ = new QLabel("Vitesse de la camera en Z");
  _eyeX = new QLabel("Position de la camera en X");
  _eyeY = new QLabel("Position de la camera en Y");
  _eyeZ = new QLabel("Position de la camera en Z");
  _centerX = new QLabel("Direction de la camera en X");
  _centerY = new QLabel("Direction de la camera en Y");
  _centerZ = new QLabel("Direction de la camera en Z"); 
  
  _nameField = new QLineEdit("");
  _veloCmraXField = new QLineEdit("");
  _veloCmraYField = new QLineEdit("");
  _veloCmraZField = new QLineEdit("");
  _eyeXField = new QLineEdit("");
  _eyeYField = new QLineEdit("");
  _eyeZField = new QLineEdit("");
  _centerXField = new QLineEdit("");
  _centerYField = new QLineEdit("");
  _centerZField = new QLineEdit("");

  _gridForm->addWidget(_name,0,0);
  _gridForm->addWidget(_nameField,0,1);
  _gridForm->addWidget(_veloCameraX,1,0);
  _gridForm->addWidget(_veloCmraXField,1,1);
  _gridForm->addWidget(_veloCameraY,2,0);
  _gridForm->addWidget(_veloCmraYField,2,1);
  _gridForm->addWidget(_veloCameraZ,3,0);
  _gridForm->addWidget(_veloCmraZField,3,1);
  _gridForm->addWidget(_eyeX,4,0);
  _gridForm->addWidget(_eyeXField,4,1);
  _gridForm->addWidget(_eyeY,5,0);
  _gridForm->addWidget(_eyeYField,5,1);
  _gridForm->addWidget(_eyeZ,6,0);  
  _gridForm->addWidget(_eyeZField,6,1);
  _gridForm->addWidget(_centerX,7,0);
  _gridForm->addWidget(_centerXField,7,1);
  _gridForm->addWidget(_centerY,8,0);
  _gridForm->addWidget(_centerYField,8,1);
  _gridForm->addWidget(_centerZ,9,0);  
  _gridForm->addWidget(_centerZField,9,1);

  _gridForm->addWidget(_submit, 10, 0, 1, 2);
  resize(800, 500);

  Init();
  // show();
}

void
CreateSession::fillForm(int index)
{
  TrialInfo ti = _controller->sessionInfo->trials[index];
 QString str;
 _nameField->setText( str =ti.name.c_str());
  _veloCmraXField->setText( str =ti.attributes[0].c_str());
  _veloCmraYField->setText( str =ti.attributes[1].c_str());
  _veloCmraZField->setText(str =ti.attributes[2].c_str());
  _eyeXField->setText(str =ti.attributes[3].c_str());
  _eyeYField->setText(str =ti.attributes[4].c_str());
  _eyeZField->setText(str =ti.attributes[5].c_str());
  _centerXField->setText(str =ti.attributes[6].c_str());
  _centerYField->setText(str =ti.attributes[7].c_str());
  _centerZField->setText(str =ti.attributes[8].c_str());

}
void
CreateSession::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(save()));
  connect(_controller, SIGNAL(fillSessionForm(int)), this, SLOT(fillForm(int)));
  connect(this, SIGNAL(changeLeftBar()), _controller, SLOT(_updateLeftBar()));
}

void CreateSession::save()
{

  std::cout << "save from create session" << std::endl;
  // todo if name is in trials...name 
  // replace
  vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
  TrialInfo trial;
  trial.name = _nameField->text().toUtf8().constData();

  vector<string> attributes;
  attributes.push_back(_veloCmraXField->text().toUtf8().constData());
    attributes.push_back(_veloCmraYField->text().toUtf8().constData());
     attributes.push_back(_veloCmraZField->text().toUtf8().constData());
      attributes.push_back(_eyeXField->text().toUtf8().constData());
       attributes.push_back(_eyeYField->text().toUtf8().constData());
   attributes.push_back(_eyeZField->text().toUtf8().constData());
  attributes.push_back(_centerXField->text().toUtf8().constData());
  attributes.push_back(_centerYField->text().toUtf8().constData());
  attributes.push_back(_centerZField->text().toUtf8().constData());

  trial.attributes = attributes;
  trials->push_back(trial);

  QString str = trial.name.c_str();
  _controller->addInComboBox(str);
  emit(changeLeftBar());
}
CreateSession::~CreateSession(){

}
