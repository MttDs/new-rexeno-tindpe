/**
 * @file   cross.hh
 * @author hadrien <hadrien@barbow>
 * @date   Sun Jun 30 01:09:56 2013
 * 
 * @brief  Declaration of the Cross class.
 * It is a child of the Shape class, it represents
 * the position of the eyes, and can only be seen
 * on the monitor screen, not on the subject's
 * 
 */

#ifndef CROSS_HH_
# define CROSS_HH_

# include "shape.hh"

class Cross : public Shape
{
public:
  Cross(const ShapeInfo&,
        VariableManager&,
        Trial* father);
  Cross() {}
  ~Cross() {}

  void Display();
  void DisplayMonitor();
  void React2input(Status&,
                   const datas&,
                   int frameId,
                   ms);
private:
};

#endif
