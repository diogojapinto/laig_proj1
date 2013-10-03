/*
 * MyRectangle.h
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#ifndef MYRECTANGLE_H_
#define MYRECTANGLE_H_

#include "MyPrimitive.h"

class MyRectangle: public MyPrimitive {
private:
	float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	float normal[3];
	float text_coords[4][2];
public:
	MyRectangle();
	MyRectangle(float x1, float y1, float x2, float y2);
	void draw();
	virtual ~MyRectangle();
	const float *calcNormal();
	void calcTextCoords();
};

#endif /* MYRECTANGLE_H_ */
