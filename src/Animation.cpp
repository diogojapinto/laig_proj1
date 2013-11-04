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
#include <sys/time.h>

Animation::Animation() {

}

Animation::Animation(string id, float span, string type) {
	this->id = id;
	this->span = span;
	this->type = type;
	vec_index = 0;
	time_passed = 0;
	time_line = 0;
	printf("kldgkdf\n");
	struct timeval t;
	gettimeofday(&t, 0);
	time_last = t.tv_usec * 0.000001;
	printf("kldgkdf\n");
	direction.push_back(new Point(0, 0, 1));
}

void Animation::addPoint(float x, float y, float z) {

	if (points.size() != 0) {
		Point *pt = new Point(x, y, z);

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

	for (int i = 1; i < points.size(); i++) {
		dist.push_back(distanceTwoPoints(points[i], points[i - 1]));

		t_dist += dist[i - 1];

		deltax = points[i]->getX() - points[i - 1]->getX();
		deltay = points[i]->getY() - points[i - 1]->getY();
		deltaz = points[i]->getZ() - points[i - 1]->getZ();

		delta.push_back(new Point(deltax, deltay, deltaz));

		float angle = 0;

		angle = acos(
				crossProduct(direction[i], direction[i - 1])
						/ (vectorSize(direction[i]) * vectorSize(direction[i - 1])));

		rotations.push_back(RadToDeg(angle));
	}

	for (int i = 0; i < dist.size(); i++) {
		time_tmp = dist[i] * span / t_dist;
		time_exp.push_back(time_tmp);
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

	struct timeval t;
	gettimeofday(&t, 0);
	float timer = t.tv_usec * 0.000001;
	float sub = fabs(timer - time_last);
	float ratio = sub / time_exp[vec_index];
	time_last = timer;
	time_passed += sub;
	time_line += sub;
	/*printf("sub: %lf\n", sub);
	printf("time_exp: %lf\n", time_exp[vec_index]);
	printf("ratio: %lf\n", ratio);*/
	if (time_passed < span) {
		point.setX(point.getX() + (delta[vec_index]->getX() * ratio));
		point.setY(point.getY() + (delta[vec_index]->getY() * ratio));
		point.setZ(point.getZ() + (delta[vec_index]->getZ() * ratio));

		if (time_line >= time_exp[vec_index]) {
			time_line = 0;
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
