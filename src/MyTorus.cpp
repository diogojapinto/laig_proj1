/*
 * MyTorus.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MyTorus.h"
#include "CGFapplication.h"

MyTorus::MyTorus() {
	this->inner = 0.5;
	this->outer = 1.5;
	this->slices = 10;
	this->loops = 10;
}

MyTorus::MyTorus(float inner, float outer, unsigned int slices,
        unsigned int loops) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

MyTorus::~MyTorus() {
}

void MyTorus::draw() {
	glEnable(GL_TEXTURE_2D);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glutSolidTorus(0.5, 1.0, 10, 10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void MyTorus::calcPoints() {

}

void MyTorus::calcNormals() {

}

void MyTorus::calcTextCoords() {

}

