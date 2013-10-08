#include <fstream>
#include "Scene.h"
#include "CGFapplication.h"
#include "InvalidPreAttrException.h"

using namespace std;

Scene *Scene::instance = NULL;

Scene::Scene() {
	bckg_r = 0;
	bckg_g = 0;
	bckg_b = 0;
	bckg_a = 0;
	drawmode = GL_FILL;
	shading = GL_SMOOTH;
	cullface = GL_CCW;
	cullorder = GL_BACK;
	doublesided = true;
	local = true;
	enabled = true;
	amb_r = 0;
	amb_g = 0;
	amb_b = 0;
	amb_a = 0;

}

void Scene::setBackground(float bckg_r, float bckg_g, float bckg_b,
        float bckg_a) {
	this->bckg_r = bckg_r;
	this->bckg_g = bckg_g;
	this->bckg_b = bckg_b;
	this->bckg_a = bckg_a;
}

void Scene::setDrawmode(string drawmode) {
	if (drawmode == "fill") {
		this->drawmode = GL_FILL;
	} else if (drawmode == "line") {
		this->drawmode = GL_LINE;
	} else if (drawmode == "point") {
		this->drawmode = GL_POINT;
	} else {
		throw InvalidPreAttrException("drawmode");
	}
}

void Scene::setShading(string shading) {
	if (shading == "flat") {
		this->shading = GL_FLAT;
	} else if (shading == "smooth"){
		this->shading = GL_SMOOTH;
	} else {
		throw InvalidPreAttrException("shading");
	}
}

void Scene::setCullface(string cullface) {
	if (cullface == "none") {
		this->cullface = GL_NONE;
	} else if (cullface == "back") {
		this->cullface = GL_BACK;
	} else if (cullface == "front") {
		this->cullface = GL_FRONT;
	} else if (cullface == "both") {
		this->cullface = GL_FRONT_AND_BACK;
	} else {
		throw InvalidPreAttrException("cullface");
	}
}

void Scene::setCullorder(string cullorder) {
	if (cullorder == "CCW") {
		this->cullorder = GL_CCW;
	} else if (cullorder == "CW") {
		this->cullorder = GL_CW;
	} else {
		throw InvalidPreAttrException("cullorder");
	}
}

void Scene::setRootId(string rootId) {
	this->rootId = rootId;
}

void Scene::setInitCamera(string init_camera) {
	this->init_camera = init_camera;
}

void Scene::addLight(Light* light) {
	lights.push_back(light);
}

void Scene::addCamera(string key, Camera* camera) {
	cameras.insert(CameraElem::value_type(key, camera));
}

void Scene::addTexture(string key, string path) {
	ifstream file;
	file.open(path.c_str(), ios::out);
	if (file.is_open()) {
		CGFtexture *tex = new CGFtexture(path);
		textures.insert(TexElem::value_type(key, tex));
		file.close();
	} else {
		throw InvalidTexFile(path);
	}

}

void Scene::addAppearance(string key, Appearance* appearance) {
	appearances.insert(AppearanceElem::value_type(key, appearance));
}

void Scene::addNode(string key, Node* node) {
	graph.insert(GraphElem::value_type(key, node));
}

void Scene::setGlobalLights(bool doublesided, bool local, bool enabled) {
	this->doublesided = doublesided;
	this->local = local;
	this->enabled = enabled;
}

void Scene::setAmb(float amb_r, float amb_g, float amb_b, float amb_a) {
	this->amb_r = amb_r;
	this->amb_g = amb_g;
	this->amb_b = amb_b;
	this->amb_a = amb_a;
}

unsigned int Scene::getDrawmode() {
	return drawmode;
}

unsigned int Scene::getShading() {
	return shading;
}

const unsigned int Scene::getCullface() {
	return cullface;
}

const unsigned int Scene::getCullorder() {
	return cullorder;
}

string Scene::getRootId() {
	return rootId;
}

Light* Scene::getLight(int index) {
	return lights[index];
}

Camera* Scene::getCamera(string key) {
	return cameras[key];
}

CGFtexture * Scene::getTexture(string key) {
	return textures[key];
}

Appearance* Scene::getAppearance(string key) {
	return appearances[key];
}

Node* Scene::getNode(string key) {
	return graph[key];
}

void Scene::applyLights() {
	if (enabled) {
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, doublesided);

		float amb[4] = { amb_r, amb_g, amb_b, amb_a };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);

		for (unsigned int i = 0; i < lights.size(); i++) {
			lights[i]->toggleLight(i);
		}

	} else {
		glDisable(GL_LIGHTING);
	}

}

void Scene::initCamera() {
	cameras[init_camera]->setCamera();
}

void Scene::initScene() {

	glClearColor(bckg_r, bckg_g, bckg_b, bckg_a);

	glPolygonMode(cullface, drawmode);

	glShadeModel(shading);

	glCullFace(cullface);
	glFrontFace(cullorder);

	applyLights();

	initCamera();

}

Scene::~Scene() {
}

Scene *Scene::getInstance() {
	if (instance == NULL)
		instance = new Scene();
	return instance;
}
