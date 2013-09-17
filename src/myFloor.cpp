/*
 * myFloor.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: knoweat
 */

#include "myFloor.h"

void myFloor::draw() {
	glPushMatrix();
	glTranslated(0, 0.05, 0);
	glScaled(8, 0.1, 6);
	cube.draw();
	glPopMatrix();
}
