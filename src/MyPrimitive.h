/*
 * MyPrimitive.h
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#ifndef MYPRIMITIVE_H_
#define MYPRIMITIVE_H_

#include "Node.h"

class MyPrimitive: public Node {
public:
	MyPrimitive();
	virtual void draw() = 0;
	virtual ~MyPrimitive();
};

#endif /* MYPRIMITIVE_H_ */
