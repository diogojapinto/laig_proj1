/*
 * MyTriangle.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyTriangle.h"
#include "CGFapplication.h"

MyTriangle::MyTriangle() {
	// TODO Auto-generated constructor stub

}

MyTriangle::~MyTriangle() {
	// TODO Auto-generated destructor stub
}

void MyTriangle::draw() {
	glNormal3f(0.0,1.0,0.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-0.5,0.0,-0.5);
	glVertex3f(-0.5,0.0,0.5);
	glVertex3f(0.5,0.0,0.5);
	glEnd();
}
