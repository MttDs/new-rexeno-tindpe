#include "create_session.hh"
#include "controller.hh"

CreateSession::CreateSession(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Nouvelle session"; 
  _gridForm = new QVBoxLayout(this);
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
  
  _nameField = new QLineEdit("Session1");
  _veloCmraXField = new QLineEdit("0");
  _veloCmraYField = new QLineEdit("0");
  _veloCmraZField = new QLineEdit("0");
  _eyeXField = new QLineEdit("0");
  _eyeYField = new QLineEdit("1");
  _eyeZField = new QLineEdit("1.8");
  _centerXField = new QLineEdit("0");
  _centerYField = new QLineEdit("0");
  _centerZField = new QLineEdit("0");
  _nameField->setMinimumWidth(250);
  _gridForm->addWidget(_name);
  _gridForm->addWidget(_nameField);
  _gridForm->addWidget(_veloCameraX);
  _gridForm->addWidget(_veloCmraXField);
  _gridForm->addWidget(_veloCameraY);
  _gridForm->addWidget(_veloCmraYField);
  _gridForm->addWidget(_veloCameraZ);
  _gridForm->addWidget(_veloCmraZField);
  _gridForm->addWidget(_eyeX);
  _gridForm->addWidget(_eyeXField);
  _gridForm->addWidget(_eyeY);
  _gridForm->addWidget(_eyeYField);
  _gridForm->addWidget(_eyeZ);  
  _gridForm->addWidget(_eyeZField);
  _gridForm->addWidget(_centerX);
  _gridForm->addWidget(_centerXField);
  _gridForm->addWidget(_centerY);
  _gridForm->addWidget(_centerYField);
  _gridForm->addWidget(_centerZ);  
  _gridForm->addWidget(_centerZField);

  _gridForm->addWidget(_submit);

  _gridForm->setSpacing(2);


  Init();
}

void
CreateSession::fillForm(int index)
{
  std::cout << index << std::endl;
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

  vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
  TrialInfo trial;
  bool b = false;
  int indexTrial = _controller->getIndexTrial();

  if (_controller->trialExists())
    {
      std::cout << "save from create session" << std::endl;

      b = true;
      trial = trials->at(indexTrial);
      std::cout << "save from create session" << std::endl;

    }
  std::cout << "save from create session" << std::endl;

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
  std::cout << "size => " << trials->size() << std::endl;
  if (b)
    {
      trials->insert(trials->begin()+(indexTrial), trial);
      _controller->updateItemText(trial.name.c_str());
      ;
      std::cout << (trials->begin()+indexTrial)->name << " " << trial.name <<std::endl;

      std::cout << "il existe deja "  << std::endl;
    }
  else
    {
      std::cout << "il existe pas" << std::endl;
      trials->push_back(trial);
           QString str = trial.name.c_str();
         _controller->addInComboBox(str);
    }
  emit(changeLeftBar());
}
CreateSession::~CreateSession()
{

}
