#ifndef VIEW_HH_
# define VIEW_HH_

#include "parser.hh"

#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QPushButton>

using namespace configuration;

class Controller;
class View : public QWidget
{
  Q_OBJECT
protected:
  Controller *_controller;
  QPushButton *_submit;
  QPushButton *_buttonDelete;

  TrialInfo* _getCurrentTrial();
public:
  View(QWidget *parent);

  View(QWidget *parent, Controller* con);
  ~View();
  const char* name;
  virtual void beforeDisplay();
};



#endif
