#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"

class XMLScene
{
public:
	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	bool parseGlobals();
	bool parseCameras();
	bool parseLighting();
	bool parseTextures();
	bool parseAppearences();
	bool parseGraph();
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearencesElement;
	TiXmlElement* graphElement;
};

#endif
