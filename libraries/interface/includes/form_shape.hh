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
#include <QMessageBox>

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
  virtual void reset() = 0;
protected:
  int _index; // Form
  int _posShape; 
  
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
  QPushButton *_buttonDelete;
  virtual void _save();
private slots:
  void _deleteShape();
signals:
  void afterSave();
};
#endif
