#ifndef ORDER_PARSER_HH
# define ORDER_PARSER_HH

# include <string>
# include <vector>
# include <stdlib.h>     /* srand, rand */
# include <time.h>       /* time */
# include "types.hh"
# include "parser.hh"

namespace configuration
{
  class SessionInfo;
};

using namespace std;

class Order
{
public:
  Order(std::string filename, configuration::SessionInfo& s);
  ~Order();
  std::vector<int>& getOrder();
  void parse();
  void _random();
  void _pile();
  void _oneAfterTheOther();
private:
  std::string _filename;
  std::vector<int> _trialsOrder;
  int _nbTrials;
  int _nbSessions;
};

#endif
