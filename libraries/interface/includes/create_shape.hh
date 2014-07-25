#ifndef CREATE_SHAPE_HH_
# define CREATE_SHAPE_HH_

#include "view.hh"
#include "form_shape.hh"
#include "form_sphere.hh"
#include "form_square.hh"
#include "form_plan.hh"
#include "parser.hh"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QObject>
#include <QVBoxLayout>

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
using namespace configuration;
class CreateShape : public View
{
Q_OBJECT
private:
  QComboBox *_comboShapes;
  QComboBox *_comboShapesEdit;

  QVBoxLayout *_layout;
  vector<FormShape*> _formShapes;
  int _lastIndex;

public:
  CreateShape(QWidget *parent, Controller *c);
  ~CreateShape();
  
  void beforeDisplay();
private:
  void _init();

private slots:
  void _showFormShape(int index);
  void _hideFormShape(int index);

public slots:
  void fillFormShape(int index);
  void loadComboShapesEdit();
};
#endif
