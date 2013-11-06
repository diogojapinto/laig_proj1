/*
 * MyPatch.h
 *
 *  Created on: Nov 5, 2013
 *      Author: diogo
 */

#ifndef MYPATCH_H_
#define MYPATCH_H_

#include "MyPrimitive.h"

class MyPatch: public MyPrimitive {
private:
	int order, partsU, partsV;
	int compute;
	float *ctrlPoints;
	int nrCtrlPoints;
	float textPoints[4][2];

public:
	MyPatch();
	MyPatch(int order, int partsU, int partsV, string compute);
	virtual ~MyPatch();
	virtual void draw();
	void addControlPoint(int x, int y, int z);
};

#endif /* MYPATCH_H_ */
