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
  QGridLayout *grid;
  
  QAction* showCreateProtocole;
  QAction* showCreateSession;
  QAction* save;

  // Left bar

  QGridLayout *gridLeftBar;

  QLabel *frequency;
  QLabel *screenWidth;
  QLabel *screenHeight;
  QLabel *nbScreens;
  QLabel *nbTrials;
  QLabel *shuffle;
  QLabel *saveLabel;
  
  QLabel *frequencyField;
  QLabel *screenWidthField;
  QLabel *screenHeightField;
  QLabel *nbScreensField;
  QLabel *nbTrialsField;
  QLabel *shuffleField;
  QLabel *saveField;

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
    
    showCreateProtocole = new QAction("Nouveau protocole", MainWindow);
    showCreateProtocole->setShortcut(QKeySequence("Ctrl+N+P"));
 
    showCreateSession = new QAction("Nouvelle session", MainWindow);
    showCreateSession->setShortcut(QKeySequence("Ctrl+N+S"));  

    save = new QAction("Sauvegarder", MainWindow);
    save->setShortcut(QKeySequence("Ctrl-S"));

    mainToolBar->addAction(showCreateProtocole);
    mainToolBar->addAction(showCreateSession);
    mainToolBar->addAction("Nouvelle forme");
    mainToolBar->addAction(save);

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
    grid->addWidget(infosBar, 0, 0, 1, 1);
    grid->addWidget(contentBar, 0, 1, 1, 3);
    
    centralWidget->setLayout(grid);

    MainWindow->setCentralWidget(centralWidget);
    
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);
    retranslateUi(MainWindow);
    
    InitLeftBar(infosBar);

    QMetaObject::connectSlotsByName(MainWindow);

  } // setupUi

  void InitLeftBar(QWidget* infosBar)
  {
    gridLeftBar = new QGridLayout(infosBar);
  
    frequency = new QLabel("Rafraichissement de l'écran (frequency=)");
    screenWidth = new QLabel("Largeur de l'écran (width=)");
    screenHeight = new QLabel("Hauteur de l'écran (height=)");
    nbScreens = new QLabel("Nombre d'écran (nb_screens=)");
    nbTrials = new QLabel("Nombre d'essai (nb_trials=)");
    shuffle = new QLabel("Ordre d'affichage des sessions (shuffle=)");
    saveLabel = new QLabel("Dossier de sauvegarde des données");

    frequencyField = new QLabel("");
    screenWidthField = new QLabel("");
    screenHeightField = new QLabel("");
    nbScreensField = new QLabel("");
    nbTrialsField = new QLabel("");
    shuffleField = new QLabel("");
    saveField = new QLabel("");

    gridLeftBar->addWidget(frequency,0,0);
    gridLeftBar->addWidget(frequencyField,0,1);
    gridLeftBar->addWidget(screenWidth,1,0);
    gridLeftBar->addWidget(screenWidthField,1,1);
    gridLeftBar->addWidget(screenHeight,2,0);
    gridLeftBar->addWidget(screenHeightField,2,1);
    gridLeftBar->addWidget(nbScreens,3,0);
    gridLeftBar->addWidget(nbScreensField,3,1);
    gridLeftBar->addWidget(nbTrials,4,0);
    gridLeftBar->addWidget(nbTrialsField,4,1);
    gridLeftBar->addWidget(shuffle,5,0);
    gridLeftBar->addWidget(shuffleField,5,1);
    gridLeftBar->addWidget(saveLabel,6,0);  
    gridLeftBar->addWidget(saveField,6,1);
  }
  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QApplication::translate("Interface", "Interface", 0, QApplication::UnicodeUTF8));
  } // retranslateUi
  
};

namespace Ui {
  class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
