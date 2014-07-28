#include "session.hh"
#include "controller.hh"

SessionView::SessionView(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Session"; 
  _gridForm = new QVBoxLayout(this);
  _submit = new QPushButton("Creer/Modifier la session");
  
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
  _deleteSession = new QPushButton("Supprimer cette session");

  _nameField = new QLineEdit("");
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
  _gridForm->addWidget(_deleteSession);

  _gridForm->setSpacing(2);
  resize(parent->size());
  _init();
}

/**
   note: initialise les evenements relatifs a la vue
**/
void
SessionView::_init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
  connect(_deleteSession, SIGNAL(clicked()), this, SLOT(_delete()));
  connect(_controller, SIGNAL(fillSessionForm(int)), this, SLOT(fillForm(int)));
  connect(this, SIGNAL(changeLeftBar()), _controller, SLOT(_updateLeftBar()));
}

/**
   @index: indice de l'essai 
  
   note: recupere l'essai a l'indice "index"
   et rempli le formulaire de la session
**/
void
SessionView::fillForm(int index)
{
  if (index>=0)
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
}
/**
   note: Sauvegarde l'essai dans le vecteur de "trials"
   si l'essai n'existe pas on l'ajoute a la fin du 
   vecteur 
   sinon on remplace l'essai
   La meme chose est effectuee pour mettre a jour la liste
   des sessions disponibles (comboTrials)
**/
void 
SessionView::_save()
{
  vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
  TrialInfo trial;
  bool b = false;
  int indexTrial = _controller->getIndexTrial();

  if (_controller->trialExists())
    {
      b = true;
      trial = trials->at(indexTrial);
    }

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
  if (b)
    {
      trials->at(indexTrial)= trial;
      _controller->updateItem(trial.name.c_str());
      _controller->setMessage("La session a bien été modifiée");
    }
  else
    {
      trials->push_back(trial);
      QString str = trial.name.c_str();
      _controller->addItem(str);
      _controller->setMessage("Nouvelle session créée");
    }
  reset();
  emit(changeLeftBar());
}


/**
   note: supprime ou remet a zero (todo) la session
**/
void
SessionView::_delete()
{
  if (_controller->trialExists())
    {

      int indexTrial = _controller->getIndexTrial();
      int nbOfTrials = _controller->sessionInfo->trials.size();
      vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
      TrialInfo* ti = &(_controller->sessionInfo->trials.at(indexTrial));
      TrialInfo* lastTi = &(_controller->sessionInfo->trials.back());
      if (nbOfTrials==1 || ti==lastTi )
	{
	  trials->erase(trials->begin()+indexTrial);
	}	  
      else
	{	  
	  trials->at(indexTrial)= trials->back();
	  trials->erase(trials->end()-1);
	}
      _controller->deleteItem();
      reset();
      emit(changeLeftBar());

      _controller->setMessage("Session supprimée!");
    }
  else
    {
      reset();
    }
}

void
SessionView::reset()
{
  _nameField->setText("");
  _veloCmraXField->setText("0");
  _veloCmraYField->setText("0");
  _veloCmraZField->setText("0");
  _eyeXField->setText("0");
  _eyeYField->setText("1");
  _eyeZField->setText("1.8");
  _centerXField->setText("0");
  _centerYField->setText("0");
  _centerZField->setText("0");
}

SessionView::~SessionView()
{

}
