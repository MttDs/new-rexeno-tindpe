#ifndef OPTION_HH_
# define OPTION_HH_

# include <string>
# include <wordexp.h>

using namespace std;

class Option
{
public:
  Option(string confFile = "~/.rexeno");
  ~Option();
private:
  
};


#endif
