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

  _xField = new QLineEdit("0");   
  _yField = new QLineEdit("0"); 
  _zField = new QLineEdit("-4"); 
  _rField = new QLineEdit("255"); 
  _gField = new QLineEdit("255"); 
  _bField = new QLineEdit("0");
  _opacityField = new QLineEdit("0.5");
  _sizeField = new QLineEdit("0.2");

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

  Init();
}

FormSquare::~FormSquare()
{

}

void 
FormSquare::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
}

void
FormSquare::_save()
{
  if (_controller->getIndexTrial() >= 0 )
    {
      vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
      TrialInfo* ti = &trials->at(_controller->getIndexTrial());
      ShapeInfo si;

      si.name =  _type->toUtf8().constData();
      si.attributes.push_back(_nameField->text().toUtf8().constData());
      si.attributes.push_back(_xField->text().toUtf8().constData());
      si.attributes.push_back(_yField->text().toUtf8().constData());
      si.attributes.push_back(_zField->text().toUtf8().constData());
      si.attributes.push_back(_frameStartField->text().toUtf8().constData());
      si.attributes.push_back(_frameEndField->text().toUtf8().constData());
      si.attributes.push_back(_rField->text().toUtf8().constData());
      si.attributes.push_back(_gField->text().toUtf8().constData());
      si.attributes.push_back(_bField->text().toUtf8().constData());
      si.attributes.push_back(_opacityField->text().toUtf8().constData());
      si.attributes.push_back(_sizeField->text().toUtf8().constData());
      ti->shapes.push_back(si);
      std::cout << "add square" << std::endl;
    }
  else{
    std::cout << "pas de session selectionnééée" << std::endl;
  }
}