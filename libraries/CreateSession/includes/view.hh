#ifndef SESSION_VIEW_HH_
# define SESSION_VIEW_HH_

# include "SessionCreator.hh"
# include "model.hh"
QT_BEGIN_NAMESPACE


class SessionView : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT

public:
  SessionView();
  ~SessionView() {}
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
