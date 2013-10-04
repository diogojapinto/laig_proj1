/* 
 * criar forma de escolher yaf e pasta de texturas
 * 
 */

#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "LightingScene.h"
#include "XMLScene.h"
#include "Scene.h"

using std::cout;
using std::exception;

Scene *scene;

int main(int argc, char* argv[]) {

	scene = new Scene();
	scene->setCullorder("CCW");

	XMLScene scene("../scene.yaf");

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new LightingScene());
		app.setInterface(new CGFinterface());

		app.run();
	} catch (GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	} catch (exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
}
