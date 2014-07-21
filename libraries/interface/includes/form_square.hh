#ifndef FORM_SQUARE_HH_
# define FORM_SQUARE_HH_

#include "form_shape.hh"

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
class FormSquare : public FormShape
{
Q_OBJECT
public:
  FormSquare(QWidget *parent, Controller *c, QVBoxLayout *parentLayout);
  ~FormSquare();

  void Init();
protected:

private:
  QLabel *_x;
  QLabel *_y;
  QLabel *_z;
  QLabel *_r;
  QLabel *_g;
  QLabel *_b;
  QLabel *_opacity;
  QLabel *_size;

  QLineEdit *_xField;
  QLineEdit *_yField;
  QLineEdit *_zField;
  QLineEdit *_rField;
  QLineEdit *_gField;
  QLineEdit *_bField;
  QLineEdit *_opacityField;
  QLineEdit *_sizeField;

private slots:
  void _save();
};
#endif
