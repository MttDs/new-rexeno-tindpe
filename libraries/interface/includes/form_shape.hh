#ifndef FORM_SHAPE_HH_
# define FORM_SHAPE_HH_


#include "view.hh"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QPushButton>

class FormShape : public View
{
public:
  FormShape(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormShape();

  void Init();
  void activate();
  void inactivate();

protected:
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
};
#endif
