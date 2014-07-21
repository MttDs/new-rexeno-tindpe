#ifndef FORM_SPHERE_HH_
# define FORM_SPHERE_HH_

#include "form_shape.hh"

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class FormSphere : public FormShape
{
public:
  FormSphere(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormSphere();

  void Iniit();
protected:

private:
  QLabel *_minStart;
  QLabel *_maxStart;
  QLabel *_x;
  QLabel *_z;
  QLabel *_randomX;
  QLabel *_randomZ;
  QLabel *_stacks;
  QLabel *_slices;
  QLabel *_radius;
  QLabel *_veloX;
  QLabel *_veloZ;

  QLineEdit *_minStartField;
  QLineEdit *_maxStartField;
  QLineEdit *_xField;
  QLineEdit *_zField;
  QLineEdit *_randomXField;
  QLineEdit *_randomZField;
  QLineEdit *_stacksField;
  QLineEdit *_slicesField;
  QLineEdit *_radiusField;
  QLineEdit *_veloXField;
  QLineEdit *_veloZField;



};
#endif
