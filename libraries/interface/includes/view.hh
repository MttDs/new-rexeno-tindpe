#ifndef SESSION_VIEW_HH_
# define SESSION_VIEW_HH_

# include <QObject>
# include <QMainWindow>
#include <QString>

class Controller;
class View : public QWidget
{
  Q_OBJECT
  protected:

  Controller *_controller;
public:
  View(QWidget *parent);

  View(QWidget *parent, Controller* con);
  ~View();
  const char* name;
  virtual void beforeDisplay();
};



#endif /* SESSION_VIEW_HH_ */
