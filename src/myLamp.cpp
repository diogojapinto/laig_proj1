/*
 * myLamp.cpp
 *
 *  Created on: Mar 19, 2013
 *      Author: knoweat
 */

#include "myLamp.h"

// Coefficients for wood
float ambLW[3] = { 0.5, 0.2, 0.0 };
float difLW[3] = { 0.5, 0.2, 0.0 };
float specLW[3] = { 0.2, 0.2, 0.2 };
float shininessLW = 50.f;

// Coefficients for metal
float ambLS[3] = { 0.2, 0.2, 0.2 };
float difLS[3] = { 0.2, 0.2, 0.2 };
float specLS[3] = { 0.9, 0.9, 0.9 };
float shininessLS = 150.f;

myLamp::myLamp() {
	cube = new myUnitCube();
	h_sphere = new myHalfSphere(20, 20, true);
	cylinder = new myCylinder(20, 20, true);

	materialLW = new CGFappearance(ambLW, difLW, specLW, shininessLW);
	materialLW->setTexture("textures"+(string)SLASH+"table.png");

	materialLS = new CGFappearance(ambLS, difLS, specLS, shininessLS);
}

myLamp::~myLamp() {
	delete (cube);
	delete (h_sphere);
	delete (cylinder);
}

void myLamp::draw() {
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glScaled(1.0, 0.5, 1.0);
	materialLS->apply();
	h_sphere->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 2.25, 0.0);
	glScaled(0.25, 4.0, 0.25);
	materialLW->apply();
	cylinder->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 4.5, 0.0);
	glScaled(0.75, 0.75, 0.75);
	materialLS->apply();
	cube->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 5.75, 1.5);
	glRotated(45.0, 1.0, 0.0, 0.0);
	glScaled(0.25, 4.0, 0.25);
	materialLW->apply();
	cylinder->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 7.25, 3.0);
	glScaled(0.75, 0.75, 0.75);
	materialLS->apply();
	cube->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 7.25, 5);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glScaled(0.25, 4.0, 0.25);
	materialLW->apply();
	cylinder->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 7.25, 7.0);
	glScaled(0.75, 0.75, 0.75);
	materialLS->apply();
	cube->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 6.25, 7.0);
	materialLS->apply();
	h_sphere->draw();
	glPopMatrix();

	glEnable(GL_CULL_FACE);
}

