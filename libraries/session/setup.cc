#include "setup.hh"
#include <wordexp.h>
#include <fstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

bool* Setup::keys = new bool[256];
int Setup::key = -1;

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

double
Setup::xRatio()
{
  return (_screenHeight / _screenWidth);
}

void
Setup::reset()
{
  /*int i = 0;
  for (; i < 256; ++i)
    Setup::keys[i] = false;
  */
  Setup::key= -1;
}
