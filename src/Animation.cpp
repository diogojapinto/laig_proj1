/*
 * Animation.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: wso277
 */

#include "Animation.h"
#include "utils.h"

Animation::Animation() {

}

Animation::Animation(string id, float span, string type) {
	this->id = id;
	this->span = span;
	this->type = type;
	counter = 0;
}

void Animation::addPoint(float x, float y, float z) {

	points.push_back(new Point(x, y, z));
}

void Animation::calculateDelta() {
	float deltax, deltay, deltaz;
	float t_dist = 0;
	float time_tmp;
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

		increments.push_back(dist[i] / deltax);

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

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

