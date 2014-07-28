#ifndef VIEW_HH_
# define VIEW_HH_

#include "parser.hh"

#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

using namespace configuration;
using namespace std;

class Controller;
class View : public QWidget
{
  Q_OBJECT
protected:
  Controller *_controller;
  QPushButton *_submit;
  QPushButton *_buttonDelete;

  vector<QLineEdit*> _fields;

  TrialInfo* _getCurrentTrial();
  bool _isValid();
public:
  View(QWidget *parent);

  View(QWidget *parent, Controller* con);
  ~View();
  const char* name;
  virtual void beforeDisplay();
};



#endif
