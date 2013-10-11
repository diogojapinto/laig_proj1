/*
 * Interface.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#include "Interface.h"
#include "Scene.h"
#include <iostream>

extern int main_window;

using namespace std;

Interface* Interface::activeInterface = NULL;
int Interface::modifiers = 0;
map<string, int*> Interface::cams_rb;
map<string, int*> Interface::lights_cb;
int *Interface::cams_vars = new int[MAX_CAMS];
int Interface::id_counter = 0;
int Interface::radio_id = 0;
GLUI_RadioGroup *Interface::cams_group = NULL;

Interface::Interface() {
}
Interface::~Interface() {
}

void Interface::init(int parent) {
	glui_window = GLUI_Master.create_glui_subwindow(parent,
	GLUI_SUBWINDOW_BOTTOM);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(idle);
	glui_window->set_main_gfx_window(main_window);
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

	// create cameras panel
	CameraElem::iterator cam_it;
	int i = 0;
	int init_camera_pos = 0;
	for (cam_it = Scene::getInstance()->cameras.begin();
			cam_it != Scene::getInstance()->cameras.end(); cam_it++) {
		int live_var = 0;
		int id = id_counter++;
		if (cam_it->first == Scene::getInstance()->getInitCamera()) {
			live_var = -1;
			init_camera_pos = i;
		}
		int* ptr = new int[2];
		ptr[0] = live_var;
		ptr[1] = i;
		cams_vars[i++] = live_var;
		cams_rb.insert(map<string, int*>::value_type(cam_it->first, ptr));
	}

	GLUI_Panel *camsPanel = glui_window->add_panel("Cameras", 1);
	radio_id = id_counter++;
	cams_group = glui_window->add_radiogroup_to_panel(
			camsPanel, cams_vars, radio_id, Interface::preprocessGUI);

	map<string, int*>::iterator cb_it;
	for (cb_it = cams_rb.begin(); cb_it != cams_rb.end(); cb_it++) {
		glui_window->add_radiobutton_to_group(cams_group, cb_it->first.c_str());
	}

	cams_group->set_int_val(init_camera_pos);

	glui_window->add_separator();

	// create lights panel
	vector<Light *>::iterator light_it;
	for (light_it = Scene::getInstance()->lights.begin();
			light_it != Scene::getInstance()->lights.end(); light_it++) {
		int live_var = 0;
		int id = id_counter++;
		if ((*light_it)->isEnabled())
			live_var = -1;

		int* ptrL = new int[2];
		ptrL[0] = live_var;
		ptrL[1] = id;
		lights_cb.insert(
				map<string, int*>::value_type((*light_it)->getId(), ptrL));
	}

	GLUI_Panel *lightsPanel = glui_window->add_panel("Lights", 1);

	map<string, int*>::iterator rb_it;
	for (rb_it = lights_cb.begin(); rb_it != lights_cb.end(); rb_it++) {
		glui_window->add_checkbox_to_panel(lightsPanel, rb_it->first.c_str(),
				&rb_it->second[0], rb_it->second[1], Interface::preprocessGUI);
	}
}

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
	int id = ctrl->user_id;
	map<string, int*>::iterator it;

	if (id == radio_id) {
		int val = cams_group->get_int_val();
		for (it = cams_rb.begin(); it != cams_rb.end(); it++) {
			if (it->second[1] == val) {
				Scene::getInstance()->setInitCamera(it->first);
				return;
			}
		}
	}

	for (it = lights_cb.begin(); it != lights_cb.end(); it++) {
		if (it->second[1] == id) {
			Scene::getInstance()->getLight(it->first)->toggleLight();
			return;
		}
	}
}

