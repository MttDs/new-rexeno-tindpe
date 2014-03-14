#ifndef ORDER_PARSER_HH
# define ORDER_PARSER_HH

# include <string>
# include <vector>

class Order
{
public:
  Order(std::string filename);
  ~Order();
  std::vector<int>& getOrder();

private:
  std::vector<int> _trialsOrder;
};

#endif
