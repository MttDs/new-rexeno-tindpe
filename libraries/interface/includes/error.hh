#ifndef ERROR_VIEW_HH_
#define ERROR_VIEW_HH_

#include <QWidget>
#include <QLabel>

#include "view.hh"

class ErrorView : public View
{
public:
  ErrorView(QWidget *parent, Controller *c);
  ~ErrorView();
private:
  QLabel *_error;
};
#endif
