/*
 * Plane.h
 *
 *  Created on: Nov 5, 2013
 *      Author: wso277
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "MyPrimitive.h"

class Plane: public MyPrimitive {
	unsigned int parts;
	float ctrl_pts[4][3];
	float nrml_pts[4][3];
	float text_pts[4][2];
public:
	Plane();
	Plane(unsigned int parts);
	virtual void draw();
	virtual void setAppearance(string appearance);
	virtual ~Plane();
};

#endif /* PLANE_H_ */
