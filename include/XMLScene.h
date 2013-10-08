#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include <vector>
#include <string>

using namespace std;

class XMLScene {
	bool valid;
	TiXmlDocument* doc;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearencesElement;
	TiXmlElement* graphElement;
	string yaf_path;
	string texture_base_path;

public:
	XMLScene();
	~XMLScene();
	void loadFile();
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
	void setPaths();
	string getTexturePath(string texture_path, string texture_file);
};

#endif
