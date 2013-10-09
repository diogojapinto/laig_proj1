/*
 * Appearance.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#include "Appearance.h"
#include "CGFapplication.h"
#include "Scene.h"
#include "InvalidTexRef.h"

using namespace std;

Appearance::Appearance() {
	id = "default";
	emi_r = 0.0;
	emi_g = 0.0;
	emi_b = 0.0;
	emi_a = 0.0;
	amb_r = 1.0;
	amb_g = 1.0;
	amb_b = 1.0;
	amb_a = 1.0;
	dif_r = 1.0;
	dif_g = 1.0;
	dif_b = 1.0;
	dif_a = 1.0;
	spec_r = 0.5;
	spec_g = 0.5;
	spec_b = 0.5;
	spec_a = 1.0;
	shin = 50.0;
	textRef = "none";
	sWrap = 0.0;
	tWrap = 0.0;
	isTextDefined = false;
}

Appearance::Appearance(string id) {
	this->id = id;
	emi_r = 0.0;
	emi_g = 0.0;
	emi_b = 0.0;
	emi_a = 0.0;
	amb_r = 1.0;
	amb_g = 1.0;
	amb_b = 1.0;
	amb_a = 1.0;
	dif_r = 1.0;
	dif_g = 1.0;
	dif_b = 1.0;
	dif_a = 1.0;
	spec_r = 0.5;
	spec_g = 0.5;
	spec_b = 0.5;
	spec_a = 1.0;
	shin = 50.0;
	textRef = "none";
	sWrap = 0.0;
	tWrap = 0.0;
	isTextDefined = false;
}

void Appearance::setId(string id) {
	this->id = id;
}

void Appearance::setEmissivity(float emi_r, float emi_g, float emi_b,
        float emi_a) {
	this->emi_r = emi_r;
	this->emi_g = emi_g;
	this->emi_b = emi_b;
	this->emi_a = emi_a;
}

void Appearance::setAmbient(float amb_r, float amb_g, float amb_b,
        float amb_a) {
	this->amb_r = amb_r;
	this->amb_g = amb_g;
	this->amb_b = amb_b;
	this->amb_a = amb_a;
}

void Appearance::setDiffuse(float dif_r, float dif_g, float dif_b,
        float dif_a) {
	this->dif_r = dif_r;
	this->dif_g = dif_g;
	this->dif_b = dif_b;
	this->dif_a = dif_a;
}

void Appearance::setSpecular(float spec_r, float spec_g, float spec_b,
        float spec_a) {
	this->spec_r = spec_r;
	this->spec_g = spec_g;
	this->spec_b = spec_b;
	this->spec_a = spec_a;
}

void Appearance::setShinniness(float shin) {
	this->shin = shin;
}

void Appearance::setTextProp(string text_id, float s_wrap, float t_wrap) {
	this->textRef = text_id;

	if (Scene::getInstance()->getTexture(textRef) == NULL) {
		throw InvalidTexRef(textRef);
	}
	this->sWrap = s_wrap;
	this->tWrap = t_wrap;

	isTextDefined = true;
}

float Appearance::getSWrap() {
	return sWrap;
}

float Appearance::getTWrap() {
	return tWrap;
}

void Appearance::apply() {
	float emissive[4] = { emi_r, emi_g, emi_b, emi_a };
	glMaterialfv(Scene::getInstance()->getCullface(), GL_EMISSION, emissive);

	float ambient[4] = { amb_r, amb_g, amb_b, amb_a };
	glMaterialfv(Scene::getInstance()->getCullface(), GL_AMBIENT, ambient);

	float diffuse[4] = { emi_r, emi_g, emi_b, emi_a };
	glMaterialfv(Scene::getInstance()->getCullface(), GL_DIFFUSE, diffuse);

	float specular[4] = { spec_r, spec_g, spec_b, spec_a };
	glMaterialfv(Scene::getInstance()->getCullface(), GL_SPECULAR, specular);

	glMaterialfv(Scene::getInstance()->getCullface(), GL_SHININESS, &shin);

	if (isTextDefined) {
		glEnable(GL_TEXTURE_2D);
		Scene::getInstance()->getTexture(textRef)->apply();
	} else
		glDisable(GL_TEXTURE_2D);
}

Appearance::~Appearance() {
}

