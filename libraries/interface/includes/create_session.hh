#ifndef CREATE_SESSION_HH_
#define CREATE_SESSION_HH_

#include "view.hh"

#include <QtDebug>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

#include <iostream>

#include <vector>

#include <string>
class CreateSession : public View
{
Q_OBJECT
private:
  QGridLayout *_gridForm;
  QPushButton *_submit;

  QLabel *_name;
  QLabel *_veloCameraX;
  QLabel *_veloCameraY;
  QLabel *_veloCameraZ;
  QLabel *_eyeX;
  QLabel *_eyeY;
  QLabel *_eyeZ;
  QLabel *_centerX;
  QLabel *_centerY;
  QLabel *_centerZ;

  QLineEdit *_nameField;
  QLineEdit *_veloCmraXField;
  QLineEdit *_veloCmraYField;
  QLineEdit *_veloCmraZField;
  QLineEdit *_eyeXField;
  QLineEdit *_eyeYField;
  QLineEdit *_eyeZField;
  QLineEdit *_centerXField;
  QLineEdit *_centerYField;
  QLineEdit *_centerZField;
public:
  CreateSession(QWidget *parent, Controller *c);
  ~CreateSession();

  void Init();

public slots:
  void save();

signals:
  void changeLeftBar();

};

#endif
