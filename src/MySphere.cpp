/*
 * MySphere.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MySphere.h"

MySphere::MySphere() {
	q = gluNewQuadric();
	gluQuadricTexture(q, true);
}

MySphere::~MySphere() {
	gluDeleteQuadric(q);
}

void MySphere::draw() {
	gluSphere(q, 0.5, 10, 10);
}
