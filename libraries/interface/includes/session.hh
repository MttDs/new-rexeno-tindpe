#ifndef SESSION_VIEW_HH_
#define SESSION_VIEW_HH_

#include "view.hh"

#include <QtDebug>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

#include <iostream>
#include <vector>
#include <string>

class SessionView : public View
{
Q_OBJECT
private:
  QVBoxLayout *_gridForm;
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

  QPushButton *_deleteSession;

public:
  SessionView(QWidget *parent, Controller *c);
  ~SessionView();

private:
  void _init();

private slots:
  void _save();
  void _delete();

public slots:
  void fillForm(int index);
  void reset();

signals:
  void changeLeftBar();

};

#endif
