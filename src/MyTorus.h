/*
 * MyTorus.h
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#ifndef MYTORUS_H_
#define MYTORUS_H_

#include "MyPrimitive.h"

class MyTorus: public MyPrimitive {
public:
	MyTorus();
	virtual ~MyTorus();
	void draw();
};

#endif /* MYTORUS_H_ */
