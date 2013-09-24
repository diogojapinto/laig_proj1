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
public:
	MyRectangle();
	void draw();
	virtual ~MyRectangle();
};

#endif /* MYRECTANGLE_H_ */
