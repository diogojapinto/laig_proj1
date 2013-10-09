#include "Light.h"
#include "GL/glut.h"

using namespace std;

Light::Light() {
	id = "";
	enabled = false;
	ready = false;
	loc_x = 0;
	loc_y = 0;
	loc_z = 0;
	amb_x = 0;
	amb_y = 0;
	amb_z = 0;
	amb_a = 0;
	dif_x = 0;
	dif_y = 0;
	dif_z = 0;
	dif_a = 0;
	spec_x = 0;
	spec_y = 0;
	spec_z = 0;
	spec_a = 0;
}

Light::Light(string id) {
	this->id = id;
	enabled = false;
	ready = false;
	loc_x = 0;
	loc_y = 0;
	loc_z = 0;
	amb_x = 0;
	amb_y = 0;
	amb_z = 0;
	amb_a = 0;
	dif_x = 0;
	dif_y = 0;
	dif_z = 0;
	dif_a = 0;
	spec_x = 0;
	spec_y = 0;
	spec_z = 0;
	spec_a = 0;
}

Light::Light(string id, bool enabled) {
	this->id = id;
	this->enabled = enabled;
	ready = false;
	loc_x = 0;
	loc_y = 0;
	loc_z = 0;
	amb_x = 0;
	amb_y = 0;
	amb_z = 0;
	amb_a = 0;
	dif_x = 0;
	dif_y = 0;
	dif_z = 0;
	dif_a = 0;
	spec_x = 0;
	spec_y = 0;
	spec_z = 0;
	spec_a = 0;
}
void Light::setLocation(float loc_x, float loc_y, float loc_z) {
	this->loc_x = loc_x;
	this->loc_y = loc_y;
	this->loc_z = loc_z;
}

void Light::setAmbient(float amb_x, float amb_y, float amb_z, float amb_a) {
	this->amb_x = amb_x;
	this->amb_y = amb_y;
	this->amb_z = amb_z;
	this->amb_a = amb_a;
}

void Light::setDiffuse(float dif_x, float dif_y, float dif_z, float dif_a) {
	this->dif_x = dif_x;
	this->dif_y = dif_y;
	this->dif_z = dif_z;
	this->dif_a = dif_a;
}

void Light::setSpecular(float spec_x, float spec_y, float spec_z,
		float spec_a) {
	this->spec_x = spec_x;
	this->spec_y = spec_y;
	this->spec_z = spec_z;
	this->spec_a = spec_a;
}

void Light::readyLight(int index) {
	float loc[4] = { loc_x, loc_y, loc_z, 1 };
	float amb[4] = { amb_x, amb_y, amb_z, amb_a };
	float dif[4] = { dif_x, dif_y, dif_z, dif_a };
	float spec[4] = { spec_x, spec_y, spec_z, spec_a };
	switch (index) {
	case 0:
		glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, loc);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 1:
		glPushMatrix();
		glLightfv(GL_LIGHT1, GL_POSITION, loc);
		glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glLightfv(GL_LIGHT2, GL_POSITION, loc);
		glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glLightfv(GL_LIGHT3, GL_POSITION, loc);
		glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT3, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glLightfv(GL_LIGHT4, GL_POSITION, loc);
		glLightfv(GL_LIGHT4, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT4, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		glLightfv(GL_LIGHT5, GL_POSITION, loc);
		glLightfv(GL_LIGHT5, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT5, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glLightfv(GL_LIGHT6, GL_POSITION, loc);
		glLightfv(GL_LIGHT6, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT6, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	case 7:
		glPushMatrix();
		glLightfv(GL_LIGHT7, GL_POSITION, loc);
		glLightfv(GL_LIGHT7, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT7, GL_SPECULAR, spec);
		glPopMatrix();
		break;
	}

}

void Light::toggleLight(int index) {

	if (!ready) {
		readyLight(index);
	}

	switch (index) {
	case 0:
		if (enabled) {
			glEnable(GL_LIGHT0);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT0);
			enabled = true;
		}
		break;
	case 1:
		if (enabled) {
			glEnable(GL_LIGHT1);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT1);
			enabled = true;
		}
		break;
	case 2:
		if (enabled) {
			glEnable(GL_LIGHT2);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT2);
			enabled = true;
		}
		break;
	case 3:
		if (enabled) {
			glEnable(GL_LIGHT3);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT3);
			enabled = true;
		}
		break;
	case 4:
		if (enabled) {
			glEnable(GL_LIGHT4);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT4);
			enabled = true;
		}
		break;
	case 5:
		if (enabled) {
			glEnable(GL_LIGHT5);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT5);
			enabled = true;
		}
		break;
	case 6:
		if (enabled) {
			glEnable(GL_LIGHT6);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT6);
			enabled = true;
		}
		break;
	case 7:
		if (enabled) {
			glEnable(GL_LIGHT7);
			enabled = false;
		}
		else {
			glDisable(GL_LIGHT7);
			enabled = true;
		}
		break;
	}

}

Light::~Light() {
}
