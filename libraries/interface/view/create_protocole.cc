#include "create_protocole.hh"
#include "controller.hh"
void print(const char*str){
  std::cout << str << std::endl;
}
CreateProtocole::CreateProtocole(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Nouveau protocole";
  _gridForm = new QGridLayout(this);
  _submit = new QPushButton("Creer le protocole");
  
  _frequency = new QLabel("Rafraichissement de l'écran (frequency=)");
  _screenWidth = new QLabel("Largeur de l'écran (width=)");
  _screenHeight = new QLabel("Hauteur de l'écran (height=)");
  _nbScreens = new QLabel("Nombre d'écran (nb_screens=)");
  _nbTrials = new QLabel("Nombre d'essai (nb_trials=)");
  _shuffle = new QLabel("Ordre d'affichage des sessions (shuffle=)");
  _save = new QLabel("Dossier de sauvegarde des données");

  _frequencyField = new QLineEdit("");
  _screenWidthField = new QLineEdit("");
  _screenHeightField = new QLineEdit("");
  _nbScreensField = new QLineEdit("");
  _nbTrialsField = new QLineEdit("");
  _shuffleField = new QLineEdit("");
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

  _gridForm->addWidget(_submit, 7, 0, 1, 2);
  resize(800, 500);

  Init();
  // show();
}

void
CreateProtocole::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(save()));
}

void 
CreateProtocole::save()
{
  std::cout << "save from create protocole" << std::endl;
  _controller->sessionInfo->frequency = _frequencyField->text().toInt(); 
  qDebug() << _frequencyField->text() ;
  std::cout << _controller->sessionInfo->frequency << std::endl;
  _controller->sessionInfo->width = _screenWidthField->text().toInt(); 
  _controller->sessionInfo->height = _screenHeightField->text().toInt();
  _controller->sessionInfo->nb_screens = _nbScreensField->text().toInt(); 
  _controller->sessionInfo->nb_trials = _nbTrialsField->text().toInt(); 
  _controller->sessionInfo->shuffle = _shuffleField->text().toInt(); 
  _controller->sessionInfo->save = _saveField->text().toUtf8().constData();
}
CreateProtocole::~CreateProtocole()
{
}
