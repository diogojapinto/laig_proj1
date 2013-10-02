/*
 * Scene.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#include <fstream>
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
	doublesided = true;
	local = true;
	enabled = true;
	amb_x = 0;
	amb_y = 0;
	amb_z = 0;
	amb_a = 0;

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

void Scene::setRootId(string rootId) {
	this->rootId = rootId;
}

void Scene::addLight(Lights* light) {
	lights.push_back(light);
}

void Scene::addCamera(Camera* camera) {
	cameras.push_back(camera);
}

bool Scene::addTexture(string key, string path) {
	ifstream file;
	file.open(path.c_str(), ios::out);
	if (file.is_open()) {
		textures.insert(TexElem::value_type(key, path));
		file.close();
		return true;
	}
	else {
		return false;
	}

}

void Scene::addAppearance(string key, CGFappearance* appearance) {
	appearances.insert(AppearanceElem::value_type(key, appearance));
}

void Scene::addNode(string key, Node* node) {
	graph.insert(GraphElem::value_type(key, node));
}

void Scene::setLights(bool doublesided, bool local, bool enabled) {
	this->doublesided = doublesided;
	this->local = local;
	this->enabled = enabled;
}

void Scene::setAmb(float amb_x, float amb_y, float amb_z, float amb_a) {
	this->amb_x = amb_x;
	this->amb_y = amb_y;
	this->amb_z = amb_z;
	this->amb_a = amb_a;
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

string Scene::getRootId() {
	return rootId;
}

Lights* Scene::getLight(int index) {
	return lights[index];
}

Camera* Scene::getCamera(int index) {
	return cameras[index];
}

string Scene::getTexture(string key) {
	return textures[key];
}

CGFappearance* Scene::getAppearance(string key) {
	return appearances[key];
}

Node* Scene::getNode(string key) {
	return graph[key];
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
	} else {
		glFrontFace(GL_CW);
	}

}

void applyLights(bool doublesided, bool local, bool enabled, float amb_x,
		float amb_y, float amb_z, float amb_a) {
	if (enabled) {
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, doublesided);

		float amb[4] = { amb_x, amb_y, amb_z, amb_a };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);

	} else {
		glDisable(GL_LIGHTING);
	}

}

void Scene::initScene() {

	glClearColor(bckg_x, bckg_y, bckg_z, bckg_a);

	applyDrawmode(drawmode);

	applyShading(shading);

	applyCullface(cullface);

	applyCullorder(cullorder);

	applyLights(doublesided, local, enabled, amb_x, amb_y, amb_z, amb_a);
}

Scene::~Scene() {
// TODO Auto-generated destructor stub
}
