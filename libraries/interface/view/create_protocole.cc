#include "create_protocole.hh"

void print(const char*str){
  std::cout << str << std::endl;
}

CreateProtocole::CreateProtocole(QWidget *parent)
  : View(parent)
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
  // show();
}

CreateProtocole::~CreateProtocole()
{

}