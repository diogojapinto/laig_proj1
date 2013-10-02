/*
 * Scene.h
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <string>
#include <vector>
#include "Lights.h"
#include "Camera.h"

using namespace std;

#define HEIGHT 1024
#define WIDTH 768

class Scene {
private:
	float bckg_x, bckg_y, bckg_z, bckg_a;
	string drawmode;
	string shading;
	string cullface;
	string cullorder;
	vector<Lights*> lights;
	vector<Camera*> cameras;
public:
	Scene();
	void setBackground(float bckg_x, float bckg_y, float bckg_z, float bckg_a);
	void setDrawmode(string drawmode);
	void setShading(string shading);
	void setCullface(string cullface);
	void setCullorder(string cullorder);
	void addLight(Lights* light);
	void addCamera(Camera* camera);
	string getDrawmode();
	string getShading();
	string getCullface();
	string getCullorder();
	Lights* getLight(int index);
	Camera* getCamera(int index);
	void initScene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
