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
#include "InvalidXMLException.h"
#include "InvalidPreAttrException.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {

	Scene::getInstance()->setCullorder("CCW");

	XMLScene parser;
	parser.setPaths();

	try {
		parser.loadFile();
	} catch (InvalidXMLException &e) {
		return -1;
	} catch (InvalidPreAttrException &e) {
		cout << e.getErrMessg();
		return -1;
	} catch (InvalidTexFile &e) {
		cout << "Invalid path to texture file: " << e.getFilePath() << endl;
		return -1;
	} catch (exception) {
		cout << "Unknown exception occured. Exiting...\n";
		return -1;
	}

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
