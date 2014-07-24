#ifndef FORM_SHAPE_HH_
# define FORM_SHAPE_HH_

#include <iostream>

#include "view.hh"
#include "parser.hh"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QPushButton>

using namespace configuration;
using namespace std;

class FormShape : public View
{
Q_OBJECT
public:
  FormShape(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormShape();

  void Init();
  void activate();
  void inactivate();
  virtual void fillForm(ShapeInfo* si, int index)=0;
  string getName(){ return _nameField->text().toUtf8().constData();}
  string getType(){ return _type->toUtf8().constData();}
protected:
  int _index;

  QGridLayout *_layout;
  QVBoxLayout *_parentLayout;
  QWidget *_parentWidget;

  QString *_type;

  QLabel *_name;
  QLabel *_frameStart;
  QLabel *_frameEnd;

  QLineEdit *_nameField;
  QLineEdit *_frameStartField;
  QLineEdit *_frameEndField;

  QPushButton *_submit;

  virtual void _save();
signals:
  void afterSave();
};
#endif
