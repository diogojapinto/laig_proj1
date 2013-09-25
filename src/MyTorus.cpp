/*
 * MyTorus.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MyTorus.h"
#include "CGFapplication.h"

MyTorus::MyTorus() {

}

MyTorus::~MyTorus() {
}

void MyTorus::draw() {
	glEnable(GL_TEXTURE_2D);
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glutSolidTorus(0.5,1.0,10,10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}
