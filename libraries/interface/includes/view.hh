#ifndef SESSION_VIEW_HH_
# define SESSION_VIEW_HH_

# include "model.hh"
# include <QObject>
# include <QMainWindow>
# include "mainWindow.hh"
QT_BEGIN_NAMESPACE

class View : public Ui_MainWindow
{
  Q_OBJECT

public:
  View();
  ~View() {}
  void SetModel(Model* m);

  void Init();
public slots:
  void Add();

private:
  Model* _m;
  void _Display();
};



QT_END_NAMESPACE

#endif /* SESSION_VIEW_HH_ */
