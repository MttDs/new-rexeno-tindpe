#include "create_session.hh"

CreateSession::CreateSession(QWidget *parent)
  : View(parent)
{
  name = "Nouvelle session"; 
  _title = new QLabel("Mise en place d'une nouvelle session", this);
  // show();
}

CreateSession::~CreateSession(){

}
