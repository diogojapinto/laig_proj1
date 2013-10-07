/*
 * Perspective.h
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#ifndef PERSPECTIVE_H_
#define PERSPECTIVE_H_

#include "Camera.h"
#include <string>

using namespace std;

class Perspective: public Camera {
private:
	float angle;
	float px, py, pz;
	float tx, ty, tz;
public:
	Perspective();
	Perspective(string id);
	void setAngle(float angle);
	void setPos(float px, float py, float pz);
	void setTarget(float tx, float ty, float tz);
	float getAngle();
	float getPosX();
	float getPosY();
	float getPosZ();
	float getTargetX();
	float getTargetY();
	float getTargetZ();
	void setCamera();
	virtual ~Perspective();
};

#endif /* PERSPECTIVE_H_ */