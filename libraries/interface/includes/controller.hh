#ifndef  CONTROLLER_HH_
# define CONTROLLER_HH_

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QObjectList>
#include <QString>
#include <QSignalMapper>

#include "ui_mainwindow.hh"
#include "view.hh"
#include "create_protocole.hh"
#include "create_session.hh"
#include "error.hh"

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class Controller : public QObject
{
  Q_OBJECT
private:
  QWidget *_viewWidget;
  vector<View*> _views;

public:
  Ui::MainWindow* _ui;

  Controller(Ui::MainWindow *ui);
  ~Controller();
  void Init();

private:
  View* _getView(QString text);

private slots:
  void _render(QString text);
};

#endif 
