/*
 * Scene.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#include "Scene.h"
#include "CGFapplication.h"

using namespace std;

Scene::Scene() {
	bckg_x = 0;
	bckg_y = 0;
	bckg_z = 0;
	bckg_a = 0;
	drawmode = "";
	shading = "";
	cullface = "";
	cullorder = "";
}

void Scene::setBackground(float bckg_x, float bckg_y, float bckg_z,
		float bckg_a) {
	this->bckg_x = bckg_x;
	this->bckg_y = bckg_y;
	this->bckg_z = bckg_z;
	this->bckg_a = bckg_a;
}

void Scene::setDrawmode(string drawmode) {
	this->drawmode = drawmode;
}

void Scene::setShading(string shading) {
	this->shading = shading;
}

void Scene::setCullface(string cullface) {
	this->cullface = cullface;
}

void Scene::setCullorder(string cullorder) {
	this->cullorder = cullorder;
}

void Scene::addLight(Lights* light) {
	lights.push_back(light);
}

void Scene::addCamera(Camera* camera) {
	cameras.push_back(camera);
}

string Scene::getDrawmode() {
	return drawmode;
}

string Scene::getShading() {
	return shading;
}

string Scene::getCullface() {
	return cullface;
}

string Scene::getCullorder() {
	return cullorder;
}

Lights* Scene::getLight(int index) {
	return lights[index];
}

Camera* Scene::getCamera(int index) {
	return cameras[index];
}

void applyDrawmode(string drawmode) {
	if (drawmode == "fill") {
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
	} else if (drawmode == "line") {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
	}
}
void applyShading(string shading) {
	if (shading == "flat") {
		glShadeModel(GL_FLAT);
	} else {
		glShadeModel(GL_SMOOTH);
	}
}

void applyCullface(string cullface) {
	if (cullface == "none") {
		glCullFace(GL_NONE);
	} else if (cullface == "back") {
		glCullFace(GL_BACK);
	} else if (cullface == "front") {
		glCullFace(GL_FRONT);
	} else {
		glCullFace(GL_FRONT_AND_BACK);
	}
}

void applyCullorder(string cullorder) {
	if (cullorder == "CCW") {
		glFrontFace(GL_CCW);
	}
	else {
		glFrontFace(GL_CW);
	}

}

void Scene::initScene() {

	glClearColor(bckg_x, bckg_y, bckg_z, bckg_a);

	applyDrawmode(drawmode);

	applyShading(shading);

	applyCullface(cullface);

	applyCullorder(cullorder);
}

Scene::~Scene() {
// TODO Auto-generated destructor stub
}
