#ifndef SQUARE_HH_
# define SQUARE_HH_

# include "rectangle.hh"

class Square : public Rectangle
{
public:
  Square(const ShapeInfo& si,
         VariableManager& vm,
         Trial* t);
  ~Square();
private:
};


#endif
