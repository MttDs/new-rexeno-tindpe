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
#include <QComboBox>
#include <QObject>
#include <QVBoxLayout>
#include <QSizePolicy>

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
  QWidget *leftWidget;
  QWidget *mainWidget;
  QWidget *centralWidget;
  QStatusBar *statusBar;
  QHBoxLayout *layout;
  
  QAction* showCreateProtocole;
  QAction* showCreateSession;
  QAction* showCreateShape;
  QAction* save;

  // Left bar

  QVBoxLayout *leftWidgetLayout;

  QLabel *frequency;
  QLabel *screenWidth;
  QLabel *screenHeight;
  QLabel *nbScreens;
  QLabel *nbTrials;
  QLabel *shuffle;
  QLabel *saveLabel;
  QLabel *nbSessions;

  QLabel *comboLabel;
  QLabel *frequencyField;
  QLabel *screenWidthField;
  QLabel *screenHeightField;
  QLabel *nbScreensField;
  QLabel *nbTrialsField;
  QLabel *shuffleField;
  QLabel *saveField;
  QLabel *nbSessionsField;
 
  QComboBox *comboTrials;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->setFixedSize(900, 650);

    menuFile = new QMenu("&File");
    menuFile->addAction("Nouveau");
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->addMenu(menuFile);
    
    MainWindow->setMenuBar(menuBar);

    mainToolBar = new QToolBar(MainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    
    showCreateProtocole = new QAction("Nouveau protocole", MainWindow);
    showCreateSession = new QAction("Nouvelle session", MainWindow);
    showCreateShape = new QAction("Ajouter une forme", MainWindow);

    save = new QAction("Sauvegarder", MainWindow);
    save->setShortcut(QKeySequence("Ctrl-S"));

    mainToolBar->addAction(showCreateProtocole);
    mainToolBar->addAction(showCreateSession);
    mainToolBar->addAction(showCreateShape);
    mainToolBar->addAction(save);

    MainWindow->addToolBar(mainToolBar);

    leftWidget = new QWidget;
    mainWidget = new QWidget;
    leftWidget->setStyleSheet("border-right: 1px solid black;");
    mainWidget->setStyleSheet("border-right: 1px solid black;;");
    centralWidget = new QWidget(MainWindow);

    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
 
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(0.5);
    leftWidget->setSizePolicy(spLeft);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2.5);
    mainWidget->setSizePolicy(spRight);

    layout = new QHBoxLayout;
 
    layout->addWidget(leftWidget);
    layout->addWidget(mainWidget);
    
    centralWidget->setLayout(layout);

    MainWindow->setCentralWidget(centralWidget);
    
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);
    retranslateUi(MainWindow);
    
    InitLeftBar(leftWidget);

    QMetaObject::connectSlotsByName(MainWindow);

  } // setupUi

  void InitLeftBar(QWidget* leftWidget)
  {
    leftWidgetLayout = new QVBoxLayout(leftWidget);
  
    comboLabel = new QLabel("Editer la session:");
    nbSessions = new QLabel("Nombre de sessions:");
    frequency = new QLabel("Rafraichissement de l'écran:");
    screenWidth = new QLabel("Largeur de l'écran:");
    screenHeight = new QLabel("Hauteur de l'écran:");
    nbScreens = new QLabel("Nombre d'écran:");
    nbTrials = new QLabel("Nombre d'essai:");
    shuffle = new QLabel("Ordre d'affichage des sessions:");
    saveLabel = new QLabel("Dossier de sauvegarde des données:");

    frequencyField = new QLabel("");
    screenWidthField = new QLabel("");
    screenHeightField = new QLabel("");
    nbScreensField = new QLabel("");
    nbTrialsField = new QLabel("");
    shuffleField = new QLabel("");
    saveField = new QLabel("");
    nbSessionsField = new QLabel("0");

    comboTrials = new QComboBox;
    comboTrials->addItem("/");

    leftWidgetLayout->addWidget(new QLabel("Les sessions:"));
    leftWidgetLayout->addWidget(comboTrials);
    leftWidgetLayout->addWidget(nbSessions);
    leftWidgetLayout->addWidget(nbSessionsField);
    leftWidgetLayout->addWidget(frequency);
    leftWidgetLayout->addWidget(frequencyField);
    leftWidgetLayout->addWidget(screenWidth);
    leftWidgetLayout->addWidget(screenWidthField);
    leftWidgetLayout->addWidget(screenHeight);
    leftWidgetLayout->addWidget(screenHeightField);
    leftWidgetLayout->addWidget(nbScreens);
    leftWidgetLayout->addWidget(nbScreensField);
    leftWidgetLayout->addWidget(nbTrials);
    leftWidgetLayout->addWidget(nbTrialsField);
    leftWidgetLayout->addWidget(shuffle);
    leftWidgetLayout->addWidget(shuffleField);
    leftWidgetLayout->addWidget(saveLabel);  
    leftWidgetLayout->addWidget(saveField);

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
