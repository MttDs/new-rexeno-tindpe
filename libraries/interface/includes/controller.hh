#ifndef  CONTROLLER_HH_
# define CONTROLLER_HH_

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include "ui_mainwindow.hh"

#include <iostream>

using namespace std;
class Controller : public QObject
{
Q_OBJECT
public:
  Ui::MainWindow* _ui;

  Controller(Ui::MainWindow* ui);
  ~Controller();
  void Init();

public slots:
  void render();
};

#endif 
