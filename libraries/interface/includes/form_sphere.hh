#ifndef FORM_SPHERE_HH_
# define FORM_SPHERE_HH_

#include "form_shape.hh"
#include "parser.hh"

#include <vector>

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

using namespace configuration;

class FormSphere : public FormShape
{
Q_OBJECT
public:
  FormSphere(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormSphere();

  void Init();
  void fillForm(ShapeInfo* si, int index);
  void reset();

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

private slots:
  void _save();
};
#endif
