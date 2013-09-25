/*
 * MySphere.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MySphere.h"
#include "CGFapplication.h"

MySphere::MySphere() {
	// TODO Auto-generated constructor stub

}

MySphere::~MySphere() {
	// TODO Auto-generated destructor stub
}

void MySphere::draw() {
	glutSolidSphere(0.5,10,10);
}
