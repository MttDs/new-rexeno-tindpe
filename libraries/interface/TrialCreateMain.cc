#include "mainWindow.hh"
#include <wordexp.h>
#include "model.hh"
#include "view.hh"

void
WriteToFile(const string& filename,
            const string& output)
{
  ofstream out(filename.c_str());
  cout << "writing to file" << endl;
  cout << filename << endl;
  out << output << endl;
  out.close();
}

bool askConfirmation()
{
  QMessageBox msgBox;
  //Set text
  msgBox.setText("File already exists..");
  //Set predefined icon, icon is show on left side of text.
  msgBox.setIcon(QMessageBox::Information);
  //set inforative text
  msgBox.setInformativeText("Are you sure you want to replace it with this new trial ?.");
  //Add ok and cancel button.
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  //Set focus of ok button
  msgBox.setDefaultButton(QMessageBox::Ok);
 
  //execute message box. method exec() return the button value of cliecke button
  int ret = msgBox.exec();
 
  //User get input from returned value (ret). you can handle it here.
  switch (ret)
  {
    case QMessageBox::Save:
      return(false);
      break;
    case QMessageBox::Cancel:
      return(false);
      break;
    case QMessageBox::Ok:
      return (true);
      // ok was clicked
      break;
    default:
      cout << "cquoifcctebnibnnz???" << endl;
      break;
  }
  return false;
}

int main(int argc,
         char** argv)
{
  QApplication app(argc, argv);
  //Ui_MainWindow* w = new Ui_MainWindow();
  //QMainWindow qmw;
  Model* m = new Model();
  View* v = new View();
  v->SetModel(m);
  wordexp_t exp_result;
  wordexp("~/.rexeno", &exp_result, 0);

  m->fillAvailableShapes(exp_result.we_wordv[0]);
  m->fillAlreadyExistingTrials(exp_result.we_wordv[0]);
  v->setupUi(v);
  v->show();
  v->Init();
  app.exec();
}

