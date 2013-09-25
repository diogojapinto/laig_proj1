/*
 * MyCylinder.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MyCylinder.h"
#include <math.h>

float pi = acos(-1.0);
float deg2rad = pi / 180.0;

MyCylinder::MyCylinder() {

	q = gluNewQuadric();

}

MyCylinder::~MyCylinder() {

	gluDeleteQuadric(q);
}

void MyCylinder::draw() {
	gluCylinder(q,0.5,0.5,1,10,10);

	glPushMatrix();
	glTranslatef(0.0,0.0,1.0);
	glRotatef(90.0,1.0,0.0,0.0);
	drawCircle();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
	drawCircle();
	glPopMatrix();



}

void MyCylinder::drawCircle() {

	glNormal3f(0.0,1.0,0.0);

	float ang_slice = 360.0 / 10.0;

	glBegin(GL_TRIANGLE_STRIP);

		for (int i=0; i <= 10; i++) {
			glVertex3f(cos(((i * ang_slice) + 90.0) * deg2rad) / 2.0, 0.0, sin(((i * ang_slice) + 90.0) * deg2rad) / 2.0);
			glVertex3f(0.0,0.0,0.0);
		}

	glEnd();

}

