#ifndef	TRIAL_HH_
# define TRIAL_HH_

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
# include <GL/glut.h>

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
  int displayFrame(Driver* d);
  bool finished();
  bool atStart();
  string& name() {return _name;}
  void adjustNbFrames();
  void addTtl();
  bool status(int);
  int frameEnd() {return _nbFrames;}
  Session* session() {return _session;}
  VariableManager variables;
  void Reset(Driver * d);
  void setIdScreen(int id){ _idScreen = id;}

private:
  Session* _session;

  int _react2status();
  void _sendTtls(Driver* d);
  bool _isSubScreen(); // subject's window
  int _random2params(int min, int max);

  int _idScreen;
  int _curFrameId;
  int _nbFrames;
  Status _status;
  Shapes _shapes;
  string& _name;
  float _move;
  int _argc;
  char **_argv;
  vector<TtlEvent*>* _ttl;
  datas _data;

  bool _logged;
  bool _start;
  bool _subjectResponse;
  bool _shapeUpdate;

  Variable* _eyeX;
  Variable* _eyeY;
  Variable*  _eyeZ;

  Variable* _centerX;
  Variable*  _centerY;
  Variable* _centerZ;

  Variable*  _cameraVeloX;
  Variable*  _cameraVeloY;
  Variable*  _cameraVeloZ;

  vector<float> _initCamera;

  ms _timePress;
  ms _timeUp;
};


#endif
