#ifndef MODEL_HH_
# define MODEL_HH_

#include <vector>

#include <boost/lexical_cast.hpp>

#include "parser.hh"
#include "recorder.hh"

#include <QMessageBox>
#include <QObject>


using namespace configuration;
using namespace boost; 
using namespace std;
class Model : public QObject
{
Q_OBJECT
public:

  Model(SessionInfo *si);
  ~Model();
  
  SessionInfo *sessionInfo;
private:
  Recorder *_recorder;
  string _message;
	     
  bool _isValid();

public slots:
  void save();
  void checkAndSave();
};


#endif /* MODEL_HH_ */
