#ifndef CONTROLLER_HH_
#define CONTROLLER_HH_

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QObjectList>
#include <QString>
#include <QSignalMapper>
#include <QFileDialog>
#include <QMessageBox>

#include <boost/lexical_cast.hpp>

#include "ui_mainwindow.hh"
#include "view.hh"
#include "error.hh"
#include "protocole.hh"
#include "session.hh"
#include "shape.hh"
#include "event.hh"
#include "parser.hh"
#include "recorder.hh"
#include "model.hh"

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
  vector<View*> _views;
  Ui::MainWindow *_ui;
  int _indexTrial;
  
  Model *_model;
  View *_getView(QString text);

public:
  SessionInfo* sessionInfo;
  Controller(Ui::MainWindow *ui);
  ~Controller();

  void addItem(QString str);
  void updateItem(QString str);
  void deleteItem();

  bool trialExists();
  int getIndexTrial(){return _indexTrial;}

private:
  void _init();

private slots:
  void _render(QString text);
  void _updateLeftBar();
  void _changeCurrentTrial(int index);
  void _loadFile();

signals:
  void fillSessionForm(int);
  void fillComboShapes();
};

#endif 
