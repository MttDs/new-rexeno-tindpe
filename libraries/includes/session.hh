/**
 * @file   session.hh
 * @author hadrien <hadrien@barbow>
 * @date   Tue May 21 23:07:59 2013
 * 
 * @brief  Defines the Session class
 * This is a global unique object (Design Pattern Singleton)
 * it represents a complete session.
 * The main task of about any program is to run each trial of the session class.
 * 
 */

#ifndef SESSION_HH_
# define SESSION_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include <iostream>
# include <vector>
# include <list>
# include "types.hh"
class Driver;
class VariableManager;
class Variable;
class Trial;
class Setup;
class Recorder;
class Order;

namespace configuration
{
  class SessionInfo;
};

using namespace std;
//using namespace configuration;

// Singleton class
class Session
{
public:
  ~Session();
  static Session* getInstance();
  static Session* getInstance(configuration::SessionInfo& s,
                              Order& o);
  void run(int argc,
           char** argv);
  void displayFrame(int screen);
  void displayHeader();

  void (*afterTrial)(string&, VariableManager&, int);
  void (*beforeTrial)(string&, VariableManager&);
  void setDriver(Driver* d) {_driver = d;}

  Setup* setup; 
  Recorder* recorder;
  int nbFrame4init() {return _nbFrame4init;}
  int nbInitFrames() {return _nbInitFrames;}
  ms getTime();

  string getNbBlock(){return _nbBlock;}
  string getSubjectName(){return _subjectName;}
  bool initialized();
  GLvoid InitGL();
private:
  Session(configuration::SessionInfo& s,
          Order& o);
  void _fillData();
  Driver* _driver;
  vector<Trial*> _trialsDefinitions;
  vector<int>& _trialsOrder;
  static Session* _instance;
  vector<pair<double, ms> > _inputData;
  vector<int>::iterator _currentTrial;
  // Guardian Trial : in charge of
  // evaluating the offset value of display
  bool _initialized;
  int _nbFrame4init;
  int _nbInitFrames;
  double _offsetVsync; // offset between 0 and 16.666 (if 60Hz)

  // Background Color :
  GLfloat _RGB[3];
  // Light Position : 
  GLfloat _lP[4]; 
  // Light Ambient : 
  GLfloat _lA[4];
  // Light Diffuse :
  GLfloat _lD[4];
  string _subjectName;
  string _nbBlock;
#ifdef DEBUG
  int __debug_FrameNumber;
#endif
};

#ifdef DEBUG
# define PDEBUG(fmt, args) cerr << fmt << args << "\n";
#else
# define PDEBUG(fmt, args) /* not debugging: nothing */
#endif


#endif

