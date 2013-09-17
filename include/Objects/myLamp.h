/*
 * myLamp.h
 *
 *  Created on: Mar 19, 2013
 *      Author: knoweat
 */

#ifndef MYLAMP_H_
#define MYLAMP_H_

#include "myUnitCube.h"
#include "myHalfSphere.h"
#include "myCylinder.h"
#include "CGFapplication.h"
#include "OS.h"

class myLamp {
	myUnitCube *cube;
	myCylinder *cylinder;
	myHalfSphere *h_sphere;
	CGFappearance* materialLW;
	CGFappearance* materialLS;
public:
	myLamp();
	~myLamp();
	void draw();
};

#endif /* MYLAMP_H_ */
