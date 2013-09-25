/*
 * MyTorus.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MyTorus.h"
#include "CGFapplication.h"

MyTorus::MyTorus() {
	// TODO Auto-generated constructor stub

}

MyTorus::~MyTorus() {
	// TODO Auto-generated destructor stub
}

void MyTorus::draw() {
	glutSolidTorus(0.5,1.0,10,10);
}
