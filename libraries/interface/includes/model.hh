#ifndef MODEL_HH_
# define MODEL_HH_

#include <vector>

#include <boost/lexical_cast.hpp>

#include "parser.hh"
#include "recorder.hh"
#include <QObject>


using namespace configuration;
using namespace boost; 

class Model : public QObject
{
Q_OBJECT
public:

  Model(SessionInfo *si);
  ~Model();
  
  SessionInfo *sessionInfo;

private:
  Recorder *_recorder;

public slots:
  void save();
/*
  void fillAlreadyExistingTrials(const std::string& confFile);

  void fillAvailableShapes(const std::string& confFile);
  const std::vector<std::string>& availableTrials() {return _availableTrials;}
  std::set<std::string>& trialsInSession() {return _trialsInSession;}

  void AddTrial(std::string);
void setTrialName(const std::string&);
void addShape2Trial(const std::string& shape);

 //std::vector<std::string>(std::vector<std::string>::const_iterator first, 
//			  std::vector<std::string>::const_iterator last) shapePrototypes ;

private:

 std::string _trialName;
  std::vector<std::string> _availableTrials;
  std::vector<std::string> _availableShapes;
  std::set<std::string> _trialsInSession;*/

};


#endif /* MODEL_HH_ */
