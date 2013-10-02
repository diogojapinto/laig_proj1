/*
 * MyRectangle.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyRectangle.h"
#include "CGFapplication.h"
#include "Scene.h"

MyRectangle::MyRectangle() {
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

MyRectangle::MyRectangle(float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

MyRectangle::~MyRectangle() {
}

void MyRectangle::draw() {

	float deltax, deltay, deltas, deltat;

	deltax = x2 - x1;
	deltay = y2 - y1;

	deltas = deltax / getAppearance()->getSWrap();
	deltat = deltay / getAppearance()->getTWrap();

	glPushMatrix();
	glBegin(GL_QUADS);

	if (scene->getCullorder() == "CCW") {
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x1, y1, 0.0);
		glTexCoord2f(deltas, 0.0);
		glVertex3f(x2, y1, 0.0);
		glTexCoord2f(deltas, deltat);
		glVertex3f(x2, y2, 0.0);
		glTexCoord2f(0.0, deltat);
		glVertex3f(x1, y2, 0.0);
	} else {
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x1, y1, 0.0);
		glTexCoord2f(0.0, deltat);
		glVertex3f(x1, y2, 0.0);
		glTexCoord2f(deltas, deltat);
		glVertex3f(x2, y2, 0.0);
		glTexCoord2f(deltas, 0.0);
		glVertex3f(x2, y1, 0.0);
	}
	glEnd();
	glPopMatrix();
}
