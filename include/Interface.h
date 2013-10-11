/*
 * Interface.h
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <GL/glui.h>
#include <map>
#include <string>

using namespace std;

//Based on CGFinterface. Simpler version
class Interface {
private:
	static int modifiers; ///< Stores the state of modifier keys (CTRL, ALT, SHIFT) for use in mouse and keyboard event handlers
	static Interface * activeInterface;
	GLUI* glui_window;
	float displacementX;
	float displacementY;
	bool pressing_left;
	bool pressing_middle;
	bool pressing_right;
	float prev_X;
	float prev_Y;

	// 1-> live_var
	// 2-> id
	map<string, int[2]> cams_rb;
	map<string, int[2]> lights_cb;

	int id_counter = 0;

public:
	Interface();
	virtual ~Interface();

	void init(int parent);///< Initializes the interface, in terms of handler setup and other low-level operations. Should not be overriden by subclasses
	void initGUI(); ///< Initializes the graphical interface itself, i.e. creating controls and establishing relations with the scene. Should be overriden by subclasses. Default is empty.
	static void setActiveInterface(Interface *gli);///< registers _gli_ as the active interface

	/** @name Static input (keyboard, mouse) handlers to be registered with GLUT
	 * These methods are global handlers that are registered by the application as the keyboard and mouse handlers.
	 * When invoked, they will route execution to the corresponding instance methods of the active CGFinterface instance.
	 */
	//@{
	static void preprocessKeyboard(unsigned char key, int x, int y);///< Called when a key is pressed. Receives as parameters the key pressed, and the mouse coordinates at the time of the press.
	static void preprocessMouse(int button, int state, int x, int y);///< Called when a mouse button event occurs.
	static void preprocessMouseMoved(int x, int y);	///< Called when the mouse moves while *some* mouse button is pressed
	static void preprocessPassiveMouseMoved(int x, int y);///< Called when the mouse moves while *no* mouse button is pressed
	//@}

	static void preprocessGUI(GLUI_Control *ctrl);///< Static handler to be registered as callback for every control created. When a control is interacted with, this function will route execution to the active interface's processGUI() method, providing a pointer to the control.
};

#endif /* INTERFACE_H_ */
