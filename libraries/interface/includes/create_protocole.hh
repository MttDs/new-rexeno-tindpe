#ifndef CREATE_PROTOCOLE_HH_
# define CREATE_PROTOCOLE_HH_

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class CreateProtocole : public QWidget
{
  Q_OBJECT
public: 

  QLabel *frequency;
  QLabel *screenWidth;
  QLabel *screenHeight;
  QLabel *nbScreens;
  QLabel *nbTrials;
  QLabel *shuffle;
  QLabel *save;

  CreateProtocole(QWidget *parent);
  ~CreateProtocole();
};

#endif
