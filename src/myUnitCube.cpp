/*
 * myUnitCube.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: knoweat
 */

#include "myUnitCube.h"

void myUnitCube::draw() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.5);
	drawBaseSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -0.5);
	glRotated(180, 0, 1, 0);
	drawBaseSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotated(90, 0, 1, 0);
	drawBaseSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0, 0);
	glRotated(-90, 0, 1, 0);
	drawBaseSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.5, 0);
	glRotated(90, 1, 0, 0);
	drawBaseSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotated(-90, 1, 0, 0);
	drawBaseSquare();
	glPopMatrix();

	glPopMatrix();
}

void myUnitCube::drawBaseSquare() {
	glNormal3b(0, 0, 1);
	//glRectd(-0.5, -0.5, 0.5, 0.5);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	plane.draw();
	glPopMatrix();
}

myUnitCube::myUnitCube() {
	plane = Plane(10);
}

