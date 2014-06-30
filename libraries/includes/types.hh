#ifndef TYPES_HH_
# define TYPES_HH_

# include <vector>
typedef unsigned long long ms;

struct pos
{
  double x;
  double y;
};

struct Element
{
  Element()
  {
    volt = 0;
    timing = 0;
  }
  ~Element() {}

  double volt;
  ms timing;
};

typedef std::vector<Element> channel;
typedef std::vector<channel> datas;



#endif /* TYPES_HH_ */
