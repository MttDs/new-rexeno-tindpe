/**
 * @file   shape.hh
 * @author hadrien <hadrien@barbow>
 * @date   Tue May 21 22:45:52 2013
 * 
 * @brief  
 * 
 * Defines the Shape class
 * Shape is a purely abstract that designates the elements that can appear during a trial.
 * Most of the time, a shape has a color and dimensions (for example a Circle or a Square)
 * but it is possible to create objects that only affect the outcome of the trial without
 * anything being displayed directly (kind of the case of Window)
 */

#ifndef SHAPE_HH_
# define SHAPE_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include <string>
# include <iostream>
# include <string>
# include <boost/lexical_cast.hpp>
# include <map>
# include <assert.h>
# include <math.h>
# include "parser.hh"
# include "variable.hh"
# include "types.hh"
# include "session.hh"

using namespace configuration;
using namespace std;

typedef map<int, bool> Status;

class Trial;
class Adapt;

class Shape
{
public:
  Shape(const ShapeInfo& si,
        VariableManager& vm,
        Trial* father);
  Shape();
  virtual ~Shape() {}

  virtual void Display();
  virtual void DisplayMonitor();
  virtual void React2input(Status&,
                           const datas&,
                           int,
                           ms);
  virtual void Reset();
  virtual void initPos(){};
  virtual void initTexture();

  //  virtual double z() { return 0.0; }

  virtual string toString();

  void updateVelo(double coef);
  void updateDuration(double coef);
  void setAdapts(vector<Adapt*>*k);
  void setStart(bool b){_start=b;}
  void setSession(Session * s){ _session = s;}

  bool MonitorDisplayable();
  bool Displayable(int frameId);
  bool start(){return _start;}

  int id() {return _id;}
  int random2params(int min, int max);
  uint ttl() {return _ttl;}

  double x() {return _x->value;}
  double y() {return _y->value;}
  double frameStart() {return _frameStart->value;}
  double frameEnd() {return (_frameEnd->value);}
  double RoundNdecimal(int n, float nb);

  const string& name() {return _name;}

  vector<Adapt*> getAdapts(){ return _adapts;}

protected:
 
  void _adaptFrame();
  void _setDisplayTime();

  bool _logged;
  bool _loggedEnd;
  bool _subjectVisible;
  bool _start;

  int _id;
  int _initFrameStart;
  int _initFrameEnd;
  GLuint _texture[1];
  uint _ttl;

  float _getRandomNumber(float pos, float nb);
  float _gainV;
  float _gainD;
  
  // Use these functions for opengl's drawing scale. 
  double _demiVertical(); // inside sub square-screen
  double _demiHorizontal(); // inside sub square-screen
  double _xGL(); // inside sub square-screen
  double _yGL(); // inside sub square-screen

  string _name;
  string _textureName;

  Variable* _frameStart;
  Variable* _frameEnd;
  Variable* _x;
  Variable* _y;
  Variable* _z;
  Variable* _width;
  Variable* _height;
  Variable* _R;
  Variable* _G;
  Variable* _B;
  Variable* _opacity;
  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;
  Variable* _minStart;
  Variable* _maxStart;

  ms _displayStart;
  ms _displayPeriod;

  Trial* _father;
  Session* _session;
  GLUquadric* _params;

  vector<Adapt*> _adapts;

};

#endif
