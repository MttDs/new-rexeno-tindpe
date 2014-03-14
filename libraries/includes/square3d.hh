/*
 * square3d.hh
 *
 *  Created on: Feb 11, 2014
 *      Author: xeno1
 */

#ifndef SQUARE3D_HH_
#define SQUARE3D_HH_

#include "rectangle3d.hh"

class Square3d : public Rectangle3d{
public:
	Square3d(const ShapeInfo& si,
	         VariableManager& vm,
	         Trial* t);
	~Square3d();

};

#endif /* SQUARE3D_HH_ */
