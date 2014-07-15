#include "create_session.hh"

CreateSession::CreateSession(QWidget *parent, Controller *c)
  : View(parent, c)
{
  name = "Nouvelle session"; 
  _title = new QLabel("Mise en place d'une nouvelle session", this);
  // show();
}

CreateSession::~CreateSession(){

}
