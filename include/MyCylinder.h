/*
 * MyCylinder.h
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#ifndef MYCYLINDER_H_
#define MYCYLINDER_H_

#include "MyPrimitive.h"
#include "CGFapplication.h"


class MyCylinder: public MyPrimitive {
public:
	MyCylinder();
	virtual ~MyCylinder();
	void draw();

private:
	GLUquadric *q;
	void drawCircle();
};

#endif /* MYCYLINDER_H_ */
