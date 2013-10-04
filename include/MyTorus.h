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
#include <vector>

using namespace std;

class MyTorus: public MyPrimitive {
	float inner, outer;
	unsigned int slices, loops;
	vector<float> px, py, pz, nx, ny, nz, tx, ty, tz;
public:
	MyTorus();
	MyTorus(float inner, float outer, unsigned int slices, unsigned int loops);
	virtual ~MyTorus();
	void draw();
	void calcPoints();
	void calcNormals();
	void calcTextCoords();
};

#endif /* MYTORUS_H_ */
