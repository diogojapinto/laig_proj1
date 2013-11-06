/*
 * Plane.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: wso277
 */

#include "Plane.h"
#include "GL/glut.h"
#include "Scene.h"

<<<<<<< HEAD
Plane::Plane() {
	// TODO Auto-generated constructor stub

}

Plane::Plane(unsigned int parts) {
	this->parts = parts;

	ctrl_pts[0][0] = -0.5;
	ctrl_pts[0][1] = 0;
	ctrl_pts[0][2] = 0.5;

	ctrl_pts[1][0] = 0.5;
	ctrl_pts[1][1] = 0;
	ctrl_pts[1][2] = 0.5;

	ctrl_pts[2][0] = -0.5;
	ctrl_pts[2][1] = 0;
	ctrl_pts[2][2] = -0.5;

	ctrl_pts[3][0] = 0.5;
	ctrl_pts[3][1] = 0;
	ctrl_pts[3][2] = -0.5;
=======
Plane::Plane() :
		MyPrimitive() {

}

Plane::Plane(unsigned int parts) :
		MyPrimitive() {
	this->parts = parts;

	ctrl_pts[0][0] = -0.5;
	ctrl_pts[0][1] = 0.0;
	ctrl_pts[0][2] = -0.5;

	ctrl_pts[1][0] = 0.5;
	ctrl_pts[1][1] = 0.0;
	ctrl_pts[1][2] = -0.5;

	ctrl_pts[2][0] = -0.5;
	ctrl_pts[2][1] = 0.0;
	ctrl_pts[2][2] = 0.5;

	ctrl_pts[3][0] = 0.5;
	ctrl_pts[3][1] = 0.0;
	ctrl_pts[3][2] = 0.5;
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

	nrml_pts[0][0] = 0;
	nrml_pts[0][1] = 1;
	nrml_pts[0][2] = 0;

	nrml_pts[1][0] = 0;
	nrml_pts[1][1] = 1;
	nrml_pts[1][2] = 0;

	nrml_pts[2][0] = 0;
	nrml_pts[2][1] = 1;
	nrml_pts[2][2] = 0;

	nrml_pts[3][0] = 0;
	nrml_pts[3][1] = 1;
	nrml_pts[3][2] = 0;

	text_pts[0][0] = 0;
<<<<<<< HEAD
	text_pts[0][1] = 0;

	text_pts[1][0] = 1;
	text_pts[1][1] = 0;

	text_pts[2][0] = 0;
	text_pts[2][1] = 1;

	text_pts[3][0] = 1;
	text_pts[3][1] = 1;
}
void Plane::draw() {

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, 6, 2, &ctrl_pts[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0, 1, 3, 2, 0, 1, 6, 2, &nrml_pts[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &text_pts[0][0]);
=======
	text_pts[0][1] = 1;

	text_pts[1][0] = 1;
	text_pts[1][1] = 1;

	text_pts[2][0] = 0;
	text_pts[2][1] = 0;

	text_pts[3][0] = 1;
	text_pts[3][1] = 0;
}
void Plane::draw() {

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &ctrl_pts[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &nrml_pts[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &text_pts[0][0]);
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

<<<<<<< HEAD
	glMapGrid2f(parts, 0.0,1.0, parts, 0.0,1.0);

	glEvalMesh2(Scene::getInstance()->getDrawmode(), 0, 1, 0, 1);
=======
	glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0);

	glEvalMesh2(Scene::getInstance()->getDrawmode(), 0.0, parts, 0.0, parts);
>>>>>>> ce56f48cb58fa4338920a12aa4daee027f3d7ed4

	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
}
void Plane::setAppearance(string appearance) {
	MyPrimitive::setAppearance(appearance);
}

Plane::~Plane() {
}

