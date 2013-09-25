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
	gluQuadricTexture(q,true);

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
			float x = cos(((i * ang_slice) + 90.0) * deg2rad) / 2.0;
			float y = sin(((i * ang_slice) + 90.0) * deg2rad) / 2.0;
			glTexCoord2f(x + 0.5, y+ 0.5);
			glVertex3f(x, 0.0, y);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0.0,0.0,0.0);
		}
	glEnd();
}

