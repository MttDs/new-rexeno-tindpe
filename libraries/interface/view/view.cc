#include "view.hh"
#include <QFileDialog>
#include <wordexp.h>
#include "popup.hh"

#include <boost/filesystem.hpp>
#include <math.h>       /* pow */

void 
WriteToFile(const string&,
            const string&);

void
View::SetModel(Model* m)
{
  _m = m;
}

View::View()
{
  _m = NULL;
  p = new PopupView;
  p->setupUi(p);
  p->Init();
}

/** 
 * When the user selects a new shape in the combobox, this function displays all the parameters adjustable 
 * for the shape in question
 *
 * @param shapeName : QString, the shape selected by the user
 */
void
View::SetShapeType(QString shapeName)
{
  //QString shapeName = ShapesComboBox->currentText();
  AttributesTableWidget->clear();
  map<string, vector<string> > prototype = _m->shapePrototypes;
  int size = prototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  for (int i = 0; i < size; ++i)
  {
    string curString = prototype[shapeName.toStdString()][i];
    uint pos = curString.find("=");
    if (pos != string::npos)
    {
      string shapeName, shapeValue;
      shapeName = curString.substr(0, pos);
      shapeValue = curString.substr(pos+1);
      QTableWidgetItem *item = new QTableWidgetItem(tr(shapeName.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
      QTableWidgetItem *item2 = new QTableWidgetItem(tr(shapeValue.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 1, item2);
    }
    else
    {
      QTableWidgetItem *item = new QTableWidgetItem(tr(curString.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
    }
  }
}

/** 
 * Initializes the interface default values and connects slots to signals
 * 
 */
void
View::Init()
{
  connect(OKButton, SIGNAL(clicked()), (View*) this, SLOT(Hello()));
  connect(ShapesComboBox, SIGNAL(currentIndexChanged(QString)), (View*) this, SLOT(SetShapeType(QString)));
  connect(AddShapeButton, SIGNAL(clicked()), (View*) this, SLOT(AddShape()));
  connect(ClearButton, SIGNAL(clicked()), (View*) this, SLOT(Clear()));
  connect(DeleteShapeButton, SIGNAL(clicked()), (View*) this, SLOT(DeleteShape()));
  connect(UpButton, SIGNAL(clicked()), (View*) this, SLOT(Up()));
  connect(BottomButton, SIGNAL(clicked()), (View*) this, SLOT(Down()));
  connect(EditShapeButton, SIGNAL(clicked()), (View*) this, SLOT(Edit()));
  connect(SaveButton, SIGNAL(clicked()), (View*) this, SLOT(Save()));
  connect(TrialNameComboBox, SIGNAL(currentIndexChanged(QString)), (View*) this, SLOT(LoadTrial(QString)));

  //this->TrialNameComboBox->setText(_m->trialName().c_str());
  vector<string>::const_iterator it;
  const vector<string>& shapes = _m->availableShapes();
  for (it = shapes.begin(); it != shapes.end(); ++it)
    this->ShapesComboBox->addItem(it->c_str());
  const vector<string>& trials = _m->availableTrials();
  this->TrialNameComboBox->addItem("<new trial>");
  for (it = trials.begin(); it != trials.end(); ++it)
    this->TrialNameComboBox->addItem(it->c_str());
}

void
View::Hello()
{
  cout << "hello" << endl;
}

/** 
 * Adds a shape and its parameters to the current protocole (represented by a list of shapes)
 * 
 */
void
View::AddShape()
{
  vector<string> newShape;
  QString shapeName = ShapesComboBox->currentText();
  QString newLine = shapeName;
  map<string, vector<string> > prototype = _m->shapePrototypes;
  int size = prototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  newShape.push_back(shapeName.toStdString());
  for (int i = 0; i < size; ++i)
  {
    QTableWidgetItem *item = AttributesTableWidget->item(i, 1);
    QString curArg = item->text();
    newShape.push_back(curArg.toStdString());
  }
  _m->protocole.push_back(newShape);
  DrawProtocole();
}

void
View::DrawProtocole()
{
  //QString shapeName = ShapesComboBox->currentText();
  QString shapeName;
  ShapesListWidget->clear();
  vector<vector<string> >::iterator it;
  int lineNumber = 0;
  for (it = _m->protocole.begin(); it != _m->protocole.end(); ++it, ++lineNumber)
  {
    vector<string>& curVect = *it;
    vector<string>::iterator it2;
    QString newLine = shapeName + " ";
    for (it2 = curVect.begin(); it2 != curVect.end(); ++it2)
      newLine += (*it2 + " ").c_str();
    ShapesListWidget->insertItem(lineNumber, newLine);
  }
}

void
View::Clear()
{
  _m->protocole.clear();
  DrawProtocole();
}

void
View::DeleteShape()
{
  int curRow = ShapesListWidget->currentRow();
  if (curRow != -1)
  {
    _m->protocole.erase(_m->protocole.begin() + curRow);
    DrawProtocole();
  }
}

void
View::Up()
{
  int curRow = ShapesListWidget->currentRow();
  if ((curRow) && (curRow != -1))
  {
    vector<string> tmp;
    tmp = _m->protocole[curRow];
    _m->protocole[curRow] = _m->protocole[curRow - 1];
    _m->protocole[curRow - 1] = tmp;
    DrawProtocole();
  }
}

void
View::Down()
{
  int curRow = ShapesListWidget->currentRow();
  int size = _m->protocole.size() - 1;;
  if ((curRow != size) && (curRow != -1))
  {
    vector<string> tmp;
    tmp = _m->protocole[curRow];
    _m->protocole[curRow] = _m->protocole[curRow + 1];
    _m->protocole[curRow + 1] = tmp;
    DrawProtocole();
  }
}

void
View::Edit()
{
  AttributesTableWidget->clear();

  int curRow = ShapesListWidget->currentRow();
  vector<string> curShape = _m->protocole[curRow];
  QString shapeName(curShape[0].c_str());
  cout << curShape[0] << endl;
  map<string, vector<string> > prototype = _m->shapePrototypes;
  int size = prototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  for (int i = 0; i < size; ++i)
  {
    string curString = prototype[shapeName.toStdString()][i];
    uint pos = curString.find("=");
    if (pos != string::npos)
    {
      string shapeName, shapeValue;
      shapeName = curString.substr(0, pos);
      shapeValue = curString.substr(pos+1);
      QTableWidgetItem *item = new QTableWidgetItem(tr(shapeName.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
    }
    else
    {
      QTableWidgetItem *item = new QTableWidgetItem(tr(curString.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
    }
  }

  vector<string>::iterator it;
  int i = 0;
  for (it = curShape.begin() + 1; it != curShape.end(); ++it, ++i)
  {
    string shapeValue = *it;
    QTableWidgetItem *item2 = new QTableWidgetItem(tr(shapeValue.c_str()).arg(pow(1, 0)));
    AttributesTableWidget->setItem(i, 1, item2);
  }
}

/** 
 * Saves a trial to file by constructiong a string and then by calling a popup for confirmation
 * the popup will then call the write to file for effective IO operation
 */
void
View::Save()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::AnyFile);

  //string filename(_m->trialName().c_str());
  string filename(this->TrialNameComboBox->currentText().toStdString());
  
  // QFile f( filename );
  // f.open( QIODevice::WriteOnly );

  string res;
  QString shapeName;
  ShapesListWidget->clear();
  vector<vector<string> >::iterator it;
  int lineNumber = 0;
  for (it = _m->protocole.begin(); it != _m->protocole.end(); ++it, ++lineNumber)
  {
    vector<string>& curVect = *it;
    vector<string>::iterator it2;
    for (it2 = curVect.begin(); it2 != curVect.end(); ++it2)
      res += (*it2 + " ").c_str();
    res += "\n";
  }
  p->Check(filename, res);
}


void
PopupView::Check(const string& filename,
                 const string& output)
{
  if (filename == "<new trial>")
  {
    this->_content = output;
    this->show();
  }
}


void
View::LoadTrial(const QString& s)
{
  cout << "loading trial" << endl;

  wordexp_t exp_result;
  wordexp("~", &exp_result, 0);
  string rexenoDir = exp_result.we_wordv[0];
  rexenoDir += "/.rexeno/trial_types/";
  string filename(rexenoDir + this->TrialNameComboBox->currentText().toStdString());
  ifstream infile((filename).c_str());

  string sLine;
  if (!infile.good())
    return;
  int lineNumber = 0;
  while (!infile.eof())
  {
    getline(infile, sLine);
    QString newLine = QString::fromStdString(sLine);
    if (sLine != "")
    {
      cout << "my line is : " << newLine.toStdString() << endl;
      ShapesListWidget->insertItem(lineNumber++, newLine);

      vector<string> newShape;
      QString shapeName = ShapesComboBox->currentText();
      QString newLine = shapeName;
      map<string, vector<string> > prototype = _m->shapePrototypes;
      int size = prototype[shapeName.toStdString()].size() - 1;
      AttributesTableWidget->setRowCount(size);
      newShape.push_back(shapeName.toStdString());
      for (int i = 0; i < size; ++i)
      {
        QTableWidgetItem *item = AttributesTableWidget->item(i, 1);
        QString curArg = item->text();
        newShape.push_back(curArg.toStdString());
      }
      _m->protocole.push_back(newShape);
      DrawProtocole();

    }
  }



}

// Popup Code


PopupView::PopupView()
{

}


// PopupView::~PopupView()
// {

// }

void
PopupView::SetModel()
{
  //this->hide();
}

void
PopupView::Save()
{
  wordexp_t exp_result;
  wordexp("~", &exp_result, 0);
  string rexenoDir = exp_result.we_wordv[0];
  rexenoDir += "/.rexeno/trial_types/";
  cout << lineEdit->displayText().toStdString() << endl;
  string filename = lineEdit->displayText().toStdString();
  if (boost::filesystem::exists(rexenoDir + filename)) 
  {
    if (askConfirmation())
      WriteToFile(rexenoDir + filename, _content);
  }
  else
  {
    WriteToFile(rexenoDir + filename, _content);
  }
  this->hide();
}

void
PopupView::Cancel()
{
  this->hide();
}

void
PopupView::Init()
{
  connect(SaveButton, SIGNAL(clicked()), (PopupView*) this, SLOT(Save()));
}
