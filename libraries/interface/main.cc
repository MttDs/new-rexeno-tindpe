#include <QtGui/QApplication>
#include "controller.hh"
#include "mainwindow.hh"

#include "ui_mainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Ui::MainWindow* ui = w.getUi();
    Controller* c = new Controller(ui);
    c->Init();

    return a.exec();
}
