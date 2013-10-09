/*
 * MyRectangle.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyRectangle.h"
#include "GL/glut.h"
#include "Scene.h"

extern Scene *scene;

MyRectangle::MyRectangle() {
	x1 = -0.5;
	y1 = -0.5;
	x2 = 0.5;
	y2 = 0.5;

	calcNormal();
	calcTextCoords();
}

MyRectangle::MyRectangle(float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

MyRectangle::~MyRectangle() {
}

void MyRectangle::draw() {
	glBegin(GL_QUADS);

	glNormal3f(normal[0], normal[1], normal[2]);
	if (Scene::getInstance()->getCullorder() == GL_CCW) {
		glTexCoord2f(text_coords[0][0], text_coords[0][1]);
		glVertex3f(x1, y1, 0.0);
		glTexCoord2f(text_coords[1][0], text_coords[1][1]);
		glVertex3f(x2, y1, 0.0);
		glTexCoord2f(text_coords[2][0], text_coords[2][1]);
		glVertex3f(x2, y2, 0.0);
		glTexCoord2f(text_coords[3][0], text_coords[3][1]);
		glVertex3f(x1, y2, 0.0);
	} else {
		glTexCoord2f(text_coords[0][0], text_coords[0][1]);
		glVertex3f(x1, y1, 0.0);
		glTexCoord2f(text_coords[1][0], text_coords[1][1]);
		glVertex3f(x1, y2, 0.0);
		glTexCoord2f(text_coords[2][0], text_coords[2][1]);
		glVertex3f(x2, y2, 0.0);
		glTexCoord2f(text_coords[3][0], text_coords[3][1]);
		glVertex3f(x2, y1, 0.0);
	}
	glEnd();
}

const float *MyRectangle::calcNormal() {
	if (Scene::getInstance()->getCullorder() == GL_CCW) {
		normal[0] = 0.0;
		normal[1] = 0.0;
		normal[2] = 1.0;
	} else {
		normal[0] = 0.0;
		normal[1] = 0.0;
		normal[2] = -1.0;
	}

	return normal;
}

void MyRectangle::calcTextCoords() {
	float deltax, deltay, deltas, deltat;

	deltax = x2 - x1;
	deltay = y2 - y1;

	deltas = deltax / getAppearance()->getSWrap();
	deltat = deltay / getAppearance()->getTWrap();

	if (Scene::getInstance()->getCullface() == GL_CCW) {
		text_coords[0][0] = 0.0;
		text_coords[0][1] = 0.0;
		text_coords[1][0] = deltas;
		text_coords[1][1] = 0.0;
		text_coords[2][0] = deltas;
		text_coords[2][1] = deltat;
		text_coords[3][0] = 0.0;
		text_coords[3][1] = deltat;
	} else {
		text_coords[0][0] = 0.0;
		text_coords[0][1] = 0.0;
		text_coords[1][0] = 0.0;
		text_coords[1][1] = deltat;
		text_coords[2][0] = deltas;
		text_coords[2][1] = deltat;
		text_coords[3][0] = deltas;
		text_coords[3][1] = 0.0;
	}
}
