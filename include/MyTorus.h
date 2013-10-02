/*
 * MyTorus.h
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#ifndef MYTORUS_H_
#define MYTORUS_H_

#include "MyPrimitive.h"
#include "CGFapplication.h"

class MyTorus: public MyPrimitive {
public:
	MyTorus();
	virtual ~MyTorus();
	void draw();
protected:
};

#endif /* MYTORUS_H_ */
