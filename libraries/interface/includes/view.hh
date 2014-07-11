#ifndef SESSION_VIEW_HH_
# define SESSION_VIEW_HH_

# include <QObject>
# include <QMainWindow>
#include <QString>
class View : public QWidget
{
  Q_OBJECT
public:
  View(QWidget *parent);
  ~View();
  const char* name;
};



#endif /* SESSION_VIEW_HH_ */
