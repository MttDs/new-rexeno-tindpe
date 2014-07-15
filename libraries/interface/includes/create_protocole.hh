#ifndef CREATE_PROTOCOLE_HH_
# define CREATE_PROTOCOLE_HH_

#include <iostream>

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit> 
#include <QPushButton>
#include <QGridLayout>
#include <QtDebug>
#include "view.hh"

class CreateProtocole : public View
{
Q_OBJECT
private: 

  QGridLayout *_gridForm;
  QPushButton *_submit;

  QLabel *_frequency;
  QLabel *_screenWidth;
  QLabel *_screenHeight;
  QLabel *_nbScreens;
  QLabel *_nbTrials;
  QLabel *_shuffle;
  QLabel *_save;
  
  QLineEdit *_frequencyField;
  QLineEdit *_screenWidthField;
  QLineEdit *_screenHeightField;
  QLineEdit *_nbScreensField;
  QLineEdit *_nbTrialsField;
  QLineEdit *_shuffleField;
  QLineEdit *_saveField;
   
public:
  CreateProtocole(QWidget *parent, Controller *c);
  ~CreateProtocole();
  void Init();

public slots:
  void save();
};

#endif
