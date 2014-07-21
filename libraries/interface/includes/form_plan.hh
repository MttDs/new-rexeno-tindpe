#ifndef FORM_PLAN_HH_
# define FORM_PLAN_HH_

#include "form_shape.hh"

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class FormPlan : public FormShape
{
public:
  FormPlan(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormPlan();

  void Iniit();

private:
  QLabel *_minStart;
  QLabel *_maxStart;
  QLabel *_x;
  QLabel *_y;
  QLabel *_width;
  QLabel *_height;
  QLabel *_repeat;

  QLineEdit *_minStartField;
  QLineEdit *_maxStartField;
  QLineEdit *_xField;
  QLineEdit *_yField;
  QLineEdit *_widthField;
  QLineEdit *_heightField;
  QLineEdit *_repeatField;
 
};

#endif

