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

  _layout->addWidget(_name,0,0);
  _layout->addWidget(_nameField,0,1);
  _layout->addWidget(_x,1,0);
  _layout->addWidget(_xField,1,1);
  _layout->addWidget(_y,2,0);
  _layout->addWidget(_yField,2,1);
  _layout->addWidget(_z,3,0);
  _layout->addWidget(_zField,3,1);
  _layout->addWidget(_frameStart,4,0);
  _layout->addWidget(_frameStartField,4,1) ;
  _layout->addWidget(_frameEnd,5,0);
  _layout->addWidget(_frameEndField,5,1);
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
     
      std::cout << "add square" << std::endl;
      if (_index!=-1)
	{
	  std::cout << "Je dois remplacer " << _index << std::endl;
	  ti->shapes.at(_index) = si;
	  _index=-1;
	}
      else
	{
	  std::cout << "add normal" << std::endl;
	  ti->shapes.push_back(si);
	}
      reset();
      FormShape::_save();
    }
  else{
    std::cout << "pas de session selectionnééée" << std::endl;
  }
}

void
FormSquare::fillForm(ShapeInfo* si, int index)
{
  _index = index;
  std::cout << "fill form index " << _index << std::endl;
  QString str;
  _nameField->setText(str = si->attributes[0].c_str());
  _xField->setText(str = si->attributes[1].c_str());
  _yField->setText(str = si->attributes[2].c_str());
  _zField->setText(str = si->attributes[3].c_str());
  _frameStartField->setText(str = si->attributes[4].c_str());
  _frameEndField->setText(str = si->attributes[5].c_str());
  _rField->setText(str = si->attributes[6].c_str());
  _gField->setText(str = si->attributes[7].c_str());
  _bField->setText(str = si->attributes[8].c_str());
  _opacityField->setText(str = si->attributes[9].c_str());
  _sizeField->setText(str = si->attributes[10].c_str());
}

void
FormSquare::reset()
{  
  _nameField->setText("Plan");
  _xField->setText("0");
  _yField->setText("0");
  _zField->setText("-5");
  _frameStartField->setText("0");
  _frameEndField->setText("-1");
  _rField->setText("255");
  _gField->setText("255");
  _bField->setText("0");
  _opacityField->setText("0.5");
  _sizeField->setText("0.2");

}
