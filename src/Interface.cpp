/*
 * Interface.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#include "Interface.h"
#include "Scene.h"

extern int main_window;

using namespace std;

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
	for (cam_it = Scene::getInstance()->cameras.begin();
	        cam_it != Scene::getInstance()->cameras.end(); cam_it++) {
		int live_var = 0;
		int id = id_counter++;
		if (cam_it->first == Scene::getInstance()->getInitCamera())
			live_var = 1;

		cams_rb.insert(map<string, int[2]>::value_type(cam_it->first, {
		        live_var, id }));
	}

	GLUI_Panel *camsPanel = glui_window->add_panel("Cameras", 1);

	map<string, int[2]>::iterator cb_it;
	for (cb_it = cams_rb.begin(); cb_it != cams_rb.end(); cb_it++) {
		glui_window->add_checkbox_to_panel(camsPanel, cb_it->first.c_str(),
		        &cb_it->second[0], cb_it->second[1], Interface::preprocessGUI);
	}

	glui_window->add_separator();

	// create lights panel
	vector<Light *>::iterator light_it;
	for (light_it = Scene::getInstance()->lights.begin();
	        light_it != Scene::getInstance()->lights.end(); light_it++) {
		int live_var = 0;
		int id = id_counter++;
		if ((*light_it)->isEnabled())
			live_var = 1;

		lights_cb.insert(map<string, int[2]>::value_type((*light_it)->getId(), {
		        live_var, id }));
	}

	GLUI_Panel *lightsPanel = glui_window->add_panel("Lights", 1);

	map<string, int[2]>::iterator rb_it;
	for (rb_it = lights_cb.begin(); rb_it != lights_cb.end(); rb_it++) {
		glui_window->add_checkbox_to_panel(camsPanel, rb_it->first.c_str(),
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

	map<string, int[2]>::iterator it;
	for (it = cams_rb.begin(); it != cams_rb.end(); it++) {
		if (it->second[1] == id) {
			Scene::getInstance()->setInitCamera(it->first);
			return;
		}
	}

	for (it = lights_cb.begin(); it != lights_cb.end(); it++) {
		if (it->second[1] == id) {
			Scene::getInstance()->getLight(it->first)->toggleLight();
			return;
		}
	}
}

