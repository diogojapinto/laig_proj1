/*
 * MyPatch.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: diogo
 */

#include <MyPatch.h>
#include <GL/gl.h>
#include <math.h>
#include "InvalidPreAttrException.h"
#include "Scene.h"

MyPatch::MyPatch() :
		MyPrimitive() {
	this->order = 1;
	this->partsU = 1;
	this->partsV = 1;
	this->compute = GL_FILL;
	int nr = pow(order + 1, 2);
	ctrlPoints = new float[nr];
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

	int nr = pow(order + 1, 2);
	ctrlPoints = new float[nr];
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

void MyPatch::draw() {
	if (nrCtrlPoints == pow(order + 1, 2)) {
		glPolygonMode(GL_FRONT_AND_BACK, compute);
		if (Scene::getInstance()->getCullorder() == GL_CCW) {
			glFrontFace(GL_CW);
		}
		//glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, order, 0, 1, 6, order, &ctrlPoints[0]);
		//glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,
		//		&text_pts[0][0]);

		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_MAP2_NORMAL);
		//glEnable(GL_MAP2_TEXTURE_COORD_2);

		glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);

		glEnable(GL_AUTO_NORMAL);
		glEvalMesh2(Scene::getInstance()->getDrawmode(), 0, 1, 0, 1);

		glDisable(GL_MAP2_VERTEX_3);
		glDisable(GL_AUTO_NORMAL);
		glDisable(GL_MAP2_NORMAL);
		//glDisable(GL_MAP2_TEXTURE_COORD_2);

		glFrontFace(Scene::getInstance()->getCullorder());
		glPolygonMode(GL_FRONT_AND_BACK, Scene::getInstance()->getDrawmode());
	}
}
