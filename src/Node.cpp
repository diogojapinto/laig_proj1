/*
 * Node.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: wso277
 */

#include "Node.h"
#include <GL/glut.h>
#include "Scene.h"

using namespace std;

Node::Node() {

	id = "";
	nodeAppearance = "default";
}

Node::Node(string id) {

	this->id = id;
	nodeAppearance = "default";
}

Node::Node(string id, float transforms[16]) {

	this->id = id;
	copy(&transforms[0], &transforms[16], this->transforms);
	nodeAppearance = "default";
}

void Node::addRef(string ref) {

	refs.push_back(ref);
}

void Node::addAppearance(string appearance) {

	nodeAppearance = appearance;
}
void Node::setTransform(float transforms[16]) {

	copy(&transforms[0], &transforms[16], this->transforms);
}

void Node::resetTransform() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW, transforms);
}

void Node::addTranslate(float x, float y, float z) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(this->transforms);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW, transforms);
	glPopMatrix();

}

void Node::addScale(float x, float y, float z) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(this->transforms);
	glScalef(x, y, z);
	glGetFloatv(GL_MODELVIEW, transforms);
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
	glGetFloatv(GL_MODELVIEW, transforms);
	glPopMatrix();
}
const float* Node::getTransform() {

	return transforms;
}

Appearance *Node::getAppearance() {
	return Scene::getInstance()->getAppearance(nodeAppearance);
}

list<string> Node::getRefs() {

	return refs;
}

string Node::getId() {

	return id;
}

Node::~Node() {
}
