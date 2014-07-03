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

  virtual void initTexture();
  double x() {return _x->value;}
  double y() {return _y->value;}
  virtual double z() { return 0.0; }
  int id() {return _id;}
  const string& name() {return _name;}
  double frameStart() {return _frameStart->value;}
  double frameEnd() {return (_frameEnd->value);}
  bool MonitorDisplayable();
  uint ttl() {return _ttl;}
  bool Displayable(int frameId);
  bool SubjectVisible(){return _subjectVisible;}
  virtual void Reset();
  virtual string toString();
  virtual void initPos(){};
  double RoundNdecimal(int n, float nb);

  void setAdapts(vector<Adapt*>*k);
  vector<Adapt*> getAdapts(){ return _adapts;}
  void updateVelo(double coef);
  void updateDuration(double coef);
  int random2params(int min, int max);
  bool start(){return _start;}
  void setStart(bool b){_start=b;}

protected:
  // Use these functions for opengl's drawing scale. 
  double _demiVertical(); // inside sub square-screen
  double _demiHorizontal(); // inside sub square-screen
  double _xGL(); // inside sub square-screen
  double _yGL(); // inside sub square-screen
  float _getRandomNumber(float pos, float nb);
  void _adaptFrame(int frame);
 
  int _id;

  GLuint _texture[1];
  GLUquadric* _params;

  string _name;
  string _textureName;

  Variable* _frameStart;
  Variable* _frameEnd;

  int _initFrameStart;
  int _initFrameEnd;

  Variable* _x;
  Variable* _y;
  Variable* _width;
  Variable* _height;
  Variable* _R;
  Variable* _G;
  Variable* _B;

  uint _ttl;
  Trial* _father;
  Session* _session;

  bool _logged;
  bool _loggedEnd;
  bool _subjectVisible;

  Variable* _veloX;
  Variable* _veloY;
  Variable* _veloZ;
  
  float _gainV;
  float _gainD;

  Variable* _minStart;
  Variable* _maxStart;
  // int _frameAdapt;
  
  bool _start;

  vector<Adapt*> _adapts;

};

#endif
