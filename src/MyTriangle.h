/*
 * MyTriangle.h
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#ifndef MYTRIANGLE_H_
#define MYTRIANGLE_H_

#include "MyPrimitive.h"

class MyTriangle: public MyPrimitive {
public:
	MyTriangle();
	virtual ~MyTriangle();
	void draw();
};

#endif /* MYTRIANGLE_H_ */
