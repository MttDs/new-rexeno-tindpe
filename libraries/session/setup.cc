#include "setup.hh"
#include <wordexp.h>
#include <fstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;
using namespace configuration;

bool* Setup::keys = new bool[256]; // Keysboard
int Setup::key = -1; // key pressed

Setup::Setup(string confFile)
{
  double height;
  double width;
  wordexp_t exp_result;
  wordexp(confFile.c_str(), &exp_result, 0);

  std::ifstream settings_file( exp_result.we_wordv[0] );
  po::variables_map vm;
  po::options_description desc;
  desc.add_options()
    ("height", po::value<double>( &height )->default_value(40), "height of the subject's screen")
    ("width", po::value<double>( &width )->default_value(40), "width of the subject's screen")
    ("refresh", po::value<double>( &height )->default_value(60), "refresh rate of screens")
    ;

  po::store( po::parse_config_file( settings_file , desc ), vm );
  po::notify(vm);

  boost::program_options::options_description dd;

  _screenHeight = height;
  _screenWidth = width;
}

Setup::Setup(configuration::SessionInfo& si)
{
  _screenHeight = si.height;
  _screenWidth = si.width;
  _refreshRate = si.frequency;
  _nbScreen = si.nb_screens;
  _ratio = -1.0;

  stringstream gms;
  
  gms << _screenWidth 
     << "x" 
     << _screenHeight 
     << ":32@" 
     << _refreshRate;
  _gameModeString = gms.str();
}

void
Setup::prepareRatio()
{
  double window_height = (double) glutGet(GLUT_WINDOW_HEIGHT);
  double window_width = (double) glutGet(GLUT_WINDOW_WIDTH);

  if (nbScreen()==2){
    window_width = window_width/2;
  }

  if (window_width >= window_height){
    _ratio = (double) (window_width/window_height);
  }
  else{
    _ratio = (double) (window_height/window_width);
  }
}

double
Setup::ratio()
{
  if (_ratio==(-1.0)){
    prepareRatio();
  } 

  return _ratio;
}

void
Setup::reset()
{
  int ii = 0;
  for (; ii < 256; ++ii)
    Setup::keys[ii] = false;
  
  Setup::key= -1;
}
