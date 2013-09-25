#include "TPscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFappearance.h"

#include <math.h>

float pi = acos(-1.0);
float deg2rad = pi / 180.0;

CGFlight* light0;

float difL0[4] = { 1.0, 1.0, 1.0, 1.0 };
float specL0[4] = { 1.0, 1.0, 1.0, 1.0 };
float ambientNull[4] = { 0.0, 0.0, 0.0, 1.0 };

float ambHW[3] = { 0.2, 0.2, 0.2 };
float difHW[3] = { 1.0, 0.81, 0.0 };
float specHW[3] = { 0.1, 0.1, 0.1 };
float shininessHW = 20.f;

float ambFl[3] = { 0.2, 0.2, 0.2 };
float difFl[3] = { 0.0, 0.82, 0.0 };
float specFl[3] = { 0.3, 0.3, 0.3 };
float shininessFl = 40.f;

float ambFe[3] = { 0.2, 0.2, 0.2 };
float difFe[3] = { 0.0, 0.41, 0.0 };
float specFe[3] = { 0.2, 0.2, 0.2 };
float shininessFe = 30.f;

float ambD[3] = { 0.2, 0.2, 0.2 };
float difD[3] = { 0.82, 0.41, 0.0 };
float specD[3] = { 0.1, 0.1, 0.1 };
float shininessD = 20.f;

float ambR[3] = { 0.2, 0.2, 0.2 };
float difR[3] = { 0.9, 0.0, 0.0 };
float specR[3] = { 0.5, 0.5, 0.5 };
float shininessR = 50.f;

float globalAmbientLight[4] = { 0.2, 0.2, 0.2, 1.0 };

void TPscene::init() {
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight); // Define ambient light

	// Declares and enables a light
	float light0_pos[4] = { 6.0, 10.0, 10.0, 1.0 };
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	/*light0->setDiffuse(difL0);
	 light0->setSpecular(specL0);
	 light0->setKc(0.1);
	 light0->setKl(0.1);
	 light0->setKq(0.1);*/
	light0->enable();

	house_walls_appearence = new CGFappearance(ambHW, difHW, specHW,
			shininessHW);
	house_walls_appearence->setTexture("../data/wall.jpg");
	floor_appearence = new CGFappearance(ambFl, difFl, specFl, shininessFl);
	floor_appearence->setTexture("../data/grass.jpg");
	fence_appearence = new CGFappearance(ambFe, difFe, specFe, shininessFe);
	fence_appearence->setTexture("../data/bush.jpg");
	door_appearence = new CGFappearance(ambD, difD, specD, shininessD);
	door_appearence->setTexture("../data/door.jpg");
	roof_appearence = new CGFappearance(ambR, difR, specR, shininessR);
	//roof_appearence->setTexture("../data/door.jpg");

	glEnable(GL_NORMALIZE);

	glShadeModel(GL_FLAT);
}

void TPscene::display() {

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// ---- END Background, camera and axis setup

	// Draw floor
	floor_appearence->apply();
	glPushMatrix();
	glTranslatef(10.0, 0.0, 10.0);
	glScalef(20.0, 0.0, 20.0);
	rect.draw();
	glPopMatrix();

	// Draw front wall
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslated(5.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	// Draw door
	door_appearence->apply();
	glPushMatrix();
	glTranslated(10.0, 2.5, 1.0);
	glScaled(4.0, 5.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	// Draw roof
	roof_appearence->apply();
	glPushMatrix();
	glTranslatef(10.0, 8.6, 0.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glScalef(15.0, 0.0, 5.0);
	rect.draw();
	glPopMatrix();

	// Draw side walls
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslatef(17.0, 4, 0.5);
	glScalef(0.0, 8.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17.0, 8.3, 0.5);
	glScalef(0.0, 0.6, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	tri.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 4, 0.5);
	glScalef(0.0, 8.0, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 8.3, 0.5);
	glScalef(0.0, 0.6, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	tri.draw();
	glPopMatrix();

	// Draw fence
	fence_appearence->apply();
	glPushMatrix();
	glTranslatef(1.5, 1.5, 0.0);
	glScalef(3.0, 3.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18.5, 1.5, 0.0);
	glScalef(3.0, 3.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.5, 10.0);
	glScalef(0.0, 3.0, 20.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 1.5, 10.0);
	glScalef(0.0, 3.0, 20.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	rect.draw();
	glPopMatrix();

	glutSwapBuffers();
}

TPscene::~TPscene() {
	delete(light0);
	delete (house_walls_appearence);
	delete (floor_appearence);
	delete (fence_appearence);
	delete(door_appearence);
	delete(roof_appearence);
}
