/*
 * MyPatch.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: diogo
 */

#include <MyPatch.h>
#include <GL/gl.h>
#include <math.h>
<<<<<<< HEAD
=======
#include "InvalidPreAttrException.h"
#include "Scene.h"
#include <iostream>
#include <stdio.h>
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

MyPatch::MyPatch() :
		MyPrimitive() {
	this->order = 1;
	this->partsU = 1;
	this->partsV = 1;
	this->compute = GL_FILL;
<<<<<<< HEAD
	ctrlPoints = new int[pow(order + 1, 2)];
	nrCtrlPoints = 0;
=======
	//int nr = pow(order + 1, 2);
	//ctrlPoints = new float[nr];
	nrCtrlPoints = 0;

	textPoints.push_back(0.0);
	textPoints.push_back(1.0);

	textPoints.push_back(1.0);
	textPoints.push_back(1.0);

	textPoints.push_back(0.0);
	textPoints.push_back(0.0);

	textPoints.push_back(1.0);
	textPoints.push_back(0.0);
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4
}

MyPatch::~MyPatch() {
}

MyPatch::MyPatch(int order, int partsU, int partsV, string compute) :
		MyPrimitive() {
<<<<<<< HEAD
=======

	if (order < 1 || order > 3) {
		throw InvalidPreAttrException("order");
	}

>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4
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

<<<<<<< HEAD
	ctrlPoints = new int[pow(order + 1, 2)];
	nrCtrlPoints = 0;
}

void MyPatch::addControlPoint(int x, int y, int z) {
	if (nrCtrlPoints <= pow(order + 1, 2)) {
		ctrlPoints[nrCtrlPoints * 3] = x;
		ctrlPoints[nrCtrlPoints * 3 + 1] = y;
		ctrlPoints[nrCtrlPoints * 3 + 2] = z;
=======
	//int nr = pow(order + 1, 2);
	//ctrlPoints = new float[nr];
	nrCtrlPoints = 0;

	textPoints.push_back(0.0);
	textPoints.push_back(1.0);

	textPoints.push_back(1.0);
	textPoints.push_back(1.0);

	textPoints.push_back(0.0);
	textPoints.push_back(0.0);

	textPoints.push_back(1.0);
	textPoints.push_back(0.0);
}

void MyPatch::addControlPoint(float x, float y, float z) {
	if (nrCtrlPoints < pow(order + 1, 2)) {
		ctrlPoints.push_back(x);
		ctrlPoints.push_back(y);
		ctrlPoints.push_back(z);
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4
		nrCtrlPoints++;
	}
}

<<<<<<< HEAD
virtual void MyPatch::draw() {
	if (nrCtrlPoints == pow(order + 1, 2)) {
		glPolygonMode(GL_FRONT_AND_BACK, compute);
		/*
		 * do things
		 */
		glPolygonMode(GL_FRONT_AND_BACK, Scene::getInstance()->getDrawmode());
	}
}
=======
void MyPatch::draw() {
	if (nrCtrlPoints == pow(order + 1, 2)) {
		if (Scene::getInstance()->getCullorder() == GL_CCW) {
			glFrontFace(GL_CW);
		}

		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_MAP2_TEXTURE_COORD_2);

		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order + 1, 0.0, 1.0, (order + 1) * 3, order + 1, &ctrlPoints[0]);
		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &textPoints[0]);

		glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);

		glEvalMesh2(compute, 0.0, partsU, 0.0, partsV);

		glDisable(GL_MAP2_VERTEX_3);
		glDisable(GL_AUTO_NORMAL);
		glDisable(GL_MAP2_TEXTURE_COORD_2);

		glFrontFace(Scene::getInstance()->getCullorder());
	}
}

void MyPatch::setAppearance(string appearance) {
	MyPrimitive::setAppearance(appearance);
}
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4
