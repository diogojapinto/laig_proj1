/*
 * myChair.h
 *
 *  Created on: Feb 26, 2013
 *      Author: knoweat
 */

#ifndef MYCHAIR_H_
#define MYCHAIR_H_

#include "myUnitCube.h"
#include <time.h>
#include "CGFapplication.h"
#include "OS.h"

class myChair {
	myUnitCube cube;
	float angle;
	float x;
	float z;
	CGFappearance* materialCT;
	CGFappearance* materialCL;
public:
	myChair();
	void draw();
};

#endif /* MYCHAIR_H_ */
