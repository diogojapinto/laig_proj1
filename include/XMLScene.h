#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include <vector>
#include <string>

using namespace std;

class XMLScene {
public:
	XMLScene(char *filename);
	~XMLScene();

private:
	TiXmlDocument* doc;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearencesElement;
	TiXmlElement* graphElement;

	TiXmlElement *findChildByAttribute(TiXmlElement *parent,
	        const char * attr,
	        const char *val);
	bool parseGlobals();
	bool parseCameras();
	bool parseLighting();
	bool parseTextures();
	bool parseAppearences();
	bool parseGraph();
	bool parseNode(TiXmlElement *curr_node, vector<string> nodes_processed);
};

#endif
