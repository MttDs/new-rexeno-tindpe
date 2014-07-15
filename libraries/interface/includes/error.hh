#ifndef ERROR_HH_
#define ERROR_HH_

#include <QWidget>
#include <QLabel>

#include "view.hh"

class Error : public View
{
public:
  Error(QWidget *parent, Controller *c);
  ~Error();
private:
  QLabel *_error;
};
#endif
