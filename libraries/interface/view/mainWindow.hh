/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created: Sun Aug 11 16:50:11 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Past;
    QAction *action_Quit;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *Buttons2GridLayout;
    QPushButton *SaveButton;
    QPushButton *QuitButton;
    QComboBox *ShapesComboBox;
    QLabel *ShapeNameLabel;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *ClearButton;
    QPushButton *OKButton;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QPushButton *AddShapeButton;
    QPushButton *DeleteShapeButton;
    QPushButton *EditShapeButton;
    QPushButton *CopyShapeButton;
    QPushButton *UpButton;
    QPushButton *BottomButton;
    QTableWidget *AttributesTableWidget;
    QLabel *TrialNameLabel;
    QLabel *ShapeListLabel;
    QListWidget *ShapesListWidget;
    QPushButton *helpButton;
    QPushButton *colorButton;
    QLabel *ShapeNameLabel_2;
    QTextEdit *textEdit;
    QComboBox *TrialNameComboBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu_Edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(896, 736);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        MainWindow->setPalette(palette);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setCheckable(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setCheckable(false);
        actionOpen->setShortcutContext(Qt::ApplicationShortcut);
        actionOpen->setIconVisibleInMenu(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setCheckable(false);
        action_Cut = new QAction(MainWindow);
        action_Cut->setObjectName(QString::fromUtf8("action_Cut"));
        action_Cut->setCheckable(true);
        action_Copy = new QAction(MainWindow);
        action_Copy->setObjectName(QString::fromUtf8("action_Copy"));
        action_Copy->setCheckable(true);
        action_Past = new QAction(MainWindow);
        action_Past->setObjectName(QString::fromUtf8("action_Past"));
        action_Past->setCheckable(true);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setCheckable(false);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(550, 560, 251, 62));
        Buttons2GridLayout = new QGridLayout(layoutWidget);
        Buttons2GridLayout->setObjectName(QString::fromUtf8("Buttons2GridLayout"));
        Buttons2GridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        Buttons2GridLayout->setContentsMargins(0, 0, 0, 0);
        SaveButton = new QPushButton(layoutWidget);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Purisa"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        SaveButton->setFont(font);
        SaveButton->setCursor(QCursor(Qt::PointingHandCursor));

        Buttons2GridLayout->addWidget(SaveButton, 0, 0, 1, 1);

        QuitButton = new QPushButton(layoutWidget);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        QuitButton->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Purisa"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        QuitButton->setFont(font1);
        QuitButton->setCursor(QCursor(Qt::PointingHandCursor));
        QuitButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 75 12pt \"Purisa\";"));

        Buttons2GridLayout->addWidget(QuitButton, 0, 1, 1, 1);

        ShapesComboBox = new QComboBox(centralwidget);
        ShapesComboBox->setObjectName(QString::fromUtf8("ShapesComboBox"));
        ShapesComboBox->setGeometry(QRect(120, 100, 161, 27));
        QPalette palette2;
        QBrush brush3(QColor(56, 46, 203, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush4);
        QBrush brush5(QColor(186, 57, 173, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush5);
        QBrush brush6(QColor(0, 170, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush6);
        QBrush brush7(QColor(120, 242, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        QBrush brush8(QColor(240, 240, 240, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        ShapesComboBox->setPalette(palette2);
        ShapesComboBox->setCursor(QCursor(Qt::PointingHandCursor));
        ShapesComboBox->setFocusPolicy(Qt::ClickFocus);
        ShapesComboBox->setStyleSheet(QString::fromUtf8(""));
        ShapesComboBox->setEditable(false);
        ShapesComboBox->setMaxVisibleItems(5);
        ShapesComboBox->setInsertPolicy(QComboBox::NoInsert);
        ShapesComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        ShapeNameLabel = new QLabel(centralwidget);
        ShapeNameLabel->setObjectName(QString::fromUtf8("ShapeNameLabel"));
        ShapeNameLabel->setGeometry(QRect(20, 100, 101, 17));
        ShapeNameLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(380, 60, 121, 84));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ClearButton = new QPushButton(layoutWidget1);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Purisa"));
        font2.setPointSize(12);
        ClearButton->setFont(font2);
        ClearButton->setCursor(QCursor(Qt::PointingHandCursor));
        ClearButton->setMouseTracking(false);
        ClearButton->setFocusPolicy(Qt::ClickFocus);
        ClearButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ClearButton);

        OKButton = new QPushButton(layoutWidget1);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));
        OKButton->setFont(font2);
        OKButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(OKButton);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(380, 230, 125, 331));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        AddShapeButton = new QPushButton(layoutWidget2);
        AddShapeButton->setObjectName(QString::fromUtf8("AddShapeButton"));
        AddShapeButton->setFont(font2);
        AddShapeButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(AddShapeButton, 0, 0, 1, 1);

        DeleteShapeButton = new QPushButton(layoutWidget2);
        DeleteShapeButton->setObjectName(QString::fromUtf8("DeleteShapeButton"));
        DeleteShapeButton->setFont(font2);
        DeleteShapeButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(DeleteShapeButton, 1, 0, 1, 1);

        EditShapeButton = new QPushButton(layoutWidget2);
        EditShapeButton->setObjectName(QString::fromUtf8("EditShapeButton"));
        EditShapeButton->setFont(font2);
        EditShapeButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(EditShapeButton, 2, 0, 1, 1);

        CopyShapeButton = new QPushButton(layoutWidget2);
        CopyShapeButton->setObjectName(QString::fromUtf8("CopyShapeButton"));
        CopyShapeButton->setFont(font2);
        CopyShapeButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(CopyShapeButton, 3, 0, 1, 1);

        UpButton = new QPushButton(layoutWidget2);
        UpButton->setObjectName(QString::fromUtf8("UpButton"));
        UpButton->setFont(font2);
        UpButton->setCursor(QCursor(Qt::PointingHandCursor));
        UpButton->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 186, 155);"));

        gridLayout->addWidget(UpButton, 4, 0, 1, 1);

        BottomButton = new QPushButton(layoutWidget2);
        BottomButton->setObjectName(QString::fromUtf8("BottomButton"));
        BottomButton->setFont(font2);
        BottomButton->setCursor(QCursor(Qt::PointingHandCursor));
        BottomButton->setLayoutDirection(Qt::LeftToRight);
        BottomButton->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 81, 65, 202);\n"
