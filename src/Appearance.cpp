/*
 * Appearance.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#include "Appearance.h"
#include "CGFapplication.h"

using namespace std;

Appearance::Appearance() :
		CGFappearance() {
	id = "";
	emi_x = 0;
	emi_y = 0;
	emi_z = 0;
	emi_a = 0;

}

Appearance::Appearance(string id) :
		CGFappearance() {
	this->id = id;
	emi_x = 0;
	emi_y = 0;
	emi_z = 0;
	emi_a = 0;

}

Appearance::Appearance(string id, string tex, int s, int t) :
		CGFappearance(tex, s, t) {
	this->id = id;
	emi_x = 0;
	emi_y = 0;
	emi_z = 0;
	emi_a = 0;

}

int Appearance::getSWrap() {
	return sWrap;
}

int Appearance::getTWrap() {
	return tWrap;
}

void Appearance::setEmissive(float emi_x, float emi_y, float emi_z,
		float emi_a) {
	this->emi_x = emi_x;
	this->emi_y = emi_y;
	this->emi_z = emi_z;
	this->emi_a = emi_a;
}

void Appearance::applyEmissive() {
	float emissive[4] = {emi_x, emi_y, emi_z, emi_a};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
}

Appearance::~Appearance() {
	// TODO Auto-generated destructor stub
}

