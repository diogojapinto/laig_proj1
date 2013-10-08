/*
 * Node.h
 *
 *  Created on: Sep 29, 2013
 *      Author: wso277
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <list>
#include "CGFappearance.h"

using namespace std;

class Node {
private:
	string id;
	float transforms[16];
	list<string> refs;
	CGFappearance* nodeAppearance;

public:
	Node();
	Node(string id);
	Node(string id, float transforms[16]);
	void addRef(string ref);
	void addAppearance(CGFappearance* appearance);
	void setTransform(float transforms[16]);
	void resetTransform();
	void addTranslate(float x, float y, float z);
	void addScale(float x, float y, float z);
	void addRotation(float angle, char axis);
	const float* getTransform();
	CGFappearance* getAppearance();
	list<string> getRefs();
	string getId();
	virtual ~Node();
};

#endif /* NODE_H_ */
