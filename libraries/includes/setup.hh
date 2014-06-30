#ifndef SETUP_HH_
# define SETUP_HH_

# include <GL/glew.h>
# include <GL/freeglut.h>

# include "parser.hh"
# include <string>

namespace configuration
{
  class SessionInfo;
};

using namespace std;

class Setup
{
public:
  Setup(string confFile = "~/.rexeno");
  Setup(configuration::SessionInfo& si);

  int nbScreen() { return _nbScreen;}
  double xRatio(){ return _screenWidth/_screenHeight;}
  double yRatio(){ return 1.0;}
  double ratio();
  double refreshRate() {return _refreshRate;}
  double screenHeight() {return _screenHeight;}
  double screenWidth() {return _screenWidth;}
  string gameModeString() {return _gameModeString;}
  
  void setScreenWidth(int width){ _screenWidth = width; }
  void setScreenHeight(int height){ _screenHeight = height; }
  void prepareRatio();

  static void reset();  
  static bool* keys; // Create an array of boolean values of length 256 (0-255)
  static int key;

private:
  // pixels
  int _screenHeight;
  int _screenWidth;

  int _nbScreen;
  // Hz :
  double _refreshRate;

  double _ratio;
  string _gameModeString;
};


#endif

