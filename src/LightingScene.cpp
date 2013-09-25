#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "Plane.h"

#include <math.h>

float pi = acos(-1.0);
float deg2rad = pi / 180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// Positions for two lights
float light0_pos[4] = { 4, 6.0, 5.0, 1.0 };
float light1_pos[4] = { 10.5, 6.0, 5.0, 1.0 };

float light2_pos[4] = { 10.5, 10.0, 9.0, 1.0 };
float light3_pos[4] = { 4, 10.0, 9.0, 1.0 };

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4] = { 0, 0, 0, 0 };

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

float ambientNull[4] = { 0, 0, 0, 1 };
float yellow[4] = { 1, 1, 0, 1 };

Plane p(100);

void LightingScene::init() {
	// Enables lighting computations
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	// Declares and enables two lights, with null ambient component

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	light0->setSpecular(yellow);

	//light0->disable();
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);

	//light1->disable();
	light1->enable();

	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambientNull);
	light2->setKc(0);
	light2->setKl(1.0);
	light2->setKq(0);

	//light2->disable();
	light2->enable();

	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambientNull);
	light3->setSpecular(yellow);
	light3->setKc(0);
	light3->setKl(0);
	light3->setKq(0.2);

	//light3->disable();
	light3->enable();

	rect = new MyRectangle();
	tri = new MyTriangle();

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
	//roof_appearence->setTexture("../data/roof.jpg");

	glShadeModel(GL_SMOOTH);
}

void LightingScene::display() {
	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer every time we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	light0->draw();
	light1->draw();
	light2->draw();
	light3->draw();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	// Draw floor
	floor_appearence->apply();
	glPushMatrix();
	glTranslatef(10.0, 0.0, 10.0);
	glScalef(20.0, 1.0, 20.0);
	rect->draw();
	glPopMatrix();

	// Draw front wall
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslated(5.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	// Draw door
	door_appearence->apply();
	glPushMatrix();
	glTranslated(10.0, 2.5, 1.0);
	glScaled(4.0, 5.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	// Draw roof
	roof_appearence->apply();
	glPushMatrix();
	glTranslatef(10.0, 8.6, 0.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glScalef(15.0, 1.0, 5.0);
	rect->draw();
	glPopMatrix();

	// Draw side walls
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslatef(17.0, 4, 0.5);
	glScalef(1.0, 8.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17.0, 8.3, 0.5);
	glScalef(1.0, 0.6, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	tri->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 4, 0.5);
	glScalef(1.0, 8.0, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 8.3, 0.5);
	glScalef(1.0, 0.6, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	tri->draw();
	glPopMatrix();

	// Draw fence
	fence_appearence->apply();
	glPushMatrix();
	glTranslatef(1.5, 1.5, 0.0);
	glScalef(3.0, 3.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18.5, 1.5, 0.0);
	glScalef(3.0, 3.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.5, 10.0);
	glScalef(1.0, 3.0, 20.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 1.5, 10.0);
	glScalef(1.0, 3.0, 20.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	rect->draw();
	glPopMatrix();

	// ---- END Primitive drawing section

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

LightingScene::~LightingScene() {
	delete (light0);
	delete (light1);
	delete (house_walls_appearence);
	delete (floor_appearence);
	delete (fence_appearence);
	delete (door_appearence);
	delete (roof_appearence);
	delete (rect);
	delete (tri);

}
