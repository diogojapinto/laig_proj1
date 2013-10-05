/*
 * MyTorus.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#include "MyTorus.h"
#include "CGFapplication.h"
#include <math.h>

extern float deg2rad;

MyTorus::MyTorus() {
	this->inner = 0.5;
	this->outer = 1.5;
	this->slices = 10;
	this->loops = 10;

	this->px = (float **) malloc(sizeof(float *) * (loops + 1));
	for (unsigned int i = 0; i <= loops; i++) {
		px[i] = (float *) malloc(sizeof(float) * (slices + 1));
	}

	this->py = (float **) malloc(sizeof(float *) * (loops + 1));
	for (unsigned int i = 0; i <= loops; i++) {
		py[i] = (float *) malloc(sizeof(float) * (slices + 1));
	}

	pz = (float *) malloc(sizeof(float) * (loops + 1));

	calcPoints();

}

MyTorus::MyTorus(float inner, float outer, unsigned int slices,
        unsigned int loops) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;

	this->px = (float **) malloc(sizeof(float *) * (loops + 1));
	for (unsigned int i = 0; i <= loops; i++) {
		px[i] = (float *) malloc(sizeof(float) * (slices + 1));
	}

	this->py = (float **) malloc(sizeof(float *) * (loops + 1));
	for (unsigned int i = 0; i <= loops; i++) {
		py[i] = (float *) malloc(sizeof(float) * (slices + 1));
	}

	pz = (float *) malloc(sizeof(float) * (loops + 1));

	calcPoints();
}

MyTorus::~MyTorus() {
}

void MyTorus::draw() {
	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < loops; i++) {
		for (unsigned int j = 0; j < slices; j++) {
			glVertex3f(px[i + 1][j], py[i + 1][j], pz[i + 1]);
			glVertex3f(px[i][j + 1], py[i][j + 1], pz[i]);
		}
		glVertex3f(px[i + 1][slices], py[i + 1][slices], pz[i + 1]);
	}
	glEnd();
	glPopMatrix();
}

void MyTorus::calcPoints() {
	float phi_step = 360.0 / loops;
	float teta_step = 360.0 / slices;

	float main_radius = (inner + outer) / 2.0;
	float sec_radius = (outer - inner) / 2.0;

	float phi = -90.0;
	for (unsigned int i = 0; i <= loops; i++) {
		float teta = 0.0;
		pz[i] = sec_radius * cosf(phi * deg2rad);
		for (unsigned int j = 0; j <= slices; j++) {
			px[i][j] = (main_radius + sec_radius * sinf(phi * deg2rad))
			        * cosf(teta * deg2rad);
			py[i][j] = (main_radius + sec_radius * sinf(phi * deg2rad))
			        * sinf(teta * deg2rad);
			teta += teta_step;
		}
		phi += phi_step;
	}
}

void MyTorus::calcNormals() {

}

void MyTorus::calcTextCoords() {

}

