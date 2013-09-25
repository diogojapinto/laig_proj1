#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include <math.h>

// Positions for two lights
float light0_pos[4] = { 5.5, 6.0, 1.1, 1.0 };
float light1_pos[4] = { 14.5, 6.0, 1.1, 1.0 };
float light2_pos[4] = { 6.5, 8.0, 22.0, 1.0 };
float light3_pos[4] = { 13.5, 8.0, 22.0, 1.0 };
float light4_pos[4] = { 30.0, 30.0, 30.0, 1.0 };

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4] = { 0, 0, 0, 0 };

float ambH[3] = { 0.8, 0.8, 0.8 };
float difH[3] = { 0.7, 0.7, 0.7 };
float specH[3] = { 0.1, 0.1, 0.1 };
float shininessH = 20.f;

float ambDif[3] = { 0.4, 0.4, 0.4 };
float difDif[3] = { 0.8, 0.8, 0.8 };
float specDif[3] = { 0.3, 0.3, 0.3 };
float shininessDif = 60.f;

float ambSpec[3] = { 0.4, 0.4, 0.4 };
float difSpec[3] = { 0.6, 0.6, 0.6 };
float specSpec[3] = { 0.8, 0.8, 0.8 };
float shininessSpec = 120.f;

float ambientNull[4] = { 0, 0, 0, 1 };

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

	light0->disable();
	//light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);

	light1->disable();
	//light1->enable();

	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambientNull);

	//light2->disable();
	light2->enable();

	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambientNull);

	light3->enable();

	light4 = new CGFlight(GL_LIGHT4, light4_pos);
	light4->setAmbient(ambientNull);
	light4->disable();

	rect = new MyRectangle();
	tri = new MyTriangle();
	cyl = new MyCylinder();
	sph = new MySphere();
	tor = new MyTorus();

	house_walls_appearence = new CGFappearance(ambH, difH, specH, shininessH);
	house_walls_appearence->setTexture("../data/wall.jpg");
	floor_appearence = new CGFappearance(ambDif, difDif, specDif, shininessDif);
	floor_appearence->setTexture("../data/grass.jpg");
	fence_appearence = new CGFappearance(ambDif, difDif, specDif, shininessDif);
	fence_appearence->setTexture("../data/bush.jpg");
	door_appearence = new CGFappearance(ambH, difH, specH, shininessH);
	door_appearence->setTexture("../data/door.jpg");
	roof_appearence = new CGFappearance(ambH, difH, specH, shininessH);
	roof_appearence->setTexture("../data/rooftop.jpg");
	table_top_appearence = new CGFappearance(ambSpec, difSpec, specSpec,
			shininessSpec);
	table_top_appearence->setTexture("../data/tabletop.jpg");
	table_leg_appearence = new CGFappearance(ambSpec, difSpec, specSpec,
			shininessSpec);
	table_leg_appearence->setTexture("../data/tableleg.jpg");
	tree_trunk_appearence = new CGFappearance(ambDif, difDif, specDif,
			shininessDif);
	tree_trunk_appearence->setTexture("../data/tree.jpg");
	tree_leafs_appearence = new CGFappearance(ambDif, difDif, specDif,
			shininessDif);
	tree_leafs_appearence->setTexture("../data/treetop.jpeg");
	rope_appearence = new CGFappearance(ambDif, difDif, specDif, shininessDif);
	rope_appearence->setTexture("../data/rope.png");
	swing_appearence = new CGFappearance(ambDif, difDif, specDif, shininessDif);
	swing_appearence->setTexture("../data/tire.jpg");
	light_body_appearence = new CGFappearance(ambSpec, difSpec, specSpec,
			shininessSpec);
	//light_body_appearence->setTexture("../data/post.jpeg");
	light_bulb_appearence = new CGFappearance(ambSpec, difSpec, specSpec,
			shininessSpec);
	//light_bulb_appearence->setTexture("../data/lamp.jpg");

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
	glRotatef(-90.0,1.0,0.0,0.0);
	rect->draw();
	glPopMatrix();

	// Draw front wall
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslated(5.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 1.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 2.5, 1.0);
	glScaled(5.0, 5.0, 1.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.5, 6.5, 1.0);
	glScaled(5.0, 3.0, 1.0);
	rect->draw();
	glPopMatrix();

	// Draw door
	door_appearence->apply();
	glPushMatrix();
	glTranslated(10.0, 2.5, 1.0);
	glScaled(4.0, 5.0, 1.0);
	rect->draw();
	glPopMatrix();

	// Draw roof
	roof_appearence->apply();
	glPushMatrix();
	glTranslatef(10.0, 8.6, 0.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glScalef(15.0, 1.0, 5.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	rect->draw();
	glPopMatrix();

	// Draw side walls
	house_walls_appearence->apply();
	glPushMatrix();
	glTranslatef(17.0, 4, 0.5);
	glScalef(1.0, 8.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
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
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18.5, 1.5, 0.0);
	glScalef(3.0, 3.0, 1.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.5, 10.0);
	glScalef(1.0, 3.0, 20.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	rect->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 1.5, 10.0);
	glScalef(1.0, 3.0, 20.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	rect->draw();
	glPopMatrix();

	//Draw Table

	glPushMatrix();
	glTranslatef(4.0, 2.0, 10.0);
	glScaled(5.0, 0.25, 5.0);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	table_top_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.0, 0.86, 10.0);
	glScaled(1.5, 2.0, 1.5);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	table_leg_appearence->apply();
	cyl->draw();
	glPopMatrix();

	// draw tree

	glPushMatrix();
	glTranslatef(16.0, 2.5, 13);
	glScalef(2.0, 5.0, 2.0);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	tree_trunk_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16.0, 6.2, 13);
	glScalef(9.0, 3.0, 9.0);
	tree_leafs_appearence->apply();
	sph->draw();
	glPopMatrix();

	// draw swing
	glPushMatrix();
	glTranslatef(12.5, 4, 13.0);
	glScaled(0.08, 5.0, 0.08);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	rope_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14.0, 4, 13.0);
	glScaled(0.08, 5.0, 0.08);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	rope_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 1.7, 13);
	glScalef(0.8, 0.8, 0.8);
	glRotatef(90, 1.0, 0.0, 0.0);
	swing_appearence->apply();
	tor->draw();
	glPopMatrix();

	// draw light1
	glPushMatrix();
	glTranslatef(6.5, 4, 22.0);
	glScaled(0.4, 8.0, 0.4);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	light_body_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, 8.0, 22.0);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(90, 1.0, 0.0, 0.0);
	light_bulb_appearence->apply();
	tor->draw();
	glPopMatrix();

	// draw light2
	glPushMatrix();
	glTranslatef(13.5, 4, 22.0);
	glScaled(0.4, 8.0, 0.4);
	glTranslated(0.0, -0.5, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	light_body_appearence->apply();
	cyl->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.5, 8.0, 22.0);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(90, 1.0, 0.0, 0.0);
	light_bulb_appearence->apply();
	tor->draw();
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
	delete (light3);
	delete (light4);
	delete (house_walls_appearence);
	delete (floor_appearence);
	delete (fence_appearence);
	delete (door_appearence);
	delete (roof_appearence);
	delete (table_top_appearence);
	delete (table_leg_appearence);
	delete (tree_trunk_appearence);
	delete (tree_leafs_appearence);
	delete (rope_appearence);
	delete (swing_appearence);
	delete (light_body_appearence);
	delete (light_bulb_appearence);
	delete (rect);
	delete (tri);
	delete (cyl);
	delete (sph);
	delete (tor);
}
