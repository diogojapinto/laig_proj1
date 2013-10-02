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
	float x1, y1, x2, y2;
public:
	MyRectangle();
	MyRectangle(float x1, float y1, float x2, float y2);
	void draw();
	virtual ~MyRectangle();
};

#endif /* MYRECTANGLE_H_ */
