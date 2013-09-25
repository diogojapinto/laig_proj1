/*
 * MyRectangle.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyRectangle.h"
#include "CGFapplication.h"

MyRectangle::MyRectangle() {
	num_divisions = 100;
}

MyRectangle::~MyRectangle() {
}

void MyRectangle::draw() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-0.5,-0.5,0.0);
	glTexCoord2f(0.0,0.0);
	glVertex3f(0.5,-0.5,0.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(0.5,0.5,0.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-0.5,0.5,0.0);
	glEnd();
	glPopMatrix();
}
