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
	glNormal3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
	glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();
}
