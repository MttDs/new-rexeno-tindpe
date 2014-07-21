#include "form_square.hh"
#include "controller.hh"

FormSquare::FormSquare(QWidget *parent, Controller *c, QVBoxLayout *parentLayout)
  : FormShape(parent, c, parentLayout)
{
  _type = new QString("Square");
  
  _x = new QLabel("Position en X:");   
  _y = new QLabel("Position en Y:"); 
  _z = new QLabel("Position en Z:"); 
  _r = new QLabel("Red:"); 
  _g = new QLabel("Green:"); 
  _b = new QLabel("blue:");
  _opacity = new QLabel("Opacity:");
  _size = new QLabel("Size:");

  _xField = new QLineEdit("");   
  _yField = new QLineEdit(""); 
  _zField = new QLineEdit(""); 
  _rField = new QLineEdit(""); 
  _gField = new QLineEdit(""); 
  _bField = new QLineEdit("");
  _opacityField = new QLineEdit("");
  _sizeField = new QLineEdit("");

  _layout->addWidget(_x,3,0);
  _layout->addWidget(_xField,3,1);
  _layout->addWidget(_y,4,0);
  _layout->addWidget(_yField,4,1);
  _layout->addWidget(_z,5,0);
  _layout->addWidget(_zField,5,1);
  _layout->addWidget(_r,6,0);
  _layout->addWidget(_rField,6,1);
  _layout->addWidget(_g,7,0);
  _layout->addWidget(_gField,7,1);
  _layout->addWidget(_b,8,0);
  _layout->addWidget(_bField,8,1);
  _layout->addWidget(_opacity,9,0);
  _layout->addWidget(_opacityField,9,1);
  _layout->addWidget(_size,10,0);
  _layout->addWidget(_sizeField,10,1);
  _layout->addWidget(_submit,11,0,1,2);
}

FormSquare::~FormSquare()
{

}

void 
FormSquare::Iniit()
{

}

