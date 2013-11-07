/*
 * MyVehicle.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: wso277
 */

#include "MyVehicle.h"
#include "GL/gl.h"

MyVehicle::MyVehicle() :
		MyPrimitive() {
	center = new MySphere(0.8, 20, 20);

	top = new MyPatch(3, 20, 20, "fill");

	top->addControlPoint(-1.0, 0, -1.0);
	top->addControlPoint(-0.5, 0.5, -1.0);
	top->addControlPoint(0.5, 0.5, -1.0);
	top->addControlPoint(1.0, 0, -1.0);

	top->addControlPoint(-1.5, -0.5, 1.0);
	top->addControlPoint(-0.5, -0.5, 3.0);
	top->addControlPoint(0.5, -0.5, 0.0);
	top->addControlPoint(1.5, -0.5, -1.0);

	top->addControlPoint(-1.5, 0.5, 4.0);
	top->addControlPoint(-0.5, 0.5, 0.0);
	top->addControlPoint(0.5, 0.5, 3.0);
	top->addControlPoint(1.5, 0.5, 4.0);

	top->addControlPoint(-1.5, 1.5, -2.0);
	top->addControlPoint(-0.5, 1.5, -2.0);
	top->addControlPoint(0.5, 1.5, 0.0);
	top->addControlPoint(1.5, 1.5, -1.0);

}

MyVehicle::~MyVehicle() {
}

void MyVehicle::draw() {

	glPushMatrix();
	glTranslatef(10,2,10);
	center->draw();
	//top->draw();

	glPopMatrix();
}

void MyVehicle::setAppearance(string appearance) {
	MyPrimitive::setAppearance(appearance);
}
