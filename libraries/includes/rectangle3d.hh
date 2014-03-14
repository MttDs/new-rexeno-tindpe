/*
 * rectangle3d.hh
 *
 *  Created on: Feb 11, 2014
 *      Author: xeno1
 */

#ifndef RECTANGLE3D_HH_
#define RECTANGLE3D_HH_

# include "shape.hh"

class Rectangle3d : public Shape
{
public:
  Rectangle3d(const ShapeInfo&,
            VariableManager&,
            Trial* father);
  Rectangle3d() {}
  void Display();
  void DisplayMonitor();
  virtual ~Rectangle3d();

  void React2input(Status&,
                   datas&,
                   int,
                   ms);
  void Reset();
protected:
  Variable* _z;
  Variable* _dir;
  Variable* _repeat;
  Variable* _velo;
  Variable* _deep;
  Variable* _pos;

  float _initX;
  float _initY;
  float _initZ;
};

#endif /* RECTANGLE3D_HH_ */
