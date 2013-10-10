/*
 * Node.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: wso277
 */

#include "Node.h"
#include <GL/glut.h>
#include "Scene.h"
#include "MyPrimitive.h"
#include <iostream>

using namespace std;

Node::Node() {

	id = "";
	nodeAppearance = "default";
}

Node::Node(string id) {

	this->id = id;
	nodeAppearance = "default";

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glPopMatrix();
}

Node::Node(string id, float transforms[16]) {

	this->id = id;
	copy(&transforms[0], &transforms[16], this->transforms);
	nodeAppearance = "default";
}

void Node::addRef(string ref) {

	refs.push_back(ref);
}

void Node::setAppearance(string appearance) {

	nodeAppearance = appearance;
}
void Node::setTransform(float transforms[16]) {

	copy(&transforms[0], &transforms[16], this->transforms);
}

void Node::resetTransform() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
}

void Node::addTranslate(float x, float y, float z) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(this->transforms);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glPopMatrix();

}

void Node::addScale(float x, float y, float z) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(this->transforms);
	glScalef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glPopMatrix();
}
void Node::addRotation(float angle, char axis) {

	float x = 0, y = 0, z = 0;

	if (axis == 'x') {
		x = 1;
	} else if (axis == 'y') {
		y = 1;
	} else {
		z = 1;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(this->transforms);
	glRotatef(angle, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glPopMatrix();
}
const float* Node::getTransform() {

	return transforms;
}

Appearance *Node::getAppearance() {
	return Scene::getInstance()->getAppearance(nodeAppearance);
}

vector<string> Node::getRefs() {

	return refs;
}

string Node::getId() {

	return id;
}

Node::~Node() {
}

void Node::addPrimitive(MyPrimitive *prim) {
	prims.push_back(prim);
}

void Node::processNode() {

	glPushMatrix();

	glMultMatrixf(transforms);

	if (prims.size() != 0)
		drawPrims();

	vector<string>::iterator it;

	for (it = refs.begin(); it != refs.end(); it++) {
		Node *ptr = Scene::getInstance()->getNode((*it));
		ptr->processNode();
	}
	glPopMatrix();
}

#include <stdio.h>

void Node::drawPrims() {
	vector<MyPrimitive *>::const_iterator it;

	Appearance *app = getAppearance();

	for (it = prims.begin(); it != prims.end(); it++) {
		(*it)->setAppearance(nodeAppearance);
		app->apply();
		(*it)->draw();
	}
}
