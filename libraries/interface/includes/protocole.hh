#ifndef PROTOCOLE_VIEW_HH_
#define PROTOCOLE_VIEW_HH_

#include <iostream>

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit> 
#include <QPushButton>
#include <QGridLayout>
#include <QtDebug>
#include "view.hh"

class ProtocoleView : public View
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
  QLabel *_savePath;
  
  QLineEdit *_frequencyField;
  QLineEdit *_screenWidthField;
  QLineEdit *_screenHeightField;
  QLineEdit *_nbScreensField;
  QLineEdit *_nbTrialsField;
  QLineEdit *_shuffleField;
  QLineEdit *_savePathField;
   
public:
  ProtocoleView(QWidget *parent, Controller *c);
  ~ProtocoleView();

private:
  void _init();

private slots:
  void _save();

signals:
  void changeLeftBar();

};

#endif
