/*
 * Animation.h
 *
 *  Created on: Oct 22, 2013
 *      Author: wso277
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>
#include <vector>
#include "Point.h"

using namespace std;

class Animation {
private:
	string id;
	float span;
	string type;
	vector<Point*> points;

public:
	Animation();
	Animation(string id, float span, string type);
	void addPoint(float x, float y, float z);
	vector<Point*> getPoints();
	float getSpan();
	virtual ~Animation();
};

#endif /* ANIMATION_H_ */
