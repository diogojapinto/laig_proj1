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
	vec_index = 0;
	time_passed = 0;
	time(&time_last);
	//points.push_back(new Point(0, 0, 0));
	direction.push_back(new Point(0, 0, 1));
}

void Animation::addPoint(float x, float y, float z) {

	if (points.size() != 0) {
		Point *pt = new Point(points.back()->getX() + x, points.back()->getY() + y, points.back()->getZ() + z);

		direction.push_back(
		 new Point(pt->getX() - points.back()->getX(), pt->getY() - points.back()->getY(),
		 pt->getZ() - points.back()->getZ()));
		points.push_back(pt);
	} else {
		points.push_back(new Point(x, y, z));
		point.setX(x);
		point.setY(y);
		point.setZ(z);
	}

}

void Animation::calculateDelta() {
	float deltax, deltay, deltaz;
	float t_dist = 0;
	float time_tmp;
	vector<float> dist;
	vector<float> increments;
	vector<Point*> delta_tmp;

	for (int i = 1; i < points.size(); i++) {
		dist.push_back(distanceTwoPoints(points[i], points[i - 1]));

		t_dist += dist[i - 1];

		deltax = points[i]->getX() - points[i - 1]->getX();
		deltay = points[i]->getY() - points[i - 1]->getY();
		deltaz = points[i]->getZ() - points[i - 1]->getZ();

		delta_tmp.push_back(new Point(deltax, deltay, deltaz));

		float angle = 0;

		 angle = acos(
		 crossProduct(direction[i], direction[i - 1])
		 / (vectorSize(direction[i]) * vectorSize(direction[i - 1])));

		 rotations.push_back(RadToDeg(angle));
	}

	for (int i = 0; i < dist.size(); i++) {
		time_tmp = dist[i] / t_dist * span;
		deltax = delta_tmp[i]->getX() / time_tmp;
		deltay = delta_tmp[i]->getY() / time_tmp;
		deltaz = delta_tmp[i]->getZ() / time_tmp;

		if (deltax != 0) {
			increments.push_back(fabs(dist[i] / deltax));
		} else if (deltay != 0) {
			increments.push_back(fabs(dist[i] / deltay));
		} else {
			increments.push_back(fabs(dist[i] / deltaz));
		}

		time_exp.push_back(time_tmp / increments[i]);

		delta.push_back(new Point(deltax, deltay, deltaz));
	}

}
vector<Point*> Animation::getPoints() {
	return points;
}

float Animation::getSpan() {
	return span;
}

int Animation::getTime() {
	return time_exp[vec_index];
}

Point* Animation::getDelta() {
	return delta[vec_index];
}

float Animation::getRotation() {
	return rotations[vec_index];
}

Point Animation::getPoint() {
	return point;
}

float Animation::updateValues() {

	time_t timer;
	float sub = time(&timer) - time_last;
	float ratio = sub / time_exp[vec_index];
	time_last = timer;
	time_passed += sub;
	if ((point.getX() != points.back()->getX()) || (point.getY() != points.back()->getY())
					|| (point.getZ() != points.back()->getZ())) {
		point.setX(point.getX() + (delta[vec_index]->getX() * ratio));
		point.setY(point.getY() + (delta[vec_index]->getY() * ratio));
		point.setZ(point.getZ() + (delta[vec_index]->getZ() * ratio));

		if ((point.getX() == points[vec_index+1]->getX()) && (point.getY() == points[vec_index+1]->getY())
				&& (point.getZ() == points[vec_index+1]->getZ())) {
			vec_index++;
		}
		return ratio;
	} else {
		return 0;
	}

	return 0;
}
Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

