#include "form_sphere.hh"
#include "controller.hh"

FormSphere::FormSphere(QWidget *parent, Controller *c, QVBoxLayout *parentLayout)
  : FormShape(parent, c, parentLayout)
{
  _type = new QString("Sphere");

  _minStart = new QLabel("Random min: ");
  _maxStart = new QLabel("Random max:");
  _x = new QLabel("centre X:");
  _z = new QLabel("centre Z:");
  _randomX = new QLabel("Random center min:");
  _randomZ = new QLabel("Random center max:");
  _stacks = new QLabel("Précision de la sphére horizontale:");
  _slices = new QLabel("Précision de la sphère verticale:");
  _radius = new QLabel("Rayon:");
  _veloX = new QLabel("Vitesse en X:");
  _veloZ = new QLabel("Vitesse en Y:");

  _minStartField = new QLineEdit("0");
  _maxStartField = new  QLineEdit("60");
  _xField = new QLineEdit("2");
  _zField = new QLineEdit("0");
  _randomXField = new QLineEdit("0.2");
  _randomZField = new QLineEdit("0");
  _stacksField = new QLineEdit("20");
  _slicesField = new QLineEdit("20");
  _radiusField = new QLineEdit("0.2");
  _veloXField = new QLineEdit("0.4");
  _veloZField = new QLineEdit("0");

  _layout->addWidget(_minStart, 3,0);
  _layout->addWidget(_minStartField,3,1);
  _layout->addWidget(_maxStart, 4,0);
  _layout->addWidget(_maxStartField,4,1);
  _layout->addWidget(_x,5,0);
  _layout->addWidget(_xField,5,1);
  _layout->addWidget(_z,6,0);
  _layout->addWidget(_zField,6,1);
  _layout->addWidget(_randomX,7,0);
  _layout->addWidget(_randomXField,7,1);
  _layout->addWidget(_randomZ,8,0);
  _layout->addWidget(_randomZField,8,1);
  _layout->addWidget(_stacks,9,0);
  _layout->addWidget(_stacksField,9,1);
  _layout->addWidget(_slices,10,0);
  _layout->addWidget(_slicesField,10,1);
  _layout->addWidget(_radius,11,0);
  _layout->addWidget(_radiusField,11,1);
  _layout->addWidget(_veloX,12,0);
  _layout->addWidget(_veloXField,12,1);
  _layout->addWidget(_veloZ,13,0);
  _layout->addWidget(_veloZField,13,1);
  _layout->addWidget(_submit,14,0,1,2);

  Init();
}

FormSphere::~FormSphere()
{

}


void 
FormSphere::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
}

void
FormSphere::_save()
{
  if (_controller->getIndexTrial() >= 0 )
    {
      vector<TrialInfo>* trials = &_controller->sessionInfo->trials;
      TrialInfo* ti = &trials->at(_controller->getIndexTrial());
      ShapeInfo si;

      si.name =  _type->toUtf8().constData();
      si.attributes.push_back(_nameField->text().toUtf8().constData());
      si.attributes.push_back(_minStartField->text().toUtf8().constData());
      si.attributes.push_back(_maxStartField->text().toUtf8().constData());
      si.attributes.push_back(_xField->text().toUtf8().constData());
      si.attributes.push_back(_zField->text().toUtf8().constData());
      si.attributes.push_back(_randomXField->text().toUtf8().constData());
      si.attributes.push_back(_randomZField->text().toUtf8().constData());
      si.attributes.push_back(_frameStartField->text().toUtf8().constData());
      si.attributes.push_back(_frameEndField->text().toUtf8().constData());
      si.attributes.push_back(_stacksField->text().toUtf8().constData());
      si.attributes.push_back(_slicesField->text().toUtf8().constData());
      si.attributes.push_back(_radiusField->text().toUtf8().constData());
      si.attributes.push_back(_veloXField->text().toUtf8().constData());
      si.attributes.push_back(_veloZField->text().toUtf8().constData());
      ti->shapes.push_back(si);
      std::cout << "add sphere" << std::endl;
    }
  else{
    std::cout << "pas de session selectionnééée" << std::endl;
  }
}