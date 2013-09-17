/*
 * myChair.cpp
 *
 *  Created on: Feb 26, 2013
 *      Author: knoweat
 */

#include "myChair.h"

// Coefficients for chair's top
float ambCT[3] = { 0.3, 0.3, 0.3 };
float difCT[3] = { 0.5, 0.3, 0.0 };
float specCT[3] = { 0.2, 0.2, 0.2 };
float shininessCT = 50.f;

// Coefficients for chair's legs
float ambCL[3] = { 0.2, 0.2, 0.2 };
float difCL[3] = { 0.2, 0.2, 0.2 };
float specCL[3] = { 0.9, 0.9, 0.9 };
float shininessCL = 150.f;

myChair::myChair() {
	angle = ((int) rand()) % 41 - 20;
	x = (float) rand() / ((float) RAND_MAX / 0.5) - 0.25;
	z = (float) rand() / ((float) RAND_MAX / 0.5) - 0.25;

	materialCT = new CGFappearance(ambCT, difCT, specCT, shininessCT);
	materialCT->setTexture("textures"+(string)SLASH+"table.png");

	materialCL = new CGFappearance(ambCL, difCL, specCL, shininessCL);
}

void myChair::draw() {
	glPushMatrix();

	glRotatef(angle, 0, 1, 0);
	glTranslatef(x, 0, z);

	//tampo da cadeira
	glPushMatrix();
	glTranslated(0, 2.85, 0);
	glScaled(3, 0.3, 3);
	materialCT->apply();
	cube.draw();
	glPopMatrix();

	//encosto da cadeira
	glPushMatrix();
	glTranslated(0, 4.5, -1.35);
	glScaled(3, 3, 0.3);
	materialCT->apply();
	cube.draw();
	glPopMatrix();

	//pernas da cadeira
	glPushMatrix();
	glTranslated(-1.35, 1.4, -1.35);
	glScaled(0.3, 2.6, 0.3);
	materialCL->apply();
	cube.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.35, 1.4, 1.35);
	glScaled(0.3, 2.6, 0.3);
	materialCL->apply();
	cube.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.35, 1.4, -1.35);
	glScaled(0.3, 2.6, 0.3);
	materialCL->apply();
	cube.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.35, 1.4, 1.35);
	glScaled(0.3, 2.6, 0.3);
	materialCL->apply();
	cube.draw();
	glPopMatrix();

	glPopMatrix();
}