"image: url(:/newPrefix/zsources/FlecheBasRouge.png);"));

        gridLayout->addWidget(BottomButton, 5, 0, 1, 1);

        AttributesTableWidget = new QTableWidget(centralwidget);
        if (AttributesTableWidget->columnCount() < 2)
            AttributesTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        AttributesTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setBackground(QColor(204, 23, 23));
        AttributesTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        AttributesTableWidget->setObjectName(QString::fromUtf8("AttributesTableWidget"));
        AttributesTableWidget->setGeometry(QRect(30, 190, 321, 401));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush9(QColor(240, 238, 228, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush4);
        QBrush brush10(QColor(247, 246, 241, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(120, 119, 114, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(160, 159, 152, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush4);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush13(QColor(255, 255, 220, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush13);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush13);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        AttributesTableWidget->setPalette(palette3);
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Serif"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        AttributesTableWidget->setFont(font3);
        AttributesTableWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        AttributesTableWidget->setAutoFillBackground(false);
        AttributesTableWidget->setFrameShape(QFrame::NoFrame);
        AttributesTableWidget->setFrameShadow(QFrame::Raised);
        AttributesTableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        AttributesTableWidget->setDragEnabled(true);
        AttributesTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        AttributesTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        AttributesTableWidget->setTextElideMode(Qt::ElideMiddle);
        AttributesTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        AttributesTableWidget->setGridStyle(Qt::DotLine);
        AttributesTableWidget->setWordWrap(false);
        TrialNameLabel = new QLabel(centralwidget);
        TrialNameLabel->setObjectName(QString::fromUtf8("TrialNameLabel"));
        TrialNameLabel->setEnabled(true);
        TrialNameLabel->setGeometry(QRect(12, 22, 73, 17));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush4);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        TrialNameLabel->setPalette(palette4);
        TrialNameLabel->setLayoutDirection(Qt::LeftToRight);
        TrialNameLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        ShapeListLabel = new QLabel(centralwidget);
        ShapeListLabel->setObjectName(QString::fromUtf8("ShapeListLabel"));
        ShapeListLabel->setGeometry(QRect(551, 31, 77, 17));
        ShapeListLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        ShapesListWidget = new QListWidget(centralwidget);
        ShapesListWidget->setObjectName(QString::fromUtf8("ShapesListWidget"));
        ShapesListWidget->setGeometry(QRect(550, 50, 321, 421));
        ShapesListWidget->setFrameShape(QFrame::StyledPanel);
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(310, 190, 31, 27));
        colorButton = new QPushButton(centralwidget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setGeometry(QRect(350, 190, 31, 27));
        colorButton->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));\n"
"color: rgb(255, 255, 255);"));
        ShapeNameLabel_2 = new QLabel(centralwidget);
        ShapeNameLabel_2->setObjectName(QString::fromUtf8("ShapeNameLabel_2"));
        ShapeNameLabel_2->setGeometry(QRect(20, 150, 191, 17));
        ShapeNameLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(210, 140, 71, 31));
        TrialNameComboBox = new QComboBox(centralwidget);
        TrialNameComboBox->setObjectName(QString::fromUtf8("TrialNameComboBox"));
        TrialNameComboBox->setGeometry(QRect(90, 50, 221, 31));
        TrialNameComboBox->setEditable(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 896, 23));
        menubar->setStyleSheet(QString::fromUtf8(""));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setStyleSheet(QString::fromUtf8(""));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        ShapeNameLabel->setBuddy(ShapesComboBox);
        ShapeNameLabel_2->setBuddy(ShapesComboBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(ClearButton, OKButton);
        QWidget::setTabOrder(OKButton, ShapesComboBox);
        QWidget::setTabOrder(ShapesComboBox, AttributesTableWidget);
        QWidget::setTabOrder(AttributesTableWidget, AddShapeButton);
        QWidget::setTabOrder(AddShapeButton, ShapesListWidget);
        QWidget::setTabOrder(ShapesListWidget, DeleteShapeButton);
        QWidget::setTabOrder(DeleteShapeButton, EditShapeButton);
        QWidget::setTabOrder(EditShapeButton, CopyShapeButton);
        QWidget::setTabOrder(CopyShapeButton, UpButton);
        QWidget::setTabOrder(UpButton, BottomButton);
        QWidget::setTabOrder(BottomButton, SaveButton);
        QWidget::setTabOrder(SaveButton, QuitButton);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(action_Quit);
        menu_Edit->addAction(actionUndo);
        menu_Edit->addAction(actionRedo);
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(action_Copy);
        menu_Edit->addAction(action_Past);

        retranslateUi(MainWindow);
        QObject::connect(QuitButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(ClearButton, SIGNAL(clicked()), ShapesListWidget, SLOT(clearSelection()));
        QObject::connect(DeleteShapeButton, SIGNAL(clicked()), ShapesListWidget, SLOT(clearSelection()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        action_Cut->setText(QApplication::translate("MainWindow", "&Cut", 0, QApplication::UnicodeUTF8));
        action_Cut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        action_Copy->setText(QApplication::translate("MainWindow", "&Copy", 0, QApplication::UnicodeUTF8));
        action_Copy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        action_Past->setText(QApplication::translate("MainWindow", "&Past", 0, QApplication::UnicodeUTF8));
        action_Past->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", 0, QApplication::UnicodeUTF8));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "&Redo", 0, QApplication::UnicodeUTF8));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        SaveButton->setText(QApplication::translate("MainWindow", "SAVE", 0, QApplication::UnicodeUTF8));
        SaveButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        QuitButton->setText(QApplication::translate("MainWindow", "QUIT", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ShapesComboBox->setToolTip(QApplication::translate("MainWindow", "Choose a shape", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ShapeNameLabel->setText(QApplication::translate("MainWindow", "Shape Name :", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ClearButton->setToolTip(QApplication::translate("MainWindow", "Clear the text of the trial name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ClearButton->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        OKButton->setToolTip(QApplication::translate("MainWindow", "Validate the entered name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        OKButton->setText(QApplication::translate("MainWindow", "Ok", 0, QApplication::UnicodeUTF8));
        OKButton->setShortcut(QApplication::translate("MainWindow", "Return", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        AddShapeButton->setToolTip(QApplication::translate("MainWindow", "Add the shape to the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        AddShapeButton->setText(QApplication::translate("MainWindow", "AddShape", 0, QApplication::UnicodeUTF8));
        AddShapeButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        DeleteShapeButton->setToolTip(QApplication::translate("MainWindow", "Delete the shape from the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        DeleteShapeButton->setText(QApplication::translate("MainWindow", "DeleteShape", 0, QApplication::UnicodeUTF8));
        DeleteShapeButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        EditShapeButton->setToolTip(QApplication::translate("MainWindow", "Edit the shape", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        EditShapeButton->setText(QApplication::translate("MainWindow", "EditShape", 0, QApplication::UnicodeUTF8));
        EditShapeButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        CopyShapeButton->setToolTip(QApplication::translate("MainWindow", "Copy the shape with its attributes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        CopyShapeButton->setText(QApplication::translate("MainWindow", "CopyShape", 0, QApplication::UnicodeUTF8));
        CopyShapeButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        UpButton->setToolTip(QApplication::translate("MainWindow", "Put the shape at the top of the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        UpButton->setText(QApplication::translate("MainWindow", "Up", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        BottomButton->setToolTip(QApplication::translate("MainWindow", "Put the shape at the bottom of the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        BottomButton->setText(QApplication::translate("MainWindow", "Down", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = AttributesTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Attributes", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = AttributesTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Values", 0, QApplication::UnicodeUTF8));
        TrialNameLabel->setText(QApplication::translate("MainWindow", "Trial Name", 0, QApplication::UnicodeUTF8));
        ShapeListLabel->setText(QApplication::translate("MainWindow", "Shapes List", 0, QApplication::UnicodeUTF8));
        helpButton->setText(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QString());
        ShapeNameLabel_2->setText(QApplication::translate("MainWindow", "Trial Max Length (Frame) :", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
