#include "create_protocole.hh"
#include "controller.hh"

CreateProtocole::CreateProtocole(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Nouveau protocole";
  _gridForm = new QGridLayout(this);
  _submit = new QPushButton("Creer le protocole");
  //_gridForm->setStyleSheet("border-right: 1px solid blue;");
  _frequency = new QLabel("Rafraichissement de l'écran:");
  _screenWidth = new QLabel("Largeur de l'écran:");
  _screenHeight = new QLabel("Hauteur de l'écran:");
  _nbScreens = new QLabel("Nombre d'écran:");
  _nbTrials = new QLabel("Nombre d'essai:");
  _shuffle = new QLabel("Ordre d'affichage des sessions:");
  _save = new QLabel("Emplacement de sauvegarde des données");

  _frequencyField = new QLineEdit("60");
  _screenWidthField = new QLineEdit("1920");
  _screenHeightField = new QLineEdit("1080");
  _nbScreensField = new QLineEdit("1");
  _nbTrialsField = new QLineEdit("20");
  _shuffleField = new QLineEdit("1");
  _saveField = new QLineEdit("");

  _gridForm->addWidget(_frequency,0,0);
  _gridForm->addWidget(_frequencyField,0,1);
  _gridForm->addWidget(_screenWidth,1,0);
  _gridForm->addWidget(_screenWidthField,1,1);
  _gridForm->addWidget(_screenHeight,2,0);
  _gridForm->addWidget(_screenHeightField,2,1);
  _gridForm->addWidget(_nbScreens,3,0);
  _gridForm->addWidget(_nbScreensField,3,1);
  _gridForm->addWidget(_nbTrials,4,0);
  _gridForm->addWidget(_nbTrialsField,4,1);
  _gridForm->addWidget(_shuffle,5,0);
  _gridForm->addWidget(_shuffleField,5,1);
  _gridForm->addWidget(_save,6,0);  
  _gridForm->addWidget(_saveField,6,1);
  resize(parent->size());
   _gridForm->addWidget(_submit, 7, 0, 1, 2);
  Init();
  // show();
}

void
CreateProtocole::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(save()));
  connect(this, SIGNAL(changeLeftBar()), _controller, SLOT(_updateLeftBar()));
}

void 
CreateProtocole::save()
{
  std::cout << "save from create protocole" << std::endl;
  _controller->sessionInfo->frequency = _frequencyField->text().toInt(); 
  _controller->sessionInfo->width = _screenWidthField->text().toInt(); 
  _controller->sessionInfo->height = _screenHeightField->text().toInt();
  _controller->sessionInfo->nb_screens = _nbScreensField->text().toInt(); 
  _controller->sessionInfo->nb_trials = _nbTrialsField->text().toInt(); 
  _controller->sessionInfo->shuffle = _shuffleField->text().toInt(); 
  _controller->sessionInfo->save = _saveField->text().toUtf8().constData();

  emit changeLeftBar();
}
CreateProtocole::~CreateProtocole()
{
}
