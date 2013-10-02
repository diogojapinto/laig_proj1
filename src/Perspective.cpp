/*
 * Perspective.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#include "Perspective.h"
#include "CGFapplication.h"
#include "Scene.h"

using namespace std;

Perspective::Perspective() /*:Camera()*/{
	angle = 0;
	px = 0;
	py = 0;
	pz = 0;
	tx = 0;
	ty = 0;
	tz = 0;

}

Perspective::Perspective(string id) /*:
 Camera(id)*/{
	angle = 0;
	px = 0;
	py = 0;
	pz = 0;
	tx = 0;
	ty = 0;
	tz = 0;
}
void Perspective::setAngle(float angle) {
	this->angle = angle;
}

void Perspective::setPos(float px, float py, float pz) {
	this->px = px;
	this->py = py;
	this->pz = pz;
}

void Perspective::setTarget(float tx, float ty, float tz) {
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}

float Perspective::getAngle() {
	return angle;
}

float Perspective::getPosX() {
	return px;
}

float Perspective::getPosY() {
	return py;
}

float Perspective::getPosZ() {
	return pz;
}

float Perspective::getTargetX() {
	return tx;
}

float Perspective::getTargetY() {
	return ty;
}

float Perspective::getTargetZ() {
	return tz;
}

void Perspective::setCamera() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, HEIGHT / WIDTH, near, far);  //setting up Perspective
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(px, py, pz, tx, ty, tz, 0, 1, 0); //vector direction is always up

}

Perspective::~Perspective() {
	// TODO Auto-generated destructor stub
}
