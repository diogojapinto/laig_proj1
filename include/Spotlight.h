/*
 * Spotlight.h
 *
 *  Created on: Oct 2, 2013
 *      Author: wso277
 */

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "Lights.h"

using namespace std;

class Spotlight: public Lights {
private:
	float angle;
	float exponent;
	float dir_x, dir_y, dir_z;
public:
	Spotlight();
	Spotlight(string id);
	Spotlight(string id, bool enabled);
	void setAngle(float angle);
	void setExponent(float exponent);
	void setDir(float dir_x, float dir_y, float dir_z);
	virtual void readyLights(int index);
	virtual ~Spotlight();
};

#endif /* SPOTLIGHT_H_ */