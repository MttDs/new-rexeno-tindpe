#ifndef CREATE_SESSION_HH_
#define CREATE_SESSION_HH_

#include "view.hh"

#include <QObject>
#include <QLabel>

class CreateSession : public View
{
private:
  
  QLabel *_title;
public:
  CreateSession(QWidget *parent);
  ~CreateSession();
};

#endif
