/*
 * MyRectangle.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyRectangle.h"
#include "CGFapplication.h"

MyRectangle::MyRectangle() {
	// TODO Auto-generated constructor stub

}

MyRectangle::~MyRectangle() {
	// TODO Auto-generated destructor stub
}

void MyRectangle::draw() {
	glPushMatrix();
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, 0.0, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.0, -0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.0, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.0, -0.5);
	glEnd();
	glPopMatrix();
}
