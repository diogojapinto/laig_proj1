/*
 * MyPatch.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: diogo
 */

#include <MyPatch.h>
#include <GL/gl.h>
#include <math.h>

MyPatch::MyPatch() :
		MyPrimitive() {
	this->order = 1;
	this->partsU = 1;
	this->partsV = 1;
	this->compute = GL_FILL;
	ctrlPoints = new int[pow(order + 1, 2)];
	nrCtrlPoints = 0;
}

MyPatch::~MyPatch() {
}

MyPatch::MyPatch(int order, int partsU, int partsV, string compute) :
		MyPrimitive() {
	this->order = order;
	this->partsU = partsU;
	this->partsV = partsV;

	if (compute == "fill") {
		this->compute = GL_FILL;
	} else if (compute == "line") {
		this->compute = GL_LINE;
	} else if (compute == "point") {
		this->compute = GL_POINT;
	} else {
		throw InvalidPreAttrException("compute");
	}

	ctrlPoints = new int[pow(order + 1, 2)];
	nrCtrlPoints = 0;
}

void MyPatch::addControlPoint(int x, int y, int z) {
	if (nrCtrlPoints <= pow(order + 1, 2)) {
		ctrlPoints[nrCtrlPoints * 3] = x;
		ctrlPoints[nrCtrlPoints * 3 + 1] = y;
		ctrlPoints[nrCtrlPoints * 3 + 2] = z;
		nrCtrlPoints++;
	}
}

virtual void MyPatch::draw() {
	if (nrCtrlPoints == pow(order + 1, 2)) {
		glPolygonMode(GL_FRONT_AND_BACK, compute);
		/*
		 * do things
		 */
		glPolygonMode(GL_FRONT_AND_BACK, Scene::getInstance()->getDrawmode());
	}
}
