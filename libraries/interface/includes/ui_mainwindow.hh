/********************************************************************************
 ** Form generated from reading UI file 'mainwindow.ui'
 **
 ** Created: Thu Jul 10 09:49:06 2014
 **      by: Qt User Interface Compiler version 4.6.2
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_MAINWINDOW_HH_
# define UI_MAINWINDOW_HH_

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QGridLayout>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QObject>

#include <iostream>

#include "create_protocole.hh"
using namespace std;

QT_BEGIN_NAMESPACE

#include "controller.hh"

class Controller;

class Ui_MainWindow
{
public:
  QMenu *menuFile;
 
  QMenuBar *menuBar;
  QToolBar *mainToolBar;
  QWidget *infosBar;
  QWidget *contentBar;
  QWidget *centralWidget;
  QStatusBar *statusBar;
  QPushButton *button1;
  QGridLayout *grid;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1200, 800);

    menuFile = new QMenu("&File");
    menuFile->addAction("Nouveau");
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->addMenu(menuFile);
    
    MainWindow->setMenuBar(menuBar);

    mainToolBar = new QToolBar(MainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainToolBar->addAction("Nouveau protocole");
    mainToolBar->addAction("Nouvelle session");
    mainToolBar->addAction("Nouvelle forme");
    MainWindow->addToolBar(mainToolBar);

    infosBar = new QWidget;
    contentBar = new QWidget;
    infosBar->setStyleSheet("border: 1px solid black; border-radius: 10px;");
    contentBar->setStyleSheet("border: 1px solid black; border-radius: 10px;");
    centralWidget = new QWidget(MainWindow);

    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    // CreateProtocole* view = new CreateProtocole(contentBar);
    //view->display();
    grid = new QGridLayout;
    button1 = new QPushButton(infosBar);
    button1->setText("Ici les affaires courantes...");

    grid->addWidget(infosBar, 0, 0, 1, 1);
    grid->addWidget(contentBar, 0, 1, 1, 3);
    
    centralWidget->setLayout(grid);

    MainWindow->setCentralWidget(centralWidget);
    
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);
    retranslateUi(MainWindow);
 
    QMetaObject::connectSlotsByName(MainWindow);

  } // setupUi

  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QApplication::translate("Interface", "Interface", 0, QApplication::UnicodeUTF8));
  } // retranslateUi

  void connectEvts(){
    //    QObject::connect(button1, SIGNAL(clicked()), controller, SLOT(teest()));
  }
};

namespace Ui {
  class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
