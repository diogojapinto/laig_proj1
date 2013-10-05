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
#include "CGFappearance.h"

using namespace std;

/*
 * meter aqui constantes tipo ccw e assim
 */

/*
 * acho que estão trocados...
 *
 *
 * todo:
 *
 * finish torus (being done)		ficou melhor, mas parece que tem aneis definidos ao contrario
 * store data on the parser (next thing I'll do)
 *
 * acrescentar transf ao nó original	-	done
 * definir appearance default (white) -> fazer get e pop (const) -  done nao tenho a certeza se no yaf posso apagar os parametros da textura ou devo deixar em branco (procurar imagem da hello kitty)
 * usar aparencias com opengl e nao cgf ??
 * estruturar o programa segundo o ficheiro com nome retardado
 * criar interface para escolher pasta das texturas e ficheiro .yaf  - versao inicial feita, nao testada. Funcao para ir buscar os paths da textura feita
 *
 */

#define HEIGHT 768
#define WIDTH 1024

typedef map<string, Node*> GraphElem;
typedef map<string, string> TexElem;
typedef map<string, CGFappearance*> AppearanceElem;

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
	TexElem textures;
	AppearanceElem appearances;
	GraphElem graph;
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
	bool addTexture(string key, string path);
	void addAppearance(string key, CGFappearance* appearance);
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
	string getTexture(string key);
	CGFappearance* getAppearance(string key);
	Node* getNode(string key);
	void initScene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
