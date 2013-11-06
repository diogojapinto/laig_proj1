/*
 * MyPatch.h
 *
 *  Created on: Nov 5, 2013
 *      Author: diogo
 */

#ifndef MYPATCH_H_
#define MYPATCH_H_

#include "MyPrimitive.h"
<<<<<<< HEAD
=======
#include <vector>
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

class MyPatch: public MyPrimitive {
private:
	int order, partsU, partsV;
	int compute;
<<<<<<< HEAD
	float *ctrlPoints;
	int nrCtrlPoints;
=======
	vector<float> ctrlPoints;
	int nrCtrlPoints;
	vector<float> textPoints;
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

public:
	MyPatch();
	MyPatch(int order, int partsU, int partsV, string compute);
	virtual ~MyPatch();
	virtual void draw();
<<<<<<< HEAD
	void addControlPoint(int x, int y, int z);
=======
	virtual void setAppearance(string appearance);
	void addControlPoint(float x, float y, float z);
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4
};

#endif /* MYPATCH_H_ */
