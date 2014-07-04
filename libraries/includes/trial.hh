#ifndef	TRIAL_HH_
# define TRIAL_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include <map>
# include <set>
# include <string>
# include <string.h>
# include "parser.hh"
# include "shape.hh"
# include "square.hh"
# include "cross.hh"
# include "sphere.hh"
# include "plan.hh"
# include "rectangle3d.hh"
# include "aircraft.hh"
# include "session.hh"
# include "window.hh"
# include "adapt.hh"
using namespace std;
using namespace configuration;

class Shape;
class Square;
class Sphere;
class Plan;
class Driver;

typedef vector<Shape*> Shapes;

# define RUNNING 0
# define PAUSE 1
# define WRONG_REDO 2
# define WRONG_NEXT 3
# define CORRECT 4
# define WAITING_FIXATION 5
# define NEUTRAL 6

struct TtlEvent
{
  TtlEvent() {delay=0;value=0;}
  double delay;
  uint value;
};

class Trial
{
public:
  Trial(TrialInfo& ti);
  ~Trial();

  void adjustNbFrames();
  void addTtl();
  void Reset(Driver * d);
  void setIdScreen(int id){ _idScreen = id;}
 
  bool finished();
  bool atStart();
  bool status(int);

  int displayFrame(Driver* d);
  int frameEnd() {return _nbFrames;}

  string toString();
  string& name() {return _name;}
 
  Shapes* shapes() {return &_shapes;}
  Session* session();

  VariableManager variables;
  

private:

  void _sendTtls(Driver* d);

  bool _isSubScreen(); // subject's window

  int _react2status();
  int _random2params(int min, int max);

  bool _logged;
  bool _start;
  bool _subjectResponse;
  bool _shapeUpdate;

  int _idScreen;
  int _curFrameId;
  int _nbFrames;

  float _move;

  string& _name;

  vector<TtlEvent*>* _ttl;
  datas _data;

  Variable* _eyeX;
  Variable* _eyeY;
  Variable* _eyeZ;
  Variable* _centerX;
  Variable* _centerY;
  Variable* _centerZ;
  Variable* _cameraVeloX;
  Variable* _cameraVeloY;
  Variable* _cameraVeloZ;

  vector<float> _initCamera;

  Session* _session;

  Status _status;
  Shapes _shapes;
  ms _timePress;
  ms _timeUp;

};


#endif
