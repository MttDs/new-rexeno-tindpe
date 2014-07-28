#include "protocole.hh"
#include "controller.hh"

ProtocoleView::ProtocoleView(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Protocole";
  _gridForm = new QGridLayout(this);
  _submit = new QPushButton("Creer le protocole");

  _frequency = new QLabel(QString::fromUtf8("Rafraichissement de l'écran:"));
  _screenWidth = new QLabel(QString::fromUtf8("Largeur de l'écran:"));
  _screenHeight = new QLabel(QString::fromUtf8("Hauteur de l'écran:"));
  _nbScreens = new QLabel(QString::fromUtf8("Nombre d'écran:"));
  _nbTrials = new QLabel(QString::fromUtf8("Nombre d'essai:"));
  _shuffle = new QLabel("Ordre d'affichage des sessions:");
 _savePath = new QLabel(QString::fromUtf8("Emplacement de sauvegarde des données"));

  _frequencyField = new QLineEdit("60");
  _screenWidthField = new QLineEdit("1920");
  _screenHeightField = new QLineEdit("1080");
  _nbScreensField = new QLineEdit("1");
  _nbTrialsField = new QLineEdit("20");
  _shuffleField = new QLineEdit("1");
  _savePathField = new QLineEdit("");

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
  _gridForm->addWidget(_savePath,6,0);  
  _gridForm->addWidget(_savePathField,6,1);

  _gridForm->addWidget(_submit, 7, 0, 1, 2);
   
  resize(parent->size());
  _init();
}
/**
   note: initialisation des evenements relatifs a
   la vue
**/
void
ProtocoleView::_init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
  connect(this, SIGNAL(changeLeftBar()), _controller, SLOT(_updateLeftBar()));
}
/**
   note: sauvegarde les donnees dans la structure
   sessionInfo
   Envoie un signal afin de mettre a jour la bar de
   gauche
**/
void 
ProtocoleView::_save()
{
  _controller->sessionInfo->frequency = _frequencyField->text().toInt(); 
  _controller->sessionInfo->width = _screenWidthField->text().toInt(); 
  _controller->sessionInfo->height = _screenHeightField->text().toInt();
  _controller->sessionInfo->nb_screens = _nbScreensField->text().toInt(); 
  _controller->sessionInfo->nb_trials = _nbTrialsField->text().toInt(); 
  _controller->sessionInfo->shuffle = _shuffleField->text().toInt(); 
  _controller->sessionInfo->save = _savePathField->text().toUtf8().constData();

  emit changeLeftBar();

  _controller->setMessage("Paramètre du protocole enregistrés.");
}


ProtocoleView::~ProtocoleView()
{
}
