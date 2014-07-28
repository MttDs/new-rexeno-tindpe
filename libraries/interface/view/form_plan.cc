#include "form_plan.hh"
#include "controller.hh"

FormPlan::FormPlan(QWidget *parent, Controller *c, QVBoxLayout *parentLayout)
  : FormShape(parent, c, parentLayout)
{
  _type = new QString("Plan");
  
  _minStart = new QLabel("Random min:");
  _maxStart = new QLabel("Random max:");
  _x = new QLabel("Position x:");
  _y = new QLabel("Position y:");
  _width = new QLabel("Largeur:");
  _height = new QLabel("Longueur:");
  _repeat = new QLabel(QString::fromUtf8("Répétition de la texture"));

  _nameField->setText("Plan");
  _frameStartField->setText("0");
  _frameEndField->setText("-1");
  _minStartField = new QLineEdit("0");
  _maxStartField = new QLineEdit("0");
  _xField = new QLineEdit("0");
  _yField = new QLineEdit("0");
  _widthField = new QLineEdit("40");
  _heightField = new QLineEdit("80");
  _repeatField = new QLineEdit("80");


  _layout->addWidget(_name,0,0);
  _layout->addWidget(_nameField,0,1);
  _layout->addWidget(_minStart,1,0);
  _layout->addWidget(_minStartField,1,1);
  _layout->addWidget(_maxStart,2,0);
  _layout->addWidget(_maxStartField,2,1);
  _layout->addWidget(_x,3,0);
  _layout->addWidget(_xField,3,1);
  _layout->addWidget(_y,4,0);
  _layout->addWidget(_yField,4,1);
  _layout->addWidget(_frameStart,5,0);
  _layout->addWidget(_frameStartField,5,1) ;
  _layout->addWidget(_frameEnd,6,0);
  _layout->addWidget(_frameEndField,6,1);
  _layout->addWidget(_width,7,0);
  _layout->addWidget(_widthField,7,1);
  _layout->addWidget(_height,8,0);
  _layout->addWidget(_heightField,8,1);
  _layout->addWidget(_repeat,9,0);
  _layout->addWidget(_repeatField,9,1);
  _layout->addWidget(_submit,10,0,1,2);
  _layout->addWidget(_buttonDelete,11,0,1,2);

  Init();
}

FormPlan::~FormPlan()
{
 
}

void 
FormPlan::Init()
{
  connect(_submit, SIGNAL(clicked()), this, SLOT(_save()));
}

void
FormPlan::_save()
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
      si.attributes.push_back(_yField->text().toUtf8().constData());
      si.attributes.push_back(_frameStartField->text().toUtf8().constData());
      si.attributes.push_back(_frameEndField->text().toUtf8().constData());
      si.attributes.push_back(_widthField->text().toUtf8().constData());
      si.attributes.push_back(_heightField->text().toUtf8().constData());
      si.attributes.push_back(_repeatField->text().toUtf8().constData());

      if (shapeValid())
	{
	  ti->shapes.at(_index) = si;
	  _controller->setMessage("La forme a bien été modifiée");
	}
      else
	{
	  ti->shapes.push_back(si);
	  _controller->setMessage("Nouvelle forme ajoutée!");
	}
      reset();
      FormShape::_save();
    }
  else{
    QMessageBox::warning(0, tr("Information"), QString::fromUtf8("Impossible, pas de session selectionnée."));
  }
}
void
FormPlan::fillForm(ShapeInfo* si, int index)
{
   _index = index;

  _nameField->setText(si->attributes[0].c_str());
  _minStartField->setText(si->attributes[1].c_str());
  _maxStartField->setText(si->attributes[2].c_str());
  _xField->setText(si->attributes[3].c_str());
  _yField->setText(si->attributes[4].c_str());
  _frameStartField->setText(si->attributes[5].c_str());
  _frameEndField->setText(si->attributes[6].c_str());
  _widthField->setText(si->attributes[7].c_str());
  _heightField->setText(si->attributes[8].c_str());
  _repeatField->setText(si->attributes[9].c_str());

  _buttonDelete->show();
}

void
FormPlan::reset()
{
  _nameField->setText("Plan");
  _minStartField->setText("0");
  _maxStartField->setText("0");
  _xField->setText("0");
  _yField->setText("0");
  _frameStartField->setText("0");
  _frameEndField->setText("-1");
  _widthField->setText("40");
  _heightField->setText("80");
  _repeatField->setText("80");

  _buttonDelete->hide();
  _index=-1;
}
