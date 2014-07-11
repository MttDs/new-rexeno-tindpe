#ifndef CREATE_PROTOCOLE_HH_
# define CREATE_PROTOCOLE_HH_

#include <QObject>
#include <QWidget>
#include <QLabel>
class CreateProtocole : public QWidget
{
  Q_OBJECT
public: 
  CreateProtocole(QWidget *parent);
  ~CreateProtocole();

  QLabel* test;

  void display();
public slots:
  void teest(){
    test->setText("youpi!");
  }



};

#endif
