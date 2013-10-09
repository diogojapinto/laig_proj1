/*
 * Interface.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#include "Interface.h"

Interface::Interface() {
}

Interface::~Interface() {
}

void Interface::init(int parent) {
	glui_window = GLUI_Master.create_glui_subwindow(parent,
	GLUI_SUBWINDOW_BOTTOM);
	GLUI_Master.set_glutKeyboardFunc(Interface::preprocessKeyboard);

	GLUI_Master.set_glutMouseFunc(Interface::preprocessMouse);
	glutMotionFunc(Interface::preprocessMouseMoved);
	glutPassiveMotionFunc(Interface::preprocessPassiveMouseMoved);
	displacementX = 0;
	displacementY = 0;

	pressing_left = false;
	pressing_right = false;
	pressing_middle = false;

	prev_X = 0;
	prev_Y = 0;
}

void Interface::initGUI() {

}

Interface* Interface::activeInterface;
int Interface::modifiers;

void Interface::setActiveInterface(Interface *gli) {
	activeInterface = gli;
}

void Interface::preprocessKeyboard(unsigned char key, int x, int y) {
	modifiers = glutGetModifiers();
}

void Interface::preprocessMouse(int button, int state, int x, int y) {
	modifiers = glutGetModifiers();
}
void Interface::preprocessMouseMoved(int x, int y) {

}

void Interface::preprocessPassiveMouseMoved(int x, int y) {

}

void Interface::preprocessGUI(GLUI_Control *ctrl) {
}

