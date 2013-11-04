/*
 * Animation.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: wso277
 */

#include "Animation.h"
#include "utils.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

Animation::Animation() {

}

Animation::Animation(string id, float span, string type) {
	this->id = id;
	this->span = span;
	this->type = type;
	counter = 1;
	vec_index = 0;
	time_passed = 0;
	points.push_back(new Point(0,0,0));
}

void Animation::addPoint(float x, float y, float z) {

	points.push_back(new Point(points.back()->getX() + x, points.back()->getY() + y, points.back()->getZ() + z));
}

void Animation::calculateDelta() {
	float deltax, deltay, deltaz;
	float t_dist = 0;
	unsigned int time_tmp;
	vector<float> dist;
	vector<Point*> delta_tmp;

	for (int i = 1; i < points.size(); i++) {
		dist.push_back(distanceTwoPoints(points[i], points[i - 1]));

		t_dist += dist[i - 1];

		deltax = points[i]->getX() - points[i - 1]->getX();
		deltay = points[i]->getY() - points[i - 1]->getY();
		deltaz = points[i]->getZ() - points[i - 1]->getZ();

		delta_tmp.push_back(new Point(deltax, deltay, deltaz));
	}

	for (int i = 0; i < dist.size(); i++) {
		time_tmp = dist[i] / t_dist * span;
		deltax = delta_tmp[i]->getX() / time_tmp;
		deltay = delta_tmp[i]->getY() / time_tmp;
		deltaz = delta_tmp[i]->getZ() / time_tmp;

		if (deltax != 0) {
			increments.push_back(abs(dist[i] / deltax));
		}
		else if (deltay != 0) {
			increments.push_back(abs(dist[i] / deltay));
		}
		else {
			increments.push_back(abs(dist[i] / deltaz));
		}

		printf("\n\ndist: %lf", dist[i]);
		printf("\n\nincrements: %d", increments[i]);
		time.push_back(ceil((float)time_tmp / (float)increments[i]));

		delta.push_back(new Point(deltax, deltay, deltaz));
	}
}
vector<Point*> Animation::getPoints() {
	return points;
}

Point Animation::getPoint() {
	return point;
}

float Animation::getSpan() {
	return span;
}

int Animation::getTime() {
	return time[vec_index];
}

Point* Animation::getDelta() {
	return delta[vec_index];
}
bool Animation::updateValues() {

	time_passed += time[vec_index];
	if (time_passed < floor(span)) {
		if (counter < increments[vec_index]) {

			counter++;
			printf("counter: %d\n", counter);
		} else {
			vec_index++;
			counter = 1;
			printf("vec: %d\n", vec_index);
		}
		return true;
	} else {
		return false;
	}

	return false;
}
Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

