#ifndef EVENT_VIEW_HH_
#define EVENT_VIEW_HH_

#include "view.hh"

#include <QtDebug>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace boost;

class EventView : public View
{
Q_OBJECT
public:
  EventView(QWidget *parent, Controller *c);
  ~EventView();

  void beforeDisplay();
private:
  void _reset();
  void _init();

  QVBoxLayout *_layout;
  QComboBox *_comboShapes;
  QComboBox *_comboEvents;
  QGridLayout *_parentForm;

  QLabel *_title;
  QLabel *_key;
  QLabel *_coef;
  QLabel *_type;

  QLineEdit *_keyField;
  QLineEdit *_coefField;
  QComboBox *_comboType;
		       
  int _currentShape;
public slots:
  void loadComboShapes();
private slots:
  void _save();
  void _loadEventsFromShape(int index);
  void _deleteEvent(int index);

signals:
  void deleteEvent(int index); 
};

#endif
