#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <QMainWindow>
#include <iostream>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  Ui::MainWindow* getUi(){ return ui;}

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
