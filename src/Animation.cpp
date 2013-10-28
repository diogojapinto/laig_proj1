/*
 * Animation.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: wso277
 */

#include "Animation.h"

Animation::Animation() {
	// TODO Auto-generated constructor stub

}

Animation::Animation(string id, float span, string type) {
	this->id = id;
	this->span = span;
	this->type = type;
}

void Animation::addPoint(float x, float y, float z) {

	points.push_back(new Point(x, y, z));
}

vector<Point*> Animation::getPoints() {
	return points;
}

float Animation::getSpan() {
	return span;
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

