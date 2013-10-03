/*
 * MySphere.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MySphere.h"

MySphere::MySphere() {
	this->radius = 0.5;
	this->slices = 10;
	this->stacks = 10;

	q = gluNewQuadric();
	gluQuadricTexture(q, true);
}

MySphere::MySphere(float radius, unsigned int slices, unsigned int stacks) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;

	q = gluNewQuadric();
	gluQuadricTexture(q, true);
}

MySphere::~MySphere() {
	gluDeleteQuadric(q);
}

void MySphere::draw() {
	gluSphere(q, radius, slices, stacks);
}
