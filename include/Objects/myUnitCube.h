/*
 * myUnitCube.h
 *
 *  Created on: Feb 20, 2013
 *      Author: knoweat
 */

#ifndef MYUNITCUBE_H_
#define MYUNITCUBE_H_

#include "CGFobject.h"
#include "Plane.h"

class myUnitCube: public CGFobject {
	Plane plane;
public:
	myUnitCube();
	void draw();
	void drawBaseSquare();
};

#endif /* MYUNITCUBE_H_ */
