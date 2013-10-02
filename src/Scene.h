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
#include <map>
#include "Lights.h"
#include "Camera.h"
#include "Node.h"

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
	string rootId;
	vector<Lights*> lights;
	vector<Camera*> cameras;
	map<string,Node*> graph;
	bool doublesided;
	bool local;
	bool enabled;
	float amb_x, amb_y, amb_z, amb_a;
public:
	Scene();
	void setBackground(float bckg_x, float bckg_y, float bckg_z, float bckg_a);
	void setDrawmode(string drawmode);
	void setShading(string shading);
	void setCullface(string cullface);
	void setCullorder(string cullorder);
	void setRootId(string rootId);
	void addLight(Lights* light);
	void addCamera(Camera* camera);
	void addNode(string key, Node* node);
	void setLights(bool doublesided, bool local, bool enabled);
	void setAmb(float amb_x, float amb_y, float amb_z, float amb_a);
	string getDrawmode();
	string getShading();
	string getCullface();
	string getCullorder();
	string getRootId();
	Lights* getLight(int index);
	Camera* getCamera(int index);
	Node* getNode(string key);
	void initScene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
