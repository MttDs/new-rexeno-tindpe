#ifndef  CONTROLLER_HH_
# define CONTROLLER_HH_

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QObjectList>
#include <QString>
#include <QSignalMapper>

#include <boost/lexical_cast.hpp>

#include "ui_mainwindow.hh"
#include "view.hh"
#include "create_protocole.hh"
#include "create_session.hh"
#include "error.hh"
#include "parser.hh"
#include "recorder.hh"

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
using namespace configuration;
using namespace boost; 

class Controller : public QObject
{
  Q_OBJECT
private:
  QWidget *_viewWidget;
  vector<View*> _views;
  Ui::MainWindow* _ui;
  Recorder* _recorder;
  View* _getView(QString text);

public:
  SessionInfo* sessionInfo;
  Controller(Ui::MainWindow *ui);
  ~Controller();
  void Init();
  void hello(){std::cout << "hello" <<std::endl;}

private slots:
  void _render(QString text);
  void _save();
  void _updateLeftBar();

};

#endif 
